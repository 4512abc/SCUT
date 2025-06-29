package org.example.model.query.UserMsgQuery;
import lombok.Data;

@Data
public class TeamInfoQuery {
    private Integer size;      // 分页大小
    private String LastCursor;     // 游标ID
    private String sort;       // 排序方式


}