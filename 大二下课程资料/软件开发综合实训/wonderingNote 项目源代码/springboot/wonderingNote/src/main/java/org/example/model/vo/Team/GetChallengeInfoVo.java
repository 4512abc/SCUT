package org.example.model.vo.Team;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import org.example.model.utils.Location;

import java.util.Date;

@Data
public class GetChallengeInfoVo {
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
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    @JsonProperty("end_time")
    private Date endTime;
    @JsonProperty("cover")
    private String cover;
    @JsonProperty("location")
    private Location location;
    @JsonProperty("created_id")
    private Long createdId;
    @JsonProperty("created_avatar")
    private String createdAvatar;
}
