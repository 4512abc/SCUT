package org.example.model.vo.OtherUserInfoVo;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import org.example.model.utils.Location;

import java.util.Date;
// PostListVo.java
import lombok.Data;

@Data
public class PostListVo {
    @JsonProperty("id")
    private Long id;

    @JsonProperty("cover")
    private String cover;

    @JsonProperty("title")
    private String title;

    @JsonProperty("view_count")
    private Integer viewCount;

    @JsonProperty("like_count")
    private Integer likeCount;

    @JsonProperty("comment_count")
    private Integer commentCount;

    @JsonProperty("create_time")
    private Date createTime;

    @JsonProperty("location")
    private Location location;

    @JsonProperty("landmark_name")
    private String landmarkName;

    // Getters & Setters
}


