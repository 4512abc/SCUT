package org.example.model.query.FootPrintQuery;

/**
 * @Author: fs
 * @Date: 2025/4/2516:26
 */
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class OtherPostLandMarkQuery {
    private Integer size;
    // 分页大小
//    @JsonProperty("LastCursor") // JSON序列化使用
//    @Parameter(name = "LastCursor") // 兼容OpenAPI/Swagger
    private String LastCursor;

    private String sort;       // 排序方式
    @JsonProperty("landmark_name")
    private String landmarkName;
}
