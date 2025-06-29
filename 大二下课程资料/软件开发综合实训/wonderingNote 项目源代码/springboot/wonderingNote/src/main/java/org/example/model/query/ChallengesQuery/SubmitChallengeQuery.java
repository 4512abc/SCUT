package org.example.model.query.ChallengesQuery;

import cn.hutool.core.date.DateTime;
import lombok.Data;
import org.example.model.utils.Location;

@Data
public class SubmitChallengeQuery {
    private String file_url;
    private Location location;
    private boolean isAi_verified;
}
