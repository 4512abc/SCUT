package org.example.model.vo.OtherUserInfoVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.Date;
import lombok.Data;
import org.example.model.utils.Location;

@Data
public class ChallengeListVo {
    @JsonProperty("id")
    private Long id;

    @JsonProperty("title")
    private String title;

    @JsonProperty("creator_account")
    private String creatorAccount;

    @JsonProperty("object_type")
    private String objectType;

    @JsonProperty("gesture_type")
    private String gestureType;

    @JsonProperty("landmark_name")
    private String landmarkName;

    @JsonProperty("participants")
    private String participants;

    @JsonProperty("end_time")
    private Date endTime;
    @JsonProperty("cover")
    private String cover;


    @JsonProperty("location")
    private Location location;


}