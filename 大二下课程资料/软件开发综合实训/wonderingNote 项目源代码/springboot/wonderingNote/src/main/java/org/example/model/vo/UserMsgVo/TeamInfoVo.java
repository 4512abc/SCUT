package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.Date;
/**
 * 群组信息VO
 * 对应接口：GET /api/auth/team_info
 * 创建时间：2025-04-12
 * 最后修改：5天前
 */
import lombok.Data;

@Data
public class TeamInfoVo {
    @JsonProperty("id")
    private Long id;                // 群组ID（对应文档字段：id）
    @JsonProperty("name")
    private String name;            // 群组名称（对应文档字段：name）
    @JsonProperty("logo")
    private String logo;            // 群组头像（对应文档字段：logo）

    @JsonProperty("creator_id")     // 与文档字段creator_id保持命名一致
    private Long creatorId;         // 创建者ID（对应文档字段：creator_id）

    @JsonProperty("max_members")    // 与文档字段max_members保持命名一致
    private Integer maxMembers;     // 最大成员数（对应文档字段：max_members）

    @JsonProperty("create_time")    // 与文档字段create_time保持命名一致
    private Date createTime;      // 创建时间（ISO8601格式字符串）

}