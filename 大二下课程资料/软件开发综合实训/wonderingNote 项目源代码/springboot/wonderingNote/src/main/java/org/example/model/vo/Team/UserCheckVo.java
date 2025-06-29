package org.example.model.vo.Team;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

@Data
public class UserCheckVo {
    @JsonProperty("user_id")
    private Long user_id;
    @JsonProperty("user_avatar")
    private String user_avatar;
    @JsonProperty("user_account")
    private String user_account;
    @JsonProperty("participant_record_id")
    private Long participant_record_id;
    @JsonProperty("complete_state")
    private String complete_state;
    @JsonProperty("evidence")
    private String evidence;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @JsonProperty("complete_time")
    private Date complete_time;
}
