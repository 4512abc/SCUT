package org.example.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

/**
 * 跨域配置类
 * 用于处理前端跨域请求访问后端接口的问题
 */
@Configuration
public class CorsConfig implements WebMvcConfigurer {

    /**
     * 配置全局跨域设置
     * @param registry CORS注册对象
     */
    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**") // 匹配所有路径
                .allowedOriginPatterns(
                        "http://localhost:*",    // 允许本地开发环境访问
                        "http://127.0.0.1:*",    // 允许本地IP访问
                        "https://*.weixin.qq.com", // 允许微信域名访问（用于微信登录）
                        "https://*.qq.com"        // 允许腾讯域名访问
                )
                .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS") // 允许的HTTP方法
                .allowedHeaders("*")         // 允许所有请求头
                .allowCredentials(true)      // 允许发送认证信息（cookies）
                .maxAge(3600);              // 预检请求的有效期，单位为秒
    }
}