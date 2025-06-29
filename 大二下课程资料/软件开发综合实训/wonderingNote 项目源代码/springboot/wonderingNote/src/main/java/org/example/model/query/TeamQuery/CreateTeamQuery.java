package org.example.model.query.TeamQuery;

import lombok.Data;

@Data
public class CreateTeamQuery {
    private String name;
    private String logo;
    private Integer max_members
            ;
}
