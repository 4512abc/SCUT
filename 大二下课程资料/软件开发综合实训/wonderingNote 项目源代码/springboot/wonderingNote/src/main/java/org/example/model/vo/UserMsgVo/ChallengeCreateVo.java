package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import org.example.model.utils.Location;

import java.util.Date;
/**
 * 挑战信息VO
 * 严格对应接口：GET /api/auth/challenge_info
 */
@Data
public class ChallengeCreateVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("title")
    private String title;

    @JsonProperty("cover")
    private String cover;
    @JsonProperty("creator_account")
    private String creatorAccount;

    @JsonProperty("creator_id")
    private Long creatorId;

    @JsonProperty("object_type")
    private String objectType;

    @JsonProperty("gesture_type")
    private String gestureType;

    @JsonProperty("landmark_name") // 严格保持文档拼写
    private String landmarkName;

    @JsonProperty("location")
    private Location location;

    @JsonProperty("team_id") // 保持String类型与接口一致
    private Long teamId;

    @JsonProperty("participants")
    private String participants;

    @JsonProperty("end_time") // 保持String类型与接口一致
    private Date endTime;

    @JsonProperty("start_time") // 保持String类型与接口一致
    private Date startTime;

    @JsonProperty("create_time") // 保持String类型与接口一致
    private Date createTime;

    @JsonProperty("images")
    private String images;

    @JsonProperty("description")
    private String description;

    @JsonProperty("radius")
    private double radius;

}