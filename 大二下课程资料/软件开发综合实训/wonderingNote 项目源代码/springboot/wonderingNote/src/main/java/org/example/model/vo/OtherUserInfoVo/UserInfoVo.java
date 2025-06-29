package org.example.model.vo.OtherUserInfoVo;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.Date;
import lombok.Data;

@Data
// UserInfoVo.java
public class UserInfoVo {
    @JsonProperty("account")
    private String account;

    @JsonProperty("avatar")
    private String avatar;

    @JsonProperty("status")
    private String status;

    @JsonProperty("create_time")
    private Date createTime;

    @JsonProperty("update_time")
    private Date updateTime;

    @JsonProperty("bio")
    private String bio;

    @JsonProperty("gender")
    private String gender;

    @JsonProperty("birthday")
    private Date birthday;

    @JsonProperty("location")
    private String location;

    @JsonProperty("postCount")
    private Integer postCount;       // 用户博文数

    @JsonProperty("ChallengeCount")
    private Integer ChallengeCount;  // 用户参加挑战数

    @JsonProperty("CommentCount")
    private Integer CommentCount;    // 用户评论数;

    @JsonProperty("participantCount")
    private Integer participantCount;

    // Getters & Setters
}

