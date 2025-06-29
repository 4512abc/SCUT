package org.example.model.query.TeamQuery;

import lombok.Data;

@Data
public class UserCheckQuery {
    private Long challenge_id;
    private Integer size;
    private String lastCursor;
    private boolean need_notice;
}
