package org.example.model.query.NotificatonQuery;

import lombok.Data;

@Data
public class MoreCommentListQuery {
    private Long rootId;
    private Integer size;
    private String sort;
    private String lastCursor;
}

