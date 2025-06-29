package org.example.model.query.OtherUserInfoQuery;
import lombok.Data;

@Data
public class ChallengeListQuery {
    private Integer size;
    private String LastCursor;
    private String sort;


}