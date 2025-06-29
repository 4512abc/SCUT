package org.example.model.query.UserUpdateQuery;

import lombok.Data;

@Data
public class ResetPwdQuery {
    private String email;
    private String emailCode;
    /**
     * 新密码
     */
    private String newPwd;
    /**
     * 重复输入
     */
    private String account;

}
