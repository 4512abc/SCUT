package org.example.model.vo.HallVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Data;

import java.util.Date;

/**
 * @Author: fs
 * @Date: 2025/5/4 11:22
 */
@Data
public class ChallengeSearchVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("cover")
    private String cover;
    @JsonProperty("title")
    private String title;
    @JsonProperty("create_id")
    private Long createId;
    @JsonProperty("created_time")
    private Date createdTime;
    @JsonProperty("count")
    private Integer count;
}
