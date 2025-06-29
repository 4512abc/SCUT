package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.model.entity.Team;
import org.springframework.stereotype.Repository;

import java.util.Date;
import java.util.List;
import java.util.Map;

@Repository
public interface TeamMapper {
    int deleteByPrimaryKey(Long id);

    int insert(Team row);

    int insertSelective(Team row);

    Team selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(Team row);

    int updateByPrimaryKey(Team row);

    //获取群组信息接口，通过传递游标信息和用户id获取用户创建的接口！
    // 使用@Param（明确参数名为"params"）
    //TOTORO编辑
    List<Team> selectByParams(@Param("params") Map<String, Object> params);

    // 根据群组ID列表批量查询群组信息
    // 由TOTORO编辑
    List<Team> selectByIds(@Param("ids") List<Long> ids);

    /**
     * 根据name和create_time进行检索。
     * name支持模糊搜索，create_time支持范围时间搜索。
     *
     * @param name 模糊搜索的团队名称
     * @param startTime 起始时间
     * @param endTime 结束时间
     * @return 符合条件的团队列表
     */
    List<Team> selectByNameAndCreateTimeRange(@Param("name") String name, @Param("startTime") Date startTime, @Param("endTime") Date endTime);

}