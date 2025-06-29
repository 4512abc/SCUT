package org.example.model.vo.UserInfoLastVo;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class UserInfoLikeAndCommentVo {
    @JsonProperty("like_count")
    private Integer likeCount;
    @JsonProperty("comment_count")
    private Integer commentCount;

    public UserInfoLikeAndCommentVo(Integer likeCount, Integer commentCount) {
        this.likeCount = likeCount;
        this.commentCount = commentCount;
    }
}