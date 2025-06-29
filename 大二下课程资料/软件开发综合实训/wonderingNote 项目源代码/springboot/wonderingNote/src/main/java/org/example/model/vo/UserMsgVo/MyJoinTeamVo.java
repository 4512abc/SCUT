package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;

import java.util.Date;

/**
 * @Author: fs
 * @Date: 2025/4/2422:21
 */
import lombok.Data;

@Data
public class MyJoinTeamVo {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("name")
    private String name;
    @JsonProperty("logo")
    private String logo;
    @JsonProperty("creator_id")     // 与文档字段creator_id保持命名一致
    private Long creatorId;         // 创建者ID（对应文档字段：creator_id）

    @JsonProperty("max_members")    // 与文档字段max_members保持命名一致
    private Integer maxMembers;     // 最大成员数（对应文档字段：max_members）

    @JsonProperty("create_time")    // 与文档字段create_time保持命名一致
    private Date createTime;      // 创建时间（ISO8601格式字符串）
    @JsonProperty("type")
    private Integer type;


}
