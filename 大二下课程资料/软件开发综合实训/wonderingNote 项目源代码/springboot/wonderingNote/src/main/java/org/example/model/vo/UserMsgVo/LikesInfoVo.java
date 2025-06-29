package org.example.model.vo.UserMsgVo;
import org.example.model.utils.Location;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.Date;
/**
 * 点赞信息VO
 * 对应接口：GET /api/auth/likes_info
 */
import lombok.Data;

@Data
public class LikesInfoVo {
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

    @JsonProperty("post_id")
    private Long postId;

}