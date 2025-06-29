package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.Date;
import lombok.Data;

import java.util.Date;

@Data
public class AnnouncementDataUserVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("title")
    private String title;
    @JsonProperty("update_time")
    private Date updateTime;
    @JsonProperty("is_read")
    private Boolean isRead;
    @JsonProperty("content")
    private String content;
    @JsonProperty("created_time")
    private Date createdTime;
    @JsonProperty("published_id")
    private Long publishedId;
}

