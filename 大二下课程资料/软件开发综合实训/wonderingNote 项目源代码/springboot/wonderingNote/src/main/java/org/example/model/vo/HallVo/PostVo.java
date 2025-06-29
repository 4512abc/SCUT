package org.example.model.vo.HallVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import org.example.model.utils.Location;

import java.util.Date;
import java.util.List;

@Data
public class PostVo {
    private List<Post> data;
    private String nextCursor;

    @Data
    public static class Post {
        @JsonProperty("id")
        private Long id;
        @JsonProperty("content")
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
        @JsonProperty("user_id")
        private Long userId;
        @JsonProperty("user_account")
        private String userAccount;
        @JsonProperty("user_avater")
        private String userAvatar;
        @JsonProperty("is_public")
        private Boolean isPublic;
        @JsonProperty("is_video")
        private Boolean is_video;
    }
}

