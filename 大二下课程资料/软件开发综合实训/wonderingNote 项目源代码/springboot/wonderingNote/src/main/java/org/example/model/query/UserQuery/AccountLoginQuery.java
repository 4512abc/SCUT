package org.example.model.query.UserQuery;

import lombok.Data;

/**
 * 账号登录请求参数封装
 * 对应接口：POST /api/auth/account_login
 */
@Data
public class AccountLoginQuery {
    private String account;     // 用户名或邮箱
    private String password;    // 密码
    private String loginType;   // 登录类型：'email' 或 'username'

    public String getAccount() {
        return account;
    }

    public void setAccount(String account) {
        this.account = account;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getLoginType() {
        return loginType;
    }

    public void setLoginType(String loginType) {
        this.loginType = loginType;
    }

    @Override
    public String toString() {
        return "AccountLoginQuery{" +
                "account='" + account + '\'' +
                ", password='[PROTECTED]'" ;
    }
}