package org.example.model.query.UserMsgQuery;

import com.fasterxml.jackson.annotation.JsonProperty;
import io.swagger.v3.oas.annotations.Parameter;
import lombok.Data;

@Data
public class PostsInfoQuery {
    private Integer size;
    // 分页大小
//    @JsonProperty("LastCursor") // JSON序列化使用
//    @Parameter(name = "LastCursor") // 兼容OpenAPI/Swagger
    private String LastCursor;

    private String sort;       // 排序方式



    // Getters & Setters

}