package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.model.entity.Like;
import java.util.List;
import java.util.Map;

public interface LikeMapper {
//    TOTORO
    List<Like> selectByIds(@Param("ids") List<Long> ids);

    Like selectByUserIdAndPostId(@Param("userId") Long userId, @Param("postId") Long postId);

    int deleteByPrimaryKey(Long id);

    int insert(Like row);

    int insertSelective(Like row);

    Like selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(Like row);

    int updateByPrimaryKey(Like row);

//    查询我的点赞所需要的查询函数
//    由TOTORO编辑
    List<Like> selectLikedPostsByUserId(@Param("params") Map<String, Object> params);
//由TOTORO编辑
    List<Like> selectByTargetIdAndType(@Param("targetId") Long targetId,
                                       @Param("targetType") String targetType);
    //由TOTORO编辑
    int deleteByIds(@Param("ids") List<Long> ids);

    /**
     * 根据 target_id 和 target_type 统计记录数
     * @param targetId 目标ID
     * @param targetType 目标类型
     * @return 符合条件的记录数
     */
    int countByTargetIdAndType(@Param("targetId") Long targetId, @Param("targetType") String targetType);

}