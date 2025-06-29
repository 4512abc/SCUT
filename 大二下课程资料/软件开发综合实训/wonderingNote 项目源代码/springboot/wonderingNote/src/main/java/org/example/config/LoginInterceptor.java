//package org.example.config;
//
//import org.example.security.util.JWTutils;
//import org.springframework.stereotype.Component;
//import org.springframework.web.servlet.HandlerInterceptor;
//
//import javax.servlet.http.HttpServletRequest;
//import javax.servlet.http.HttpServletResponse;
//import java.util.Map;
//
//@Component
//public class LoginInterceptor implements HandlerInterceptor {
//
//    @Override
//    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
//        String token = request.getHeader("token");
//        try {
//            Map<String, Object> claims = JWTutils.parseToken(token);
//            return true;
//        } catch (Exception e) {
//            response.setStatus(401);
//            return false;
//        }
//    }
//}