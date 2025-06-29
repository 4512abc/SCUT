package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.model.entity.TeamMember;
import org.example.model.entity.TeamMemberKey;
import org.example.utils.CursorPageUtil;

import java.util.List;
import java.util.Map;

public interface TeamMemberMapper {

    int deleteByPrimaryKey(TeamMemberKey key);

    int insert(TeamMember row);

    int insertSelective(TeamMember row);

    TeamMember selectByPrimaryKey(TeamMemberKey key);

    int updateByPrimaryKeySelective(TeamMember row);

    int updateByPrimaryKeyWithBLOBs(TeamMember row);

    int updateByPrimaryKey(TeamMember row);

    /**
     * 根据teamId查询所有记录，提取其中的userId为列表返回
     * @param teamId 团队ID
     * @return 用户ID列表
     */
    List<Long> selectUserIdsByTeamId(Long teamId);

    /**
     * 根据teamId分页查询成员
     * @param params 查询参数
     * @return 成员列表
     * 由TOTORO 编辑
     */
    List<TeamMember> selectByTeamId(Map<String, Object> params);

    /**
     * 根据用户ID分页查询群组成员信息
     * @param params 查询参数
     * @return 群组成员列表
     */
    //由TOTORO编辑！！！
    List<TeamMember> selectByUserId(@Param("params") Map<String, Object> params);

    /**
     * 根据teamId和userId联合查找记录
     * @param teamId 团队ID
     * @param userId 用户ID
     * @return TeamMember对象
     */
    TeamMember selectByTeamIdAndUserId(Long teamId, Long userId);
    /**
     * 根据teamId统计记录数量
     * @param teamId 团队ID
     * @return 记录数量
     */
    int countByTeamId(Long teamId);

}

