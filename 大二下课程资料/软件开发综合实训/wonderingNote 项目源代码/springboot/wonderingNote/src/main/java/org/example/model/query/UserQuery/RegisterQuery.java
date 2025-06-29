package org.example.model.query.UserQuery;

/**
 * 用户注册请求参数封装
 * 对应接口：POST /api/auth/register
 */
public class RegisterQuery {


    private String email;
    private String password;
    private String code;

    // Getter and Setter 方法

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    @Override
    public String toString() {
        return "RegisterQuery{" +
                "email='" + email + '\'' +
                ", password='[PROTECTED]'" +
                ", code='[PROTECTED]'" +
                '}';
    }
}