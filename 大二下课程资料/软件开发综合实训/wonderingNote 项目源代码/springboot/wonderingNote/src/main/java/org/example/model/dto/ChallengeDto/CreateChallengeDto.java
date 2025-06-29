package org.example.model.dto.ChallengeDto;

import cn.hutool.core.date.DateTime;
import lombok.Data;
import org.example.model.utils.Location;

@Data
public class CreateChallengeDto {
    private Long creator_id;
    private String description;
    private DateTime end_time;
    private String gesture_type;
    private String images;
    private String landmark_name;
    private Location location;
    private String object_type;
    private double radius;
    private DateTime start_time;
    private Long team_id;
    private String title;
}
