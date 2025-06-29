package org.example.model.query.ChallengesQuery;

import cn.hutool.core.date.DateTime;
import com.alibaba.druid.sql.ast.statement.SQLDropOutlineStatement;
import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.example.model.utils.Location;

import java.time.OffsetDateTime;
import java.util.Date;

@Data
public class CreateChallengeQuery {
        private String description;
        @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
        private Date end_time;
        private String gesture_type;
        private String images;
        private String landmark_name;
        private Location location;
        private String object_type;
        private double radius;
        @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
        private Date start_time;
        private Long team_id;
        private String title;
        private Byte need_face_verify;

}
