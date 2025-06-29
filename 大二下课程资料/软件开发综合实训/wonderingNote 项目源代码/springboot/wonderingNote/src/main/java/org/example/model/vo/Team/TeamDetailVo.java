package org.example.model.vo.Team;

import java.util.Date;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class TeamDetailVo {
    @JsonProperty("name")
    private String name;
    @JsonProperty("logo")
    private String logo;
    @JsonProperty("creatorId")
    private Long creatorId;
    @JsonProperty("maxMembers")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Integer maxMembers;
    @JsonProperty("createTime")
    private Date createTime;
    @JsonProperty("membersCount")
    private Integer membersCount;
    @JsonProperty("challengeCount")
    private Integer challengeCount;
}
