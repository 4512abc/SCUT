package org.example.service;


import cn.hutool.crypto.SecureUtil;
import com.google.gson.Gson;
import org.example.common.result.Result;
import org.example.exception.CustomException;
import org.example.mapper.UserMapper;
import org.example.mapper.UserProfileMapper;
import org.example.model.dto.FileInfoDto.FileInfoDto;
import org.example.model.dto.FileInfoDto.FileUpLoadDto;
import org.example.model.dto.UserUpdateDto.ResetPwdDto;
import org.example.model.entity.User;
import org.example.model.entity.UserProfile;
import org.example.model.query.UserQuery.AccountLoginQuery;
import org.example.model.dto.UserDto.AccountLoginDto;
import org.example.model.query.UserQuery.RegisterQuery;
import org.example.model.dto.UserDto.WxLoginDto;
import org.example.model.query.UserQuery.ResetAccountQuery;
import org.example.model.query.UserUpdateQuery.ResetPwdQuery;
import org.example.model.query.UserUpdateQuery.UserUpdateQuery;
import org.example.model.vo.FileInfoVo.FileUploadVo;
import org.example.utils.EmailUtil;
import org.example.utils.FileUrlUtil;
import org.example.utils.JWTUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.io.IOException;
import java.util.*;

import lombok.extern.slf4j.Slf4j;
import org.springframework.web.multipart.MultipartFile;

import static org.example.common.result.ResultCode.*;


/**
 * description: 用户信息业务层实现类
 **/

@Service
@Slf4j
public class UserService {
    @Autowired
    private UserMapper userMapper;


    @Value("${APPID}")
    private String appid;

    @Value("${APPSECRET}")
    private String appsecret;

    @Autowired
    private RestTemplate restTemplate;

    // 用于存储用户信息和token
    Map<String,Object> map = new HashMap<>();

    @Autowired
    private UserProfileMapper userProfileMapper;

    @Autowired
    private FileInfoService fileInfoService;

    public ResetPwdDto resetPwdUpdateQuery(ResetPwdQuery resetPwdQuery){
        User user=userMapper.selectByAccount(resetPwdQuery.getAccount());
        ResetPwdDto resetPwdDto=new ResetPwdDto();
        BeanUtils.copyProperties(user,resetPwdDto);
        if(user==null)
            throw new CustomException(USER_NOT_EXIST_ERROR);
        if(user.getEmail().equals(resetPwdQuery.getEmail())){
            user.setPassword(SecureUtil.md5(resetPwdQuery.getNewPwd()));
            userMapper.updateByPrimaryKeySelective(user);
            return resetPwdDto;
        }
        else
            throw new CustomException(EMAIL_ERROR);
    }

    public void updateUserProfile(UserUpdateQuery userUpdateQuery, long id){
        UserProfile userProfile=userProfileMapper.selectByPrimaryKey(id);
        if(userProfile==null){
            userProfile=new UserProfile();
            userProfile.setUserId(id);
            userProfile.setBio(userUpdateQuery.getBio());
            userProfile.setBirthday(userUpdateQuery.getBirthday());
            userProfile.setGender(userUpdateQuery.getGender());
            userProfile.setLocation(userUpdateQuery.getLocation());
            userProfile.setSettings(userUpdateQuery.getSettings());
            userProfileMapper.insert(userProfile);
        }
        else{
            userProfile.setUserId(id);
            userProfile.setBio(userUpdateQuery.getBio());
            userProfile.setBirthday(userUpdateQuery.getBirthday());
            userProfile.setGender(userUpdateQuery.getGender());
            userProfile.setLocation(userUpdateQuery.getLocation());
            userProfile.setSettings(userUpdateQuery.getSettings());
            userProfileMapper.updateByPrimaryKeySelective(userProfile);
        }


    }

    public FileUpLoadDto updateAvatar(MultipartFile file, Long id) throws IOException {
        FileUpLoadDto fileUpLoadDto=fileInfoService.add(file);

        if(fileUpLoadDto==null)
            throw new CustomException(USER_NOT_EXIST_ERROR);

        User user=userMapper.selectByPrimaryKey(id);
        user.setAvatar(fileUpLoadDto.getFile_url());
        log.info("[调试] 用户头像更新成功"+fileUpLoadDto.getFile_url()+"用户id"+id);
//        userMapper.updateByPrimaryKeySelective(user);
        userMapper.updateByPrimaryKey(user);
        log.info("[调试] 用户头像更新成功"+user.getAvatar());
        return fileUpLoadDto;
    }

    public AccountLoginDto findByAccount(AccountLoginQuery accountLoginQuery) {
        log.info("[调试] 开始登录验证，登录类型：{}", accountLoginQuery.getLoginType());

        User user = null;
        // 根据登录类型查���用户
        if ("email".equals(accountLoginQuery.getLoginType())) {
            if(!EmailUtil.isValidEmail(accountLoginQuery.getAccount()))
                throw new CustomException(EMAIL_ERROR);
            user = userMapper.selectByEmail(accountLoginQuery.getAccount());
        } else if ("username".equals(accountLoginQuery.getLoginType())) {
            user = userMapper.selectByAccount(accountLoginQuery.getAccount());
        } else {
            throw new CustomException(INVAILD_LOGIN_TYPE);
        }

        // 用户不存在
        if (user == null) {
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }

        // 密码验证
        if (!Objects.equals(SecureUtil.md5(accountLoginQuery.getPassword()), user.getPassword())) {
            throw new CustomException(USER_PASSWORD_ERROR);
        }

        // 转换为DTO
        AccountLoginDto accountLoginDto = new AccountLoginDto();
        BeanUtils.copyProperties(user, accountLoginDto);
        return accountLoginDto;
    }

    public boolean register(RegisterQuery registerQuery) {
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
        user.setAccessLevel("user");

        log.info("[调试] 准备保存用户信息: {}", user);

        try {
            int result = userMapper.insertSelective(user);
            log.info("[调试] 用户注册结果: {}", result > 0 ? "成功" : "失败");
            return result > 0;
        } catch (Exception e) {
            log.error("[调试] 保存用户信息时发生异常", e);
            throw new CustomException("112", "注册失败，请稍后重试");
        }
    }

    /**
     * 登录验证
     * @param code 临时登录码
     * @return ·
     */
    public Map<String,Object> checkLogin(String code) {
        Map<String,Object> resultMap = new HashMap<>();

        try {
            // 构建微信服务器请求URL
            String url = String.format("https://api.weixin.qq.com/sns/jscode2session?appid=%s&secret=%s&js_code=%s&grant_type=authorization_code",
                    appid, appsecret, code);

            log.info("请求微信URL: {}", url);

            ResponseEntity<String> responseEntity = restTemplate.exchange(url, HttpMethod.GET, null, String.class);
            log.info("微信服务器响应: {}", responseEntity.getBody());

            if (responseEntity.getStatusCode() != HttpStatus.OK) {
                resultMap.put("errmsg", "微信服务器请求失败");
                log.error("微信服务器请求失败, 状态码: {}", responseEntity.getStatusCode());
                return resultMap;
            }

            // 解析响应数据
            WxLoginDto wxLoginDto = new Gson().fromJson(responseEntity.getBody(), WxLoginDto.class);
            log.info("解析后的微信登录信息: {}", wxLoginDto);

            if (wxLoginDto.getErrcode() != null && !wxLoginDto.getErrcode().equals("0")) {
                resultMap.put("errmsg", wxLoginDto.getErrmsg());
                log.warn("微信返回错误码: {}, 错误信息: {}", wxLoginDto.getErrcode(), wxLoginDto.getErrmsg());
                return resultMap;
            }

            String openid = wxLoginDto.getOpenid();
            if (openid == null || openid.isEmpty()) {
                resultMap.put("errmsg", "获取openid失败");
                log.error("openid为空，无法登录");
                return resultMap;
            }

            log.info("获取到的openid: {}", openid);

            // 查询用户
            User user = userMapper.selectByWxOpenid(openid);
            log.info("数据库中查询到的用户: {}", user);

            // 不存在则创建新用户
            // 用户不存在时创建新用户（关键修改开始）
            if (user == null) {
                user = new User();
                user.setWxOpenid(openid);

                // 改进账号生成算法
                String randomSuffix = String.format("%04d", new Random().nextInt(10000));
                user.setAccount("wx_" + openid.substring(openid.length()-8) + randomSuffix);

                user.setStatus("1");
                user.setCreateTime(new Date());
                user.setUpdateTime(new Date());
                user.setAccessLevel("user");

                // 使用insertSelective并获取回填ID
                int insertResult = userMapper.insertSelective(user);
                if (insertResult <= 0 || user.getId() == null) { // 检查主键回填
                    throw new CustomException(USER_CREATE_ERROR);
                }

                // 无需再次查询，直接使用回填对象
                log.info("新建用户ID: {}", user.getId());
            }
            // 关键修改结束

            // 生成token并返回结果
            Map<String, Object> claims = new HashMap<>();
            claims.put("id", user.getId());
            claims.put("openid", user.getWxOpenid());
            claims.put("loginType", "wechat");
            claims.put("loginTime", System.currentTimeMillis());
            String token = JWTUtils.getToken(claims);
            log.info("生成的token: {}", token);

            resultMap.put("user", user);
            resultMap.put("token", token);
            return resultMap;

        } catch (Exception e) {
            log.error("微信登录处理异常", e);
            resultMap.put("errmsg", "服务器内部错误");
            return resultMap;
        }
    }

    /**
     * 重置密码
     * @param email 邮箱
     * @param newPassword 新密码
     * @return 是否成功
     */
    public boolean resetPassword(String email, String newPassword) {
        log.info("[调试] 开始重置密码，邮箱: {}", email);

        // 查找用户
        User user = userMapper.selectByEmail(email);
        if (user == null) {
            log.error("[调试] 用户不存在，邮箱: {}", email);
            throw new CustomException("111", "用户不存在");
        }

        try {
            // 更新密码
            user.setPassword(SecureUtil.md5(newPassword));
            user.setUpdateTime(new Date());

            int result = userMapper.updateByPrimaryKeySelective(user);
            log.info("[调试] 密码重置结果: {}", result > 0 ? "成功" : "失败");

            return result > 0;
        } catch (Exception e) {
            log.error("[调试] 重置密码时发生异常", e);
            throw new CustomException("112", "重置密码失败，请稍后重试");
        }
    }

    public boolean resetAccount(String account,Long id) {
        // 查找用户
        User userTest = userMapper.selectByAccount(account);
        if (userTest != null) {
            throw new CustomException(USER_HAVE_ACCOUNT);
        }
        User user = userMapper.selectByPrimaryKey(id);
        try {
            // 更新密码
            user.setAccount(account);
            user.setUpdateTime(new Date());

            int result = userMapper.updateByPrimaryKeySelective(user);
            log.info("[调试]账号码重置结果: {}", result > 0 ? "成功" : "失败");

            return result > 0;
        } catch (Exception e) {
            log.error("[调试] 重置账号时发生异常", e);
            throw new CustomException(RESET_ACCOUNT_ERROR);
        }
    }

}
