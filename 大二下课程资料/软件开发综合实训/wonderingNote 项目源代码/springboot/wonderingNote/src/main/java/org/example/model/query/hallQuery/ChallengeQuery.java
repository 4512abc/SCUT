package org.example.model.query.hallQuery;

import lombok.Data;

@Data
public class ChallengeQuery {
    private Integer size = 12; // 默认分页大小
    private String lastCursor; // 游标
    private String sort; // 排序方式
}