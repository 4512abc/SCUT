// Request.java

package org.example.model.query.UserUpdateQuery;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;


import java.sql.Date;

/**
 * Request
 */
@Data
public class UserUpdateQuery {
    private String bio;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date birthday;
    private String gender;
    private String location;
    private String settings;

}