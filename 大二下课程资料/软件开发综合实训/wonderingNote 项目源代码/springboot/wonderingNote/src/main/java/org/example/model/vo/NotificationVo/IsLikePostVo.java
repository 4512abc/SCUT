package org.example.model.vo.NotificationVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Data;

@Data
public class IsLikePostVo {
    @JsonProperty("isLike")
    private Boolean isLike;

}
