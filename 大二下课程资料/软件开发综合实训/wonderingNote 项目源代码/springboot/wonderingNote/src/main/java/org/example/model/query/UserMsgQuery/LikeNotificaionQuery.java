package org.example.model.query.UserMsgQuery;

import java.util.Map;

/**
 * 点赞通知的查询对象
 */
import lombok.Data;

@Data
public class LikeNotificaionQuery {
    private Integer size;      // 分页大小
    private String LastCursor;     // 游标ID
    private String sort;       // 排序方式
}