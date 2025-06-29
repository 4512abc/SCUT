package org.example.utils;

import com.auth0.jwt.JWT;
import com.auth0.jwt.JWTVerifier;
import com.auth0.jwt.algorithms.Algorithm;
import com.auth0.jwt.exceptions.JWTVerificationException;
import com.auth0.jwt.exceptions.TokenExpiredException;
import com.auth0.jwt.interfaces.DecodedJWT;
import lombok.Data;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;
import cn.hutool.core.util.StrUtil;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * JWT工具类，用于JWT的生成、验证和解析
 */
@Component
@Data
@ConfigurationProperties(prefix = "jwt")
@Slf4j
public class JWTUtils {
    // 定义token返回头部
    public static String header;

    // token前缀
    public static String tokenPrefix;

    // 签名密钥
    public static String secret;

    // 有效期
    public static long expireTime;

    /**
     * 使用claims创建token
     * @param claims 存放的用户信息
     * @return token字符串
     */
    public static String getToken(Map<String, Object> claims) {
        if (claims == null || claims.isEmpty()) {
            throw new IllegalArgumentException("Claims不能为空");
        }

        try {
            com.auth0.jwt.JWTCreator.Builder builder = JWT.create();

            // 添加所有claims
            claims.forEach((key, value) -> {
                if (value == null) {
                    builder.withClaim(key, "");  // 将null转为空字符串
                } else if (value instanceof String) {
                    builder.withClaim(key, (String) value);
                } else if (value instanceof Long) {
                    builder.withClaim(key, (Long) value);
                } else if (value instanceof Integer) {
                    builder.withClaim(key, (Integer) value);
                } else if (value instanceof Boolean) {
                    builder.withClaim(key, (Boolean) value);
                }
            });

            // 添加过期时间
            builder.withExpiresAt(new Date(System.currentTimeMillis() + expireTime));

            // 生成token
            return tokenPrefix + builder.sign(Algorithm.HMAC512(secret));
        } catch (Exception e) {
            log.error("[调试] 生成token失败", e);
            throw new RuntimeException("生成token失败");
        }
    }

    /**
     * 验证token是否有效
     * @param token JWT token字符串
     * @return 验证通过返回true，否则返回false
     */
    public static boolean validateToken(String token) {
        if (StrUtil.isBlank(token)) {
            return false;
        }
        try {
            parseToken(token);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    /**
     * 解析Token
     * @param token JWT token字符串
     * @return 解析后的JWT对象
     */
    public static DecodedJWT parseToken(String token) {
        if (StrUtil.isBlank(token)) {
            throw new RuntimeException("Token不能为空");
        }
        log.info("token:{}",token);

        try {
            String actualToken = token.replace(tokenPrefix, "");
            Algorithm algorithm = Algorithm.HMAC512(secret);
            JWTVerifier verifier = JWT.require(algorithm).build();
            return verifier.verify(actualToken);
        } catch (TokenExpiredException e) {
            log.info("[调试] Token已过期");
            throw new RuntimeException("Token已过期");
        } catch (JWTVerificationException e) {
            log.error("[调试] Token解析失败", e);
            throw new RuntimeException("Token解析失败");
        }
    }

    /**
     * 从Token中获取用户信息
     * @param token JWT token字符串
     * @return 包含用户信息的Map
     */
    public static Map<String, Object> getClaims(String token) {
        try {
            DecodedJWT jwt = parseToken(token);
            Map<String, Object> claims = new HashMap<>();
            jwt.getClaims().forEach((key, claim) -> {
                if (claim.asLong() != null) {
                    claims.put(key, claim.asLong());
                } else if (claim.asString() != null) {
                    claims.put(key, claim.asString());
                }
            });
            return claims;
        } catch (Exception e) {
            log.error("[调试] 获取Claims失败: {}", e.getMessage());
            throw new RuntimeException("获取Claims失败");
        }
    }

    /**
     * 检查token是否需要更新
     * @param token JWT token字符串
     * @return 如果需要更新返回true，否则返回false
     */
    public static boolean isNeedUpdate(String token) {
        try {
            DecodedJWT jwt = parseToken(token);
            Date expiresAt = jwt.getExpiresAt();
            // 如果剩余过期时间少于过期时长的一半时需要更新
            return (expiresAt.getTime() - System.currentTimeMillis()) < (expireTime >> 1);
        } catch (Exception e) {
            return true;
        }
    }

    // setter方法，用于注入配置属性
    public void setHeader(String header) {
        JWTUtils.header = header;
    }

    public void setTokenPrefix(String tokenPrefix) {
        JWTUtils.tokenPrefix = tokenPrefix;
    }

    public void setSecret(String secret) {
        JWTUtils.secret = secret;
    }

    public void setExpireTime(long expireTime) {
        JWTUtils.expireTime = expireTime;
    }
}