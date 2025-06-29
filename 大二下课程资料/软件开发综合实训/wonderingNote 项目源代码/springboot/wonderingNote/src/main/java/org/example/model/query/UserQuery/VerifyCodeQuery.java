package org.example.model.query.UserQuery;

import lombok.Data;

@Data
public class VerifyCodeQuery {
    private String email;
    private String code;
}
