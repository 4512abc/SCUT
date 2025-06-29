package org.example.model.query.OtherUserInfoQuery;

import javax.validation.constraints.NotNull;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
// UserInfoQuery.java
public class UserInfoQuery {
    @NotNull(message = "用户ID不能为空")
    @JsonProperty("user_id")
    private Long userId;


}
