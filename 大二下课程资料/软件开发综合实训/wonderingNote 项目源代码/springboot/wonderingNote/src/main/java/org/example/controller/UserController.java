package org.example.controller;


import cn.hutool.core.util.StrUtil;
import org.example.common.result.Result;
import org.example.common.result.ResultCode;
import org.example.exception.CustomException;
import org.example.model.dto.FileInfoDto.FileInfoDto;
import org.example.model.dto.UserUpdateDto.ResetPwdDto;
import org.example.model.entity.User;
import org.example.model.query.UserQuery.*;
import org.example.model.dto.UserDto.AccountLoginDto;
import org.example.model.query.UserUpdateQuery.ResetPwdQuery;
import org.example.model.query.UserUpdateQuery.UserUpdateQuery;
import org.example.model.vo.FileInfoVo.FileUploadVo;
import org.example.utils.JWTUtils;
import org.example.service.UserService;
import org.example.utils.EmailUtil;
import org.example.utils.GenerateEmailCode;
import org.example.utils.VerifyEmail;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import lombok.extern.slf4j.Slf4j;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import static org.example.common.result.ResultCode.WECHAT_LOGIN_ERROR;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import static org.example.common.result.ResultCode.*;

@RestController
@RequestMapping(value="/api/auth")
@CrossOrigin
@Slf4j
public class UserController {
    @Autowired
    private UserService userService;

    @Autowired
    private EmailUtil emailUtil;

    @PostMapping("/login")
    public Result login(@RequestBody AccountLoginQuery accountLoginQuery, HttpServletResponse response) {
        try {
            AccountLoginDto accountLoginDto = userService.findByAccount(accountLoginQuery);

            // 使用统一的token生成方法
            String token = generateUserToken(accountLoginDto.getId(), accountLoginDto.getAccount());

            // 构建返回数据
            Map<String, Object> resultData = new HashMap<>();
            resultData.put("token", token);
            resultData.put("userInfo", accountLoginDto);

            response.setHeader(JWTUtils.header, token);
            return Result.success(resultData);
        } catch (CustomException e) {
            return Result.error(e.getCode(), e.getMessage());
        } catch (Exception e) {
            log.error("[调试] 登录异常", e);
            return Result.error("-1", e.getMessage());
        }
    }

    @PostMapping("/email_code")
    public Result emailCode(@RequestBody EmailCodeQuery requestData, HttpServletRequest request, HttpServletResponse response) {
        String email = requestData.getEmail();
        if(!EmailUtil.isValidEmail(email))
            return Result.error(EMAIL_ERROR);
        log.info("[调试] 收到发送验证码请求");
        log.info("[调试] 请求头 Content-Type: {}", request.getContentType());
        log.info("[调试] 请求数据: {}", requestData);
        log.info("[调试] 提取的邮箱: {}", email);

        if (StrUtil.isBlank(email)) {
            log.error("[调试] 邮箱地址为空");
            return Result.error(EMAIL_ERROR);
        }

        try {
            HttpSession session = request.getSession(true);
            String sessionId = session.getId();
            response.setHeader("Set-Cookie", "JSESSIONID=" + sessionId + "; Path=/; HttpOnly; SameSite=None; Secure");

            // 生成验证码
            GenerateEmailCode generateEmailCode = new GenerateEmailCode();
            String verificationCode = generateEmailCode.generateVerificationCode();
            log.info("[调试] 生成的验证码: {}", verificationCode);

            // 存储验证码
            session.setAttribute("email_code", verificationCode);
            session.setMaxInactiveInterval(24 * 60);
            log.info("[调试] 验证码已存储到session，有效期24分钟");

            //存储邮箱
            session.setAttribute("Email", email);
            log.info("[调试] 邮箱已存储到session");

            // 发送验证码邮件
            String subject = "验证码";
            String text = "您的验证码是: " + verificationCode;
            emailUtil.sendEmail(email, subject, text);
            log.info("[调试] 验证码邮件发送成功");

            return Result.success(null);
        } catch (Exception e) {
            log.error("[调试] 发送验证码异常", e);
            return Result.error(EMAIL_SEND_ERROR);
        }
    }

    @PostMapping("/register")
    public Result register(@RequestBody RegisterQuery registerQuery, HttpServletRequest request, HttpServletResponse response) {
        log.info("[调试] 收到注册请求，数据: {}", registerQuery);

        if(!EmailUtil.isValidEmail(registerQuery.getEmail()))
            return Result.error(EMAIL_ERROR);
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

        // 验证码比对
        if (!registerQuery.getCode().equals(storedCode)) {
            return Result.error(EMAIL_CODE_ERROR);
        }

        if(!registerQuery.getEmail().equals((String) session.getAttribute("Email"))) {
            return Result.error(EMAIL_ERROR);
        }

        try {
            // 调用service注册用户
            boolean success = userService.register(registerQuery);
            if (success) {
                // 注册成功后清除验证码
                session.removeAttribute("email_code");
                session.removeAttribute("Email");
                // 确保设置新的session id
                response.setHeader("Set-Cookie", "JSESSIONID=" + session.getId() + "; Path=/; HttpOnly; SameSite=None; Secure");
                return Result.success(null);
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

    /**
     * 微信登录
     * @param wxLoginQuery 获取临时凭证code
     * @param response
     * @return 返回执行结果

     */
    @PostMapping("/wechat_login")
    public Result wechatLogin(@RequestBody WxLoginQuery wxLoginQuery, HttpServletResponse response) {
        log.info("[调试] 收到微信登录请求, code: {}", wxLoginQuery.getCode());
        try {
            Map<String, Object> resultMap = userService.checkLogin(wxLoginQuery.getCode());
            if (resultMap.containsKey("user")) {
                // 将User对象正确转换
                User user = (User) resultMap.get("user");
                // 使用统一的token生成方法，用openid作为标识符
                String token = generateUserToken(
                        user.getId(),
                        user.getWxOpenid()
                );

                response.setHeader(JWTUtils.header, token);
                resultMap.put("token", token);
                return Result.success(resultMap.get("user"));
            } else {
                return Result.error(WECHAT_LOGIN_ERROR);
            }
        } catch (Exception e) {
            log.error("[调试] 微信登录异常", e);
            return Result.error(WECHAT_LOGIN_ERROR);
        }
    }

    /**
    * 忘记密码页面的相关操作，包括验证验证码和重置密码
    * */
    @PostMapping("/verify_code")
    public Result verifyForgetCode(@RequestBody VerifyCodeQuery requestData,
                                   HttpServletRequest request) {
        log.info("[调试] 收到验证码验证请求: {}", requestData);

        if(!EmailUtil.isValidEmail(requestData.getEmail()))
            return Result.error(EMAIL_ERROR);
        String email = requestData.getEmail();
        String code = requestData.getCode();

        // 参数校验
        if (StrUtil.isBlank(email) || StrUtil.isBlank(code)) {
            return Result.error(PARAM_ERROR);
        }

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

        // 验证码比对
        if (!code.equals(storedCode)) {
            return Result.error(EMAIL_TIME_OUT);
        }

        if(!email.equals((String) session.getAttribute("Email"))){
            return Result.error(EMAIL_ERROR);
        }

        // 验证通过后将邮箱存入session用于重置密码时验证
        session.setAttribute("reset_email", email);

        return Result.success(null);
    }

    @PostMapping("/reset_password")
    public Result resetPassword(@RequestBody RePwdQuery requestData,
                                HttpServletRequest request) {
        log.info("[调试] 收到重置密码请求: {}", requestData);

        String newPassword = requestData.getPassword();
        if (StrUtil.isBlank(newPassword)) {
            return Result.error(USER_PASSWORD_ERROR);
        }

        HttpSession session = request.getSession(false);
        if (session == null) {
            return Result.error(PAGE_TIMEOUT);
        }

        String email = (String) session.getAttribute("reset_email");
        if (StrUtil.isBlank(email)) {
            return Result.error(PAGE_TIMEOUT);
        }

        try {
            boolean success = userService.resetPassword(email, newPassword);
            if (success) {
                // 清除session中的验证信息
                session.removeAttribute("email_code");
                session.removeAttribute("reset_email");
                return Result.success(null);
            } else {
                return Result.error(RESET_PASSWORD_ERROR);
            }
        } catch (CustomException e) {
            return Result.error(e.getCode(), e.getMessage());
        }
    }

    @PostMapping("/reset_account")
    public Result resetAccount(@RequestBody ResetAccountQuery requestData,@RequestHeader("Authorization")String token) {
        log.info("[调试] 收到重置账号请求: {}", requestData);

        if (StrUtil.isBlank(requestData.getAccount())) {
            return Result.error(PARAM_ERROR);
        }

        Map<String,Object> claims=JWTUtils.getClaims(token);

        try {
            boolean success = userService.resetAccount(requestData.getAccount(), (Long) claims.get("id"));
            if (success) {
                return Result.success(null);
            } else {
                return Result.error(RESET_ACCOUNT_ERROR);
            }
        } catch (CustomException e) {
            return Result.error(e.getCode(), e.getMessage());
        }
    }

    /**
     * Token生成的统一方法
     */
    private String generateUserToken(Long userId, String identifier) {
        Map<String, Object> claims = new HashMap<>();
        claims.put("id", userId);
        claims.put("identifier", identifier != null ? identifier : ""); // 统一标识符，可以是account或openid
        claims.put("loginTime", System.currentTimeMillis());
        return JWTUtils.getToken(claims);
    }
    @PutMapping("/update")
    public Result update(@RequestBody UserUpdateQuery userUpdateQuery, @RequestHeader("Authorization") String token)
    {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        long id= (long) claims.get("id");
        userService.updateUserProfile(userUpdateQuery,id);
        return Result.success(UPDATE_SUCCESS);
    }

    @PostMapping("/avatar_update")
    public Result avatarUpdate(MultipartFile file, @RequestHeader(name="Authorization") String token) throws IOException {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        long id= (long) claims.get("id");
        FileUploadVo fileUploadVo = new FileUploadVo( userService.updateAvatar(file,id));
        if (fileUploadVo!= null) {
            return Result.success(fileUploadVo);
        } else {
            return Result.error(FILE_CREATE_ERROR);
        }
    }


}