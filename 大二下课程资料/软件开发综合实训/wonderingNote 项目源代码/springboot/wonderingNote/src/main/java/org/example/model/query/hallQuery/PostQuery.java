package org.example.model.query.hallQuery;

import lombok.Data;

@Data
public class PostQuery {
    private Integer size = 12;
    private String sort;
    private String lastCursor;
}

