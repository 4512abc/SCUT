package org.example.model.vo.HomeVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;


@Data
public class HomeChallengeRankVo {
    @JsonProperty("user_account")
    private String userAccount;
    @JsonProperty("avatar")
    private String avatar;
    @JsonProperty("number")
    private Integer number;
    @JsonProperty("user_id")
    private String userId;

    public HomeChallengeRankVo(String account, String avatar, Integer number, String string) {
        this.userAccount = account;
        this.avatar = avatar;
        this.number = number;
        this.userId = string;

    }
}
