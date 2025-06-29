package org.example.service;

import cn.hutool.crypto.SecureUtil;
import lombok.extern.slf4j.Slf4j;
import org.example.exception.CustomException;
import org.example.mapper.UserMapper;
import org.example.model.dto.AdminUserDto.AdminUserLoginDto;
import org.example.model.dto.UserDto.AccountLoginDto;
import org.example.model.entity.User;
import org.example.model.query.UserQuery.AccountLoginQuery;
import org.example.model.query.UserQuery.RegisterQuery;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Date;
import java.util.Objects;
import java.util.Random;

import static org.example.common.result.ResultCode.*;

@Slf4j
@Service
public class AdminUserService {

    @Autowired
    private UserMapper userMapper;
    public String register(RegisterQuery registerQuery) {
        // 创建管理员用户
        log.info("[调试] 开始注册用户");

        // 只检查邮箱是否已存在
        User existUserByEmail = userMapper.selectByEmail(registerQuery.getEmail());
        if (existUserByEmail != null) {
            log.info("[调试] 邮箱 {} 已被注册", registerQuery.getEmail());
            throw new CustomException("111", "该邮箱已被注册");
        }

        // 创建新用户对象
        User user = new User();
        // 生成随机账号
        String randomAccount = "user_" + System.currentTimeMillis()%10000
                + String.format("%04d", new Random().nextInt(10000));
        user.setAccount(randomAccount);
        user.setEmail(registerQuery.getEmail());
        String encodedPassword = SecureUtil.md5(registerQuery.getPassword());
        user.setPassword(encodedPassword);
        user.setCreateTime(new Date());
        user.setUpdateTime(new Date());
        user.setStatus("1");
        user.setAccessLevel("admin");

        log.info("[调试] 准备保存用户信息: {}", user);

        try {
            int result = userMapper.insertSelective(user);
            log.info("[调试] 用户注册结果: {}", result > 0 ? "成功" : "失败");
            if(result > 0)
                return user.getAccount();
            throw new CustomException("112", "注册失败，请稍后重试");
        } catch (Exception e) {
            log.error("[调试] 保存用户信息时发生异常", e);
            throw new CustomException("112", "注册失败，请稍后重试");
        }
    }

    public AdminUserLoginDto findByAccount(AccountLoginQuery accountLoginQuery) {
        log.info("[调试] 开始登录验证，登录类型：{}", accountLoginQuery.getLoginType());

        User user = null;
        // 根据登录类型查用户
        if ("email".equals(accountLoginQuery.getLoginType())) {
            user = userMapper.selectByEmail(accountLoginQuery.getAccount());
        } else if ("username".equals(accountLoginQuery.getLoginType())) {
            user = userMapper.selectByAccount(accountLoginQuery.getAccount());
        } else {
            throw new CustomException(PARAM_ERROR);
        }
        log.info("[调试] 查询到的用户信息: {}", user);

        // 用户不存在
        if (user == null) {
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }
        if(user.getAccessLevel().equals("user")){
            log.info("用户权限为：{}",user.getAccessLevel());
            throw new CustomException(USER_LEVEL_ERROR);
        }
        // 密码验证
        if (!Objects.equals(SecureUtil.md5(accountLoginQuery.getPassword()), user.getPassword())) {
            log.info("[调试] 密码错误"+SecureUtil.md5(accountLoginQuery.getPassword()));
            throw new CustomException(USER_PASSWORD_ERROR);
        }

        // 转换为DTO
        AdminUserLoginDto dto = new AdminUserLoginDto();
        BeanUtils.copyProperties(user, dto);
        return dto;
    }

    public void resetPassword(Long userId,String password) {
        log.info("[调试] 开始重置密码，用户ID: {}", userId);
        if (userId == null) {
            throw new CustomException(PARAM_ERROR);
        }
        if (password == null) {
            throw new CustomException(PARAM_ERROR);
        }
        try {
            User user = userMapper.selectByPrimaryKey(userId);
            if (user == null) {
                throw new CustomException(USER_NOT_EXIST_ERROR);
            }
            user.setPassword(SecureUtil.md5(password));
            userMapper.updateByPrimaryKeySelective(user);
            log.info("[调试] 重置密码成功，用户ID: {}", userId);
        } catch (Exception e) {
            log.error("[调试] 重置密码时发生异常", e);
        }

    }
}
