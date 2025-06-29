package org.example.model.vo.PostVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import org.example.model.utils.Location;

import java.util.Date;

/**
 * 完整的帖子信息返回结构
 */
@Data
public class PostInfoVo {

    @JsonProperty("initial_info")
    private InitialInfoVo initialInfo; // 必需初始信息

    @JsonProperty("post_list")
    private PostListVo postList; // 必需帖子列表

    @JsonProperty("details")
    private PostDetailsVo details; // 必需-详情
    /**
     * 数据主体结构
     */
    @Data
    public static class PostDataVo {
        @JsonProperty("initial_info")
        private InitialInfoVo initialInfo; // 必需初始信息

        @JsonProperty("post_list")
        private PostListVo postList; // 必需帖子列表

        @JsonProperty("details")
        private PostDetailsVo details; // 必需帖子详情

    }

    /**
     * 用户初始信息
     */
    @Data
    public static class InitialInfoVo {
        @JsonProperty("user_account")
        private Long userAccount; // 必需-用户账号(bignum)

        @JsonProperty("id")
        private String id; // 必需-用户昵称

        @JsonProperty("user_avatar")
        private String userAvatar; // 必需-用户头像
    }

    /**
     * 帖子列表信息
     */
    @Data
    public static class PostListVo {
        @JsonProperty("id")
        private Long postId; // 必需-帖子ID(bignum)

        @JsonProperty("cover")
        private String cover; // 必需-封面图

        @JsonProperty("title")
        private String title; // 必需-标题

        @JsonProperty("view_count")
        private Integer viewCount; // 必需-浏览次数

        @JsonProperty("like_count")
        private Integer likeCount; // 必需-点赞数

        @JsonProperty("comment_count")
        private Integer commentCount; // 必需-评论数

        @JsonProperty("create_time")
        private Date createTime; // 必需-创建时间

        @JsonProperty("location")
        private Location location; // 必需-位置

        @JsonProperty("landmark_name")
        private String landmarkName;

    }

    /**
     * 帖子详情内容
     */
    @Data
    public static class PostDetailsVo {
        @JsonProperty("content")
        private String content; // 必需-文本内容

        @JsonProperty("images")
        private String images; // 必需-图片集合(JSON字符串)

        @JsonProperty("videos")
        private String videos; // 必需-视频集合(JSON字符串)
    }
}