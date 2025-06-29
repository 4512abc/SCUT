package org.example.model.dto.UserDto;

import lombok.Data;
/**
 * 账号登录返回数据
 */
@Data
public class AccountLoginDto {
    private Long id;
    private String account;
    private String email;
    private String accessLevel;
    private String status;
    // 不要包含敏感信息如密码
}