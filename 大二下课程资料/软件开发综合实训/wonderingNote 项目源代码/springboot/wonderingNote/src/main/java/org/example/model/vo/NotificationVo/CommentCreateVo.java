package org.example.model.vo.NotificationVo;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class CommentCreateVo {
    @JsonProperty("comment_id")
    private Long commentId;
    @JsonProperty("content")
    private String content;
    @JsonProperty("status")
    private boolean status;

}
