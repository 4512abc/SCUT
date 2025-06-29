package org.example.model.vo.NotificationVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Data;

@Data
public class AnnouncementIsreadVo {
    @JsonProperty("Announcement_id")
    private Long AnnouncementId;
}