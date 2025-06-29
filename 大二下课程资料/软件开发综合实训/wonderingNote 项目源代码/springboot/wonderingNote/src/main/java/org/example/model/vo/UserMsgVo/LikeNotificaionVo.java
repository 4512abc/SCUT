package org.example.model.vo.UserMsgVo;

import java.util.Date;

/**
 * 点赞通知的视图对象
 */
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class LikeNotificaionVo {
    @JsonProperty("user_id")
    private Long userId; // 点赞用户ID
    @JsonProperty("account")
    private String account; // 点赞用户账号
    @JsonProperty("post_id")
    private Long postId; // 被点赞的博文ID
    @JsonProperty("created_time")
    private Date createdTime; // 点赞时间
    @JsonProperty("title")
    private String title; // 博文标题
    @JsonProperty("is_read")
    private Boolean isRead; // 是否已读
    @JsonProperty("cover")
    private String cover; // 头像
    @JsonProperty("id")
    private Long id; // 头像

}