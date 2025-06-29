package org.example.model.dto.UserMsgDto;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.example.model.entity.PostWithBLOBs;

import java.io.IOException;
import java.util.Date;
import java.util.List;

public class PostsInfoDto {
    private Long id;
    private String cover;
    private String title;
    private Integer viewCount;
    private Integer likeCount;
    private Integer commentCount;
    private Date createTime;
    private LocationDto location;

    // 从PostWithBLOBs转换的方法
    public static PostsInfoDto fromEntity(PostWithBLOBs post) {
        PostsInfoDto dto = new PostsInfoDto();
        dto.setId(post.getId());
        dto.setTitle(post.getTitle());
        dto.setViewCount(post.getViewCount());
        dto.setLikeCount(post.getLikeCount());
        dto.setCommentCount(post.getCommentCount());
        dto.setCreateTime(post.getCreateTime());

        // 处理封面图片（从images JSON中获取第一张）
        dto.setCover(extractFirstImage(post.getImages()));

        // 处理位置信息
        dto.setLocation(parseLocation(post.getLocation()));

        return dto;
    }

    public static String extractFirstImage(String imagesJson) {
        if (imagesJson == null || imagesJson.isEmpty()) {
            return null;
        }
        try {
            ObjectMapper mapper = new ObjectMapper();
            List<String> images = mapper.readValue(imagesJson, new TypeReference<List<String>>() {});
            return images.isEmpty() ? null : images.get(0);
        } catch (IOException e) {
            return null;
        }
    }

    public static LocationDto parseLocation(byte[] locationBytes) {
        if (locationBytes == null || locationBytes.length == 0) {
            return null;
        }
        try {
            // 假设location存储的是JSON格式的经纬度
            String locationStr = new String(locationBytes);
            ObjectMapper mapper = new ObjectMapper();
            return mapper.readValue(locationStr, LocationDto.class);
        } catch (Exception e) {
            LocationDto location = new LocationDto();
            location.setLng("116.404"); // 默认值
            location.setLat("39.915");  // 默认值
            return location;
        }
    }

    // Getters and Setters
    public static class LocationDto {
        private String lng;
        private String lat;

        public String getLng() {
            return lng;
        }

        public void setLng(String lng) {
            this.lng = lng;
        }

        public String getLat() {
            return lat;
        }

        public void setLat(String lat) {
            this.lat = lat;
        }
    }

    // 其他getter/setter...
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getCover() {
        return cover;
    }

    public void setCover(String cover) {
        this.cover = cover;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public Integer getViewCount() {
        return viewCount;
    }

    public void setViewCount(Integer viewCount) {
        this.viewCount = viewCount;
    }

    public Integer getLikeCount() {
        return likeCount;
    }

    public void setLikeCount(Integer likeCount) {
        this.likeCount = likeCount;
    }

    public Integer getCommentCount() {
        return commentCount;
    }

    public void setCommentCount(Integer commentCount) {
        this.commentCount = commentCount;
    }

    public Date getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Date createTime) {
        this.createTime = createTime;
    }

    public LocationDto getLocation() {
        return location;
    }

    public void setLocation(LocationDto location) {
        this.location = location;
    }
}