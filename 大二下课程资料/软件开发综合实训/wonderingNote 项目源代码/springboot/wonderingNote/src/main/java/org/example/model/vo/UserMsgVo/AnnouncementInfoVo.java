package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.Date;
/**
 * 公告信息VO
 * 对应接口：GET /api/auth/announcement_info
 */
import lombok.Data;

@Data
public class AnnouncementInfoVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("title")
    private String title;

    @JsonProperty("update_time") // 确保与文档字段名一致
    private Date updateTime; // 使用Date类型便于处理

    @JsonProperty("type")
    private Integer type;
}