package org.example.model.vo.SearchInfoVo;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.example.model.entity.Challenge;
import org.example.model.utils.Location;
import org.example.utils.FileUrlUtil;

import java.util.Date;

@Data
public class TeamChallengeListVo {
    private String cover;
    private String creatorAccount;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date endTime;
    private String gestureType;
    private long id;
    private String landmarkName;
    private Location location;
    private String objectType;
    private String participants;
    private String title;
    private Long creatorId;

    public TeamChallengeListVo(Challenge challenge, String creatorAccount) {
        this.cover = FileUrlUtil.getFirstFileFromJsonArray(challenge.getImages());
        this.creatorAccount = creatorAccount;
        this.endTime = challenge.getEndTime();
        this.gestureType = challenge.getGestureType();
        this.id = challenge.getId();
        this.landmarkName = challenge.getLandmarkName();
        this.location = Location.fromBytes(challenge.getLocation());
        this.objectType = challenge.getObjectType();
        this.participants = challenge.getParticipants();
        this.title = challenge.getTitle();
        this.creatorId = challenge.getCreatorId();
    }
}
