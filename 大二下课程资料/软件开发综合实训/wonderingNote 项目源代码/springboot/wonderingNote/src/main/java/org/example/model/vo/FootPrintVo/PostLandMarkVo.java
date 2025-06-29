package org.example.model.vo.FootPrintVo;
import java.util.Date;
import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import org.example.model.utils.Location;
/**
 * 博文信息VO
 * 对应接口：GET /api/auth/posts_info
 */
import lombok.Data;

@Data
public class PostLandMarkVo {
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

    @JsonProperty("is_public")
    private Boolean isPublic;
    // ------------------------ 嵌套类：位置信息 ------------------------



}