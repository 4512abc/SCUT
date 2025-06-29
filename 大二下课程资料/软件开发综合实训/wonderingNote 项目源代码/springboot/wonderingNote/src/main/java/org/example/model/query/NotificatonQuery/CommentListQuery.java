package org.example.model.query.NotificatonQuery;
import lombok.Data;

@Data
public class CommentListQuery {
    private Long postId;
    private Integer size;
    private String sort;
    private String LastCursor;


}