package org.example.model.vo.NotificationVo;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class MoreCommentListVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("parent_id")
    private Long parentId;
    @JsonProperty("parent_userid")
    private Long parentUserId;
    @JsonProperty("parent_account")
    private String parentAccount;
    @JsonProperty("user_id")
    private Long userId;
    @JsonProperty("account")
    private String account;
    @JsonProperty("avater")
    private String avatar;
    @JsonProperty("content")
    private String content;
    @JsonProperty("parent_content")
    private String parentContent;


}
