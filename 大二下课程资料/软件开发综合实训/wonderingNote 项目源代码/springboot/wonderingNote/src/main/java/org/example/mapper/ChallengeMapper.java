package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.model.entity.Challenge;
import org.example.model.entity.PostWithBLOBs;
import org.example.model.vo.HomeVo.HomeMonthDataVo;
import org.springframework.stereotype.Repository;

import java.util.Date;
import java.util.List;
import java.util.Map;

@Repository
public interface ChallengeMapper {

    int deleteByPrimaryKey(Long id);


    int insert(Challenge row);

    int insertSelective(Challenge row);

    Challenge selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(Challenge row);

    int updateByPrimaryKeyWithBLOBs(Challenge row);

    int updateByPrimaryKey(Challenge row);
    List<Challenge> selectByTeamId(Long teamId);
    Challenge selectById(@Param("id") Long id);
    List<Challenge> selectByIds(@Param("ids") List<Long> ids);
    List<Challenge> selectByCreatorId(@Param("creatorId") Long creatorId);

    //    由TOTORO编写
    List<Challenge> selectChallengesByCreator(@Param("params") Map<String, Object> params);

    // 新增方法
    int selectChallengeTotal();
    int selectChallengeAddToday(@Param("date") Date date);

    List<HomeMonthDataVo> selectMonthlyPostAndChallengeCount();
    //TOTORO
    List<Challenge> selectUnfinishedChallenges(@Param("params") Map<String, Object> params);
    /**
     * 根据 title 和 create_time 范围进行检索
     * @param title 模糊搜索的标题
     * @param startTime 起始时间
     * @param endTime 结束时间
     * @return List<Challenge> 符合条件的挑战记录列表
     */
    List<Challenge> selectByTitleAndCreateTimeRange(
            @Param("title") String title,
            @Param("startTime") java.util.Date startTime,
            @Param("endTime") java.util.Date endTime
    );
    List<Challenge>  selectByTitleAndCreateTimeRange_1(@Param("params") Map<String, Object> params);


    /**
     * 根据用户id获取用户创建的挑战数量
     * @param creatorId 用户ID
     * @return 用户创建的挑战数量
     */
    Integer selectUserChallengeCount(@Param("creatorId") Long creatorId);


    List<Challenge> selectChallengesById(@Param("params") Map<String, Object> params);

    List<Challenge>  selectByTitleAndCreateTimeRange_2(@Param("params") Map<String, Object> params);
    List<Challenge> selectByTeamId_1(@Param("params") Map<String, Object> params);
}
