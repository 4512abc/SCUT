package org.example.model.dto.AdminUserDto;

import lombok.Data;

@Data
public class AdminUserLoginDto {
    private Long id;
    private String account;
    private String email;
    private String accessLevel;
    private String status;
}
