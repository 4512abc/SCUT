package org.example.model.query.UserQuery;

/**
 * 发送邮箱验证码请求参数封装
 * 对应接口：POST /api/auth/email_code
 */
public class EmailCodeQuery {

    private String email;

    // Getter and Setter 方法
    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public String toString() {
        return "EmailCodeQuery{" +
                "email='" + email + '\'' +
                '}';
    }
}