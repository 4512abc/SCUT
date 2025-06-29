package org.example.model.vo.SearchInfoVo;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.example.model.entity.Challenge;

import java.math.BigInteger;
import java.sql.Timestamp;
import java.util.Date;

@Data
public class SearchChallengeVo {
    private long challengeId;
    private long count;
    private String cover;
    private long createId;
    private String title;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date createTime;
    public SearchChallengeVo(Challenge challenge, long count){
        this.challengeId=challenge.getId();
        this.count=count;
        this.cover=challenge.getImages();
        this.createId=challenge.getCreatorId();
        this.createTime=challenge.getCreateTime();
        this.title=challenge.getTitle();
    }
}
