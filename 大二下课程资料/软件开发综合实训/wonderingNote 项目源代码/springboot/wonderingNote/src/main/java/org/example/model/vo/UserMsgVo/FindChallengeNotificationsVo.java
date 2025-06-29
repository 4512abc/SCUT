package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

@Data
public class FindChallengeNotificationsVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("content")
    private String content;
    @JsonProperty("create_time")
    private Date createTime;
    public FindChallengeNotificationsVo(Long id, String content, Date createTime){
        this.id = id;
        this.content = content;
        this.createTime = createTime;
    }
}
