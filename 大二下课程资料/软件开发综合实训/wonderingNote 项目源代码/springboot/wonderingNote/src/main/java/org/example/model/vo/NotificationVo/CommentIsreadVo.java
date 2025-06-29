package org.example.model.vo.NotificationVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class CommentIsreadVo {
    @JsonProperty("post_id")
    private Long postId;
}