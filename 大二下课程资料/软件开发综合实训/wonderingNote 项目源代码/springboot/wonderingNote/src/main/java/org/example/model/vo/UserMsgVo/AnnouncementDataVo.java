package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.Date;
import lombok.Data;

@Data
public class AnnouncementDataVo {

    @JsonProperty("title")
    private String title;
    @JsonProperty("content")
    private String content;
    @JsonProperty("type")
    private Integer type;
    @JsonProperty("published_id")
    private Long publishedId;
    @JsonProperty("create_time")
    private Date createTime;
    @JsonProperty("update_time")
    private Date updateTime;
    @JsonProperty("user_avatar")
    private String userAvatar;
    @JsonProperty("user_account")
    private String userAccount;


}
