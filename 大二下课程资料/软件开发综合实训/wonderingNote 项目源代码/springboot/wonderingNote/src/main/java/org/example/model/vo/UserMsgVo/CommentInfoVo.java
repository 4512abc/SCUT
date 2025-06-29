package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.Date;
/**
 * 评论通知信息VO
 * 对应接口：GET /api/auth/comment_info
 */
import lombok.Data;

@Data
public class CommentInfoVo {
    @JsonProperty("id")
    private Long id;

    @JsonProperty("post_id")
    private Long postId;

    @JsonProperty("parent_id")
    private Long parentId;

    @JsonProperty("content")
    private String content;

    @JsonProperty("like_count")
    private Integer likeCount;

    @JsonProperty("is_read")
    private Boolean isRead;

    @JsonProperty("created_time")
    private Date createdTime;

    @JsonProperty("user_id")
    private Long userId;
    @JsonProperty("avatar")
    String avatar;
    @JsonProperty("account")
    String account;
    @JsonProperty("title")
    String title;
}