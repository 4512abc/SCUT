package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.model.entity.Comment;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Map;
import java.util.Set;

@Repository
public interface CommentMapper {

    int deleteByPrimaryKey(Long id);

    int insert(Comment row);

    int insertSelective(Comment row);

    Comment selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(Comment row);

    int updateByPrimaryKey(Comment row);
    // CommentMapper.java（正确修改）
    List<Comment> selectCommentsByIds(@Param("ids") Set<Long> ids); // 返回List类型

    List<Comment> selectRootCommentsByPostId(@Param("params") Map<String, Object> params);

    Comment selectFirstChildCommentByRootId(@Param("rootId") Long rootId);

    List<Comment> selectChildCommentsByRootId(@Param("rootId") Long rootId, @Param("lastCursor") String lastCursor, @Param("size") Integer size);

    int selectChildCommentCountByRootId(@Param("rootId") Long rootId);

    List<Comment> selectCommentsByUserId(@Param("params") Map<String, Object> params);

//    由TOTORO编辑
    List<Comment> selectByPostId(@Param("postId") Long postId);
    //    由TOTORO编辑
    int deleteByIds(@Param("ids") List<Long> ids);
    /**
     * 根据 post_id 查询所有被检索到的条目数量
     *
     * @param postId 文章ID
     * @return 符合条件的记录总数
     */
    int selectCommentCountByPostId(@Param("postId") Long postId);



    /**
     * 根据用户id获取用户发表的评论数量
     * @param userId 用户ID
     * @return 用户发表的评论数量
     */
    Integer selectUserCommentCount(@Param("userId") Long userId);

}

