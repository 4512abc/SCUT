package org.example.model.vo.UserInfoLastVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Data;

@Data
public class UserInfoLastSetVo {
    @JsonProperty("user_state")
    private String userState;

    public UserInfoLastSetVo(String userState) {
        this.userState = userState;
    }
}