package org.example.model.vo.SearchInfoVo;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.example.model.entity.Team;

import java.util.Date;

@Data
public class SearchTeamVo {
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date createTime;
    private String createdUserAccount;
    private long createdUserId;
    private String logo;
    private String name;
    private long teamId;
    private Integer userNumber;

    public SearchTeamVo(Team team, String createdUseraccount,Integer userNumber)
    {
        this.createTime = team.getCreateTime();
        this.createdUserAccount = createdUseraccount;
        this.createdUserId = team.getCreatorId();
        this.logo = team.getLogo();
        this.name = team.getName();
        this.teamId = team.getId();
        this.userNumber = userNumber;
    }
}
