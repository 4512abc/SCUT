package org.example.model.vo.UserInfoLastVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class UserCommentPostVo {
    @JsonProperty("my_id")
    private Long myId;
    @JsonProperty("id")
    private Long id;
    @JsonProperty("post_id")
    private Long postId;
    @JsonProperty("post_content")
    private String postContent;
    @JsonProperty("cover")
    private String cover;
    @JsonProperty("title")
    private String title;
    @JsonProperty("user_account")
    private String userAccount;
    @JsonProperty("user_id")
    private Long userId;
    @JsonProperty("user_avater")
    private String userAvatar;
    @JsonProperty("content")
    private String content;
    @JsonProperty("parent_id")
    private Long parentId;
    @JsonProperty("parent_userid")
    private Long parentUserId;
    @JsonProperty("parent_useraccount")
    private String parentUserAccount;
    @JsonProperty("parent_content")
    private String parentContent;

}
