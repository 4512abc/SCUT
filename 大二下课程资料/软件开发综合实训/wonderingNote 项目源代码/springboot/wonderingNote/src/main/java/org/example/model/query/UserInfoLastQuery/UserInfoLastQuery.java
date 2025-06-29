package org.example.model.query.UserInfoLastQuery;

/**
 * @Author: fs
 * @Date: 2025/4/2415:28
 */
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class UserInfoLastQuery {
    @JsonProperty("user_state")
    private String userState;
}
