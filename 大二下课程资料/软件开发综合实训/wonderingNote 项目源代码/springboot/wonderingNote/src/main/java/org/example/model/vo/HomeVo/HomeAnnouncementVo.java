package org.example.model.vo.HomeVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.Date;

import lombok.Data;


@Data
public class HomeAnnouncementVo {
    @JsonProperty("announcement_id")
    private Long id;
    @JsonProperty("title")
    private String title;
    @JsonProperty("content")
    private String content;
    @JsonProperty("create_time")
    private Date createTime;
    @JsonProperty("update_time")
    private Date updateTime;

    public HomeAnnouncementVo(Long id, String title, String content, Date createTime, Date updateTime) {
        this.id = id;
        this.title = title;
        this.content = content;
        this.createTime = createTime;
        this.updateTime = updateTime;
    }
}
