package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.model.entity.Post;
import org.example.model.entity.PostWithBLOBs;
import org.example.model.vo.HomeVo.HomeMonthDataVo;
import org.springframework.stereotype.Repository;

import java.util.Date;
import java.sql.Timestamp;
import java.util.List;
import java.util.Map;

@Repository
public interface PostMapper {

    int deleteByPrimaryKey(Long id);

    int insert(PostWithBLOBs row);
    //由TOTORO进行了自增和地址处理！！！
    int insertSelective(PostWithBLOBs row);

    PostWithBLOBs selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(PostWithBLOBs row);

    int updateByPrimaryKeyWithBLOBs(PostWithBLOBs row);

    int updateByPrimaryKey(Post row);

//   用来获取用户博文列表，使用游标分页！！！
//     由TOTORO编辑
    List<PostWithBLOBs> selectPostsWithBLOBs(@Param("params") Map<String, Object> params);
//TOTORO
    List<PostWithBLOBs> selectPostsWithBLOBs_1(@Param("params") Map<String, Object> params);
//TOTORO
List<PostWithBLOBs>selectPostsWithBLOBsbyLandmarkName(@Param("params") Map<String, Object> params);

//TOTORO
List<PostWithBLOBs>selectOtherPostsWithBLOBsbyLandmarkName(@Param("params") Map<String, Object> params);

    //根据博文id查询博文
//    由TOTORO编辑
    PostWithBLOBs selectPostWithBLOBsById(@Param("id") Long id);
//
//    由TOTORO编辑
    List<Post> selectByIds(@Param("ids") List<Long> ids);
//TOTORO
//    查地标博文
List<PostWithBLOBs> selectLandmarkPostsWithBLOBs(@Param("params") Map<String, Object> params);
    // 新增方法
    int selectPostTotal();
    int selectPostAddToday(@Param("date") Date date);

    List<HomeMonthDataVo> selectMonthlyPostAndChallengeCount();

    Integer selectUserLikeCount(@Param("userId") Long userId);
    Integer selectUserCommentCount(@Param("userId") Long userId);
    /**
     * 根据用户id获取用户发布的博文数量
     * @param userId 用户ID
     * @return 符合条件的博文数量
     */
    Integer selectUserPostCount(@Param("userId") Long userId);
    /**
     * 根据标题和创建时间范围检索帖子
     * @param title 模糊搜索的标题关键字
     * @param startTime 创建时间范围的起始时间
     * @param endTime 创建时间范围的结束时间
     * @return 符合条件的帖子列表
     */
    List<PostWithBLOBs> selectByTitleAndCreateTimeRange(
            @Param("title") String title,
            @Param("startTime") java.util.Date startTime,
            @Param("endTime") java.util.Date endTime
    );
    List<PostWithBLOBs>  selectByTitleAndCreateTimeRange(@Param("params") Map<String, Object> params);

    List<PostWithBLOBs>  selectByTitleAndCreateTimeRange_1(@Param("params") Map<String, Object> params);

    List<PostWithBLOBs>  selectByTitleAndCreateTimeRange_2(@Param("params") Map<String, Object> params);

}