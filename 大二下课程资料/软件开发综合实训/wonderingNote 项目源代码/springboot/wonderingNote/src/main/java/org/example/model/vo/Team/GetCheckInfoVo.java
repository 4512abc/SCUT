package org.example.model.vo.Team;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

@Data
public class GetCheckInfoVo {
    @JsonProperty("complete_time")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date completeTime;
    @JsonProperty("complete_state")
    private Byte completeState;
    private String evidence;;
}
