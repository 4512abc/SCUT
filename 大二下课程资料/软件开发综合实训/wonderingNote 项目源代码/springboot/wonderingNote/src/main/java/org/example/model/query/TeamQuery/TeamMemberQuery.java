package org.example.model.query.TeamQuery;

import lombok.Data;

@Data
public class TeamMemberQuery {
    private Long teamId;
    private Integer size;
    private String lastCursor;
}