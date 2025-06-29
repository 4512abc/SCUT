package org.example.model.vo.HallVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

import java.util.Date;

/**
 * @Author: fs
 * @Date: 2025/5/4 11:22
 */
@Data
public class PostSearchVo {
    @JsonProperty("id")
    private Long id;

    @JsonProperty("title")
    private String title;

    @JsonProperty("cover")
    private String cover;

    @JsonProperty("view_count")
    private Integer viewCount;

    @JsonProperty("like_count")
    private Integer likeCount;

    @JsonProperty("comment_count")
    private Integer commentCount;

    @JsonProperty("created_time")
    private Date createTime;


    @JsonProperty("landmark_name")
    private String landmarkName;

    @JsonProperty("user_id")
    private Long userId;

    @JsonProperty("user_account")
    private String userAccount;

    @JsonProperty("user_avatar")
    private String userAvatar;

    @JsonProperty("is_public")
    private Boolean isPublic;

    @JsonProperty("is_video")
    private Boolean is_video;
}
