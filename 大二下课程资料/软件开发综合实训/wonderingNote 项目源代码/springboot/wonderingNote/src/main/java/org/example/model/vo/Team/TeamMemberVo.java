package org.example.model.vo.Team;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

@Data
public class TeamMemberVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("user_account")
    private String userAccount;
    @JsonProperty("user_avatar")
    private String userAvatar;
    @JsonProperty("join_time")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date joinTime;
    @JsonProperty("update_time")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date updateTime;

}