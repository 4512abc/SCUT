package org.example.model.vo.SearchInfoVo;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.example.model.entity.User;

import java.math.BigInteger;
import java.sql.Timestamp;
import java.util.Date;

@Data
public class SearchUserVo {
    private String avatar;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date createTime;
    private String email;
    private String userAccount;
    private long userId;
    private String userState;

    public SearchUserVo(User user) {
        this.avatar = user.getAvatar();
        this.createTime = user.getCreateTime();
        this.email = user.getEmail();
        this.userAccount = user.getAccount();
        this.userId = user.getId();
        this.userState = user.getStatus();
    }


}
