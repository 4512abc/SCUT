package org.example.model.vo.HallVo;

import lombok.Data;
import org.example.model.entity.User;

@Data
public class UserSearchVo {
    private String email;
    private String avatar;
    private String user_account;
    private Long id;

    public UserSearchVo(User user) {
        this.email = user.getEmail();
        this.avatar = user.getAvatar();
        this.user_account = user.getAccount();
        this.id = user.getId();
    }
}
