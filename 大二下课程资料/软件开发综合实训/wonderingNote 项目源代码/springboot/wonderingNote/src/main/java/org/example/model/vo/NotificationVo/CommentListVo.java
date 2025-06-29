package org.example.model.vo.NotificationVo;

/**
 * @Author: fs
 * @Date: 2025/4/2301:37
 */
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class CommentListVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("user_id")
    private Long userId;
    @JsonProperty("account")
    private String account;
    @JsonProperty("avater")
    private String avatar;
    @JsonProperty("content")
    private String content;
    @JsonProperty("son_userid")
    private Long sonUserId;
    @JsonProperty("son_id")
    private Long sonId;
    @JsonProperty("son_account")
    private String sonAccount;
    @JsonProperty("son_avater")
    private String sonAvatar;
    @JsonProperty("son_content")
    private String sonContent;
    @JsonProperty("is_have")
    private Boolean isHave;


}
