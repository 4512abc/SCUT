// Request.java

package org.example.model.vo.ChallengeVo;

import cn.hutool.core.date.DateTime;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import org.example.model.utils.Location;

import java.util.Date;
import java.time.OffsetDateTime;

@Data
public class ChallengeInfoVo {
    @JsonProperty("create_time")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date createTime;

    @JsonProperty("creator_id")
    private Long creatorid;

    private String description;

    @JsonProperty("end_time")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date endTime;

    @JsonProperty("gesture_type")
    private String gestureType;

    private String images;

    private Location location;

    @JsonProperty("object_type")
    private String objectType;

    private double radius;

    @JsonProperty("start_time")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date startTime;

    @JsonProperty("team_id")
    private Long teamid;

    private String title;

    @JsonProperty("landmark_name")
    private String LandmarkName;

    @JsonProperty("team_id")
    private Long TeamId;

    @JsonProperty("need_face_verify")
    private int NeedFaceVerify;

}