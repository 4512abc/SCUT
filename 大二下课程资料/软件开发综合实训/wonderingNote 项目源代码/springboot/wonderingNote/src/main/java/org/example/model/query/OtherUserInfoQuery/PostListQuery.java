package org.example.model.query.OtherUserInfoQuery;// PostListQuery.java
import lombok.Data;

@Data
public class PostListQuery {
    private Integer size ;
    private String sort ;
    private String LastCursor;
}
