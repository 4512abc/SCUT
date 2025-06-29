package org.example.controller;

import cn.hutool.core.util.StrUtil;
import lombok.extern.slf4j.Slf4j;
import org.apache.ibatis.annotations.Delete;
import org.example.common.result.Result;
import org.example.exception.CustomException;
import org.example.model.dto.AdminUserDto.AdminUserLoginDto;
import org.example.model.query.UserQuery.AccountLoginQuery;
import org.example.model.query.UserQuery.RegisterQuery;
import org.example.service.AdminUserService;
import org.example.utils.JWTUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.example.utils.JWTUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import java.util.HashMap;
import java.util.Map;

import static org.example.common.result.ResultCode.*;
import static org.example.common.result.ResultCode.USER_EXIST_ERROR;

@Slf4j
@RestController
@RequestMapping(value="/api/admin")
public class AdminUserController {

    @Autowired
    private AdminUserService adminUserService;
    @PostMapping("/register")
    public Result register(@RequestBody RegisterQuery registerQuery, HttpServletRequest request, HttpServletResponse response) {
        log.info("[调试] 收到注册请求，数据: {}", registerQuery);

        //query是前端管理的参数，不要修改
        // 检查基本参数
        if (StrUtil.isBlank(registerQuery.getPassword()) ||
                StrUtil.isBlank(registerQuery.getEmail()) ||
                StrUtil.isBlank(registerQuery.getCode())) {
            return Result.error(PARAM_ERROR);
        }

        // 获取 session，如果不存在则返回 null（不创建新session）
        HttpSession session = request.getSession(false);
        if (session == null) {
            log.error("[调试] Session不存在");
            return Result.error(EMAIL_TIME_OUT);
        }

        // 获取存储的验证码
        String storedCode = (String) session.getAttribute("email_code");
        log.info("[调试] Session ID: {}, 存储的验证码: {}", session.getId(), storedCode);

        if (storedCode == null) {
            return Result.error(EMAIL_TIME_OUT);
        }
        if(!registerQuery.getEmail().equals((String) session.getAttribute("Email")))
        {
            return Result.error(EMAIL_ERROR);
        }

        // 验证码比对
        if (!registerQuery.getCode().equals(storedCode)) {
            return Result.error(EMAIL_CODE_ERROR);
        }

        try {
            // 调用service注册用户
            String success = adminUserService.register(registerQuery);
            if (success!=null) {
                // 注册成功后清除验证码
                session.removeAttribute("email_code");
                session.removeAttribute("Email");
                // 确保设置新的session id
                response.setHeader("Set-Cookie", "JSESSIONID=" + session.getId() + "; Path=/; HttpOnly; SameSite=None; Secure");
                return Result.success(success);
            } else {
                return Result.error(USER_EXIST_ERROR);
            }
        }  catch (CustomException e) {
            log.error("[调试] 注册异常: {}", e.getMessage());
            return Result.error(e.getCode(), e.getMessage());
        } catch (Exception e) {
            log.error("[调试] 注册过程异常", e);
            return Result.error("-1", e.getMessage());
        }
    }

    @PostMapping("/login")
    public Result login(@RequestBody AccountLoginQuery accountLoginQuery, HttpServletResponse response) {
        try {
            AdminUserLoginDto adminUserLoginDto = adminUserService.findByAccount(accountLoginQuery);

            // 使用统一的token生成方法
            String token = generateUserToken(adminUserLoginDto.getId(), adminUserLoginDto.getAccessLevel());

            // 构建返回数据
            Map<String, Object> resultData = new HashMap<>();
            resultData.put("token", token);
            resultData.put("userInfo", adminUserLoginDto);

            response.setHeader(JWTUtils.header, token);
            return Result.success(resultData);
        } catch (CustomException e) {
            return Result.error(e.getCode(), e.getMessage());
        } catch (Exception e) {
            log.error("[调试] 登录异常", e);
            return Result.error("-1", e.getMessage());
        }
    }

    private String generateUserToken(Long userId, String identifier) {
        Map<String, Object> claims = new HashMap<>();
        claims.put("id", userId);
        claims.put("accessLevel", identifier != null ? identifier : ""); // 统一标识符，可以是account或openid
        claims.put("loginTime", System.currentTimeMillis());
        return JWTUtils.getToken(claims);
    }

    @PostMapping("/reset_pwd")
    public Result resetPassword(@RequestBody String password, @RequestHeader("Authorization")String token) {
        log.info("[调试] 收到重置密码请求，数据: {}",password);

        // 检查基本参数
        if (StrUtil.isBlank(password)){
            return Result.error(PARAM_ERROR);
        }

        Map<String,Object> claims=JWTUtils.getClaims(token);
        adminUserService.resetPassword((Long) claims.get("id"),password);
        return Result.success("success");
    }
}
