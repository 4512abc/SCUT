package org.example.service;

import lombok.extern.slf4j.Slf4j;
import org.example.common.result.ResultCode;
import org.example.exception.CustomException;
import org.example.mapper.NotificationMapper;
import org.example.model.entity.Notification;
import org.example.model.query.NotificatonQuery.*;
import org.example.model.vo.NotificationVo.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.example.mapper.*;
import org.example.model.entity.*;
import org.example.model.vo.common.PageResultVo;
import org.example.utils.CursorPageUtil;

import java.util.*;
import java.util.stream.Collectors;

import static org.example.common.result.ResultCode.*;

/**
 * 用户信息服务类
 * 功能：处理用户主页、群组、帖子、点赞等业务逻辑
 */
@Slf4j
@Service
public class NotificationService {

    @Autowired
    private NotificationMapper notificationMapper;  // 通知数据访问对象
    @Autowired
    private LikeMapper likeMapper;  // 点赞数据访问对象
    @Autowired
    private PostMapper postMapper;  // 帖子数据访问对象
    @Autowired
    private CommentMapper commentMapper;  // 评论数据访问对象
    @Autowired
    private UserMapper userMapper;  // 用户数据访问对象

    /**
     * 获取评论列表（分页）
     * @param query 查询条件，包含帖子ID、分页大小和游标
     * @return 分页评论列表
     */
    public PageResultVo<CommentListVo> getCommentList(CommentListQuery query) {
        // 1. 执行游标分页查询
        PostWithBLOBs post_1= postMapper.selectByPrimaryKey(query.getPostId());
        if(post_1==null) {
            throw new CustomException(POST_NOT_FOUND);
        }
        CursorPageUtil.PageResult<Comment> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("postId", query.getPostId());
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return commentMapper.selectRootCommentsByPostId(params);
                },
                comment -> String.valueOf(comment.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );


        // 2. 获取根评论的第一条子评论
        List<CommentListVo> vos = pageResult.getData().stream().map(rootComment -> {
            CommentListVo vo = new CommentListVo();
            vo.setId(rootComment.getId());
            vo.setUserId(rootComment.getUserId());
            vo.setAccount(userMapper.selectAccountById(rootComment.getUserId()));
            vo.setAvatar(userMapper.selectByPrimaryKey(rootComment.getUserId()).getAvatar());
            vo.setContent(rootComment.getContent());

            // 获取第一条子评论
            Comment firstChildComment = commentMapper.selectFirstChildCommentByRootId(rootComment.getId());
            if (firstChildComment != null) {
                vo.setSonUserId(firstChildComment.getUserId());
                vo.setSonId(firstChildComment.getId());
                vo.setSonAccount(userMapper.selectAccountById(firstChildComment.getUserId()));
                vo.setSonAvatar(userMapper.selectByPrimaryKey(firstChildComment.getUserId()).getAvatar());
                vo.setSonContent(firstChildComment.getContent());

                // 查询子评论数量
                int childCommentCount = commentMapper.selectChildCommentCountByRootId(rootComment.getId());
                vo.setIsHave(childCommentCount > 1 ? true : false);
            } else {
                vo.setIsHave(false);
            }

            return vo;
        }).collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    /**
     * 获取更多评论列表（子评论分页）
     * @param query 查询条件，包含根评论ID、分页大小和游标
     * @return 分页子评论列表
     */
    public PageResultVo<MoreCommentListVo> getMoreCommentList(MoreCommentListQuery query) {
        // 1. 执行游标分页查询
        Comment rootComment = commentMapper.selectByPrimaryKey(query.getRootId());
        if(rootComment==null){
            throw new CustomException(COMMENT_NOT_FOUND);
        }
        if(rootComment.getIsRoot()==0){
            throw new CustomException(COMMENT_OPERATION_FORBIDDE);
        }
        CursorPageUtil.PageResult<Comment> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("rootId", query.getRootId());
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return commentMapper.selectChildCommentsByRootId(query.getRootId(), param.getLastCursor(), param.getSize());
                },
                comment -> String.valueOf(comment.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );
        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(Collections.emptyList(), null);
        }
        // 2. 获取子评论的用户信息
        List<MoreCommentListVo> vos = pageResult.getData().stream().map(comment -> {
            MoreCommentListVo vo = new MoreCommentListVo();
            vo.setId(comment.getId());
            vo.setUserId(comment.getUserId());
            vo.setAccount(userMapper.selectByPrimaryKey(comment.getUserId()).getAccount());
            vo.setAvatar(userMapper.selectByPrimaryKey(comment.getUserId()).getAvatar());
            vo.setContent(comment.getContent());

            // 获取父评论信息
            if (comment.getParentId() != null) {
                Comment parentComment = commentMapper.selectByPrimaryKey(comment.getParentId());
                vo.setParentId(parentComment.getId());
                vo.setParentUserId(parentComment.getUserId());
                vo.setParentAccount(userMapper.selectByPrimaryKey(comment.getUserId()).getAccount());
                vo.setParentContent(parentComment.getContent());
            }

            return vo;
        }).collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    /**
     * 创建评论
     * @param postId 帖子ID
     * @param query 评论创建请求参数
     * @param userId 用户ID
     * @return 评论创建结果
     */
    public CommentCreateVo createComment(Long postId, CommentCreateQuery query, Long userId) {
        // 创建评论
        PostWithBLOBs post_1 = postMapper.selectByPrimaryKey(postId);
        if(post_1==null){
            throw new CustomException(POST_NOT_FOUND);
        }
        if(!post_1.getIsPublic()){
            throw new CustomException(POST_NOT_PUBLIC);
        }
        if(query.getContent()==null|| Objects.equals(query.getContent(), "")){
            throw new CustomException(COMMENT_CONTENT_EMPTY);
        }
        Comment comment = new Comment();
        comment.setUserId(userId);
        comment.setPostId(postId);
        comment.setContent(query.getContent());
        comment.setParentId(query.getParentId());
        comment.setIsRoot(query.getParentId() == null ? (byte) 1 : (byte) 0); // 如果父评论为空，则为根评论
        comment.setCreateTime(new Date());
        comment.setLikeCount(0);
        comment.setStatus((byte)1);

        // 先插入评论，获取生成的 id
        commentMapper.insert(comment);

        // 设置 root_id
        if (query.getParentId() == null) {
            // 如果父评论为空，root_id 设置为自己的 id
            log.info("设置 root_id 为自己的 id={}",query.getParentId());
            comment.setRootId(comment.getId());
        } else {
            // 如果父评论不为空，root_id 设置为父评论的 root_id
            Comment parentComment = commentMapper.selectByPrimaryKey(query.getParentId());
            comment.setRootId(parentComment.getRootId());
        }

        // 更新评论的 root_id
        commentMapper.updateByPrimaryKeySelective(comment);

        // 获取博文作者ID
        Post post = postMapper.selectByPrimaryKey(postId);
        Long postAuthorId = post.getUserId();

        // 更新博文评论数
        postMapper.updateByPrimaryKeySelective(new PostWithBLOBs() {{
            setId(postId);
            setCommentCount(post.getCommentCount() + 1);
        }});

        // 创建通知
        Notification notification = new Notification();
        notification.setSenderId(userId);
        notification.setReceiverId(postAuthorId);
        notification.setType((byte) 1); // 1代表评论类型
        notification.setTypeId(comment.getId());
        notification.setContent("用户" + userId + "评论了你的帖子");
        notification.setIsRead(false);
        notification.setCreateTime(new Date());
        notificationMapper.insert(notification);

        // 返回结果
        CommentCreateVo vo = new CommentCreateVo();
        vo.setCommentId(comment.getId());
        vo.setContent(comment.getContent());
        vo.setStatus(true);
        return vo;
    }

    /**
     * 更新点赞通知为已读状态
     * @param userId 用户ID
     * @param query 查询参数
     * @return 更新结果
     */
    public LikeIsreadVo updateLikeIsRead(Long userId, LikeIsreadQuery query) {
        Notification notification = new Notification();
        notification.setTypeId(query.getId());
        log.info("[调试] 执行 selectPostsWithBLOBs 查询，参数: userId={}", query.getId());
        notification.setType((byte) 2); // 2代表点赞类型
        notification.setIsRead(true);

        // 查询是否存在对应的通知
        Notification existingNotification = notificationMapper.selectByTypeIdAndType(userId,query.getId(), (byte) 2);
        if (existingNotification == null) {
            throw new CustomException(LIKE_NOT_FOUND);
        } else {
            log.info("[调试] 找到对应的通知，通知ID={}, isRead={}", existingNotification.getId(), existingNotification.getIsRead());
            // 设置通知的ID，以便更新操作能找到正确的记录
            notification.setId(existingNotification.getId());
        }

        int result = notificationMapper.updateByPrimaryKeySelective(notification);
        log.info("是否更新成功：result={}", result);
        LikeIsreadVo vo = new LikeIsreadVo();
        Like like= likeMapper.selectByPrimaryKey(existingNotification.getTypeId());
        vo.setPostId(like.getTargetId()); // 1表示已读
        return vo;
    }

    /**
     * 更新评论通知为已读状态
     * @param userId 用户ID
     * @param query 查询参数
     * @return 更新结果
     */
    public CommentIsreadVo updateCommentIsRead(Long userId, CommentIsreadQuery query) {
        Notification notification = new Notification();
        notification.setTypeId(query.getId());
        notification.setType((byte) 1); // 1代表评论类型
        notification.setIsRead(true);

        // 查询是否存在对应的通知
        Notification existingNotification = notificationMapper.selectByTypeIdAndType(userId,query.getId(), (byte) 1);
        if (existingNotification == null) {
            log.warn("[调试] 未找到对应的通知，typeId={}, type=1", query.getId());
            throw new CustomException(COMMENT_NOT_FOUND);
        } else {
            log.info("[调试] 找到对应的通知，通知ID={}, isRead={}", existingNotification.getId(), existingNotification.getIsRead());
            // 设置通知的ID，以便更新操作能找到正确的记录
            notification.setId(existingNotification.getId());
        }

        int result = notificationMapper.updateByPrimaryKeySelective(notification);
        log.info("是否更新成功：result={}", result);
        CommentIsreadVo vo = new CommentIsreadVo();
        Comment comment = commentMapper.selectByPrimaryKey(existingNotification.getTypeId());
        vo.setPostId(comment.getPostId()); // 返回博文id
        return vo;
    }

    /**
     * 更新公告通知为已读状态
     * @param userId 用户ID
     * @param query 查询参数
     * @return 更新结果
     */
    public AnnouncementIsreadVo updateAnnouncementIsRead(Long userId, AnnouncementIsreadQuery query) {
        Notification notification = new Notification();
        notification.setTypeId(query.getId());
        notification.setType((byte) 3); // 3代表公告类型
        notification.setIsRead(true);

        // 查询是否存在对应的通知
        Notification existingNotification = notificationMapper.selectByTypeIdAndType(userId,query.getId(), (byte) 3);
        if (existingNotification == null) {
            log.warn("[调试] 未找到对应的通知，typeId={}, type=3", query.getId());
            throw new CustomException(ANNOUNCEMENT_NOT_FOUND);
        } else {
            log.info("[调试] 找到对应的通知，通知ID={}, isRead={}", existingNotification.getId(), existingNotification.getIsRead());
            // 设置通知的ID，以便更新操作能找到正确的记录
            notification.setId(existingNotification.getId());
        }

        int result = notificationMapper.updateByPrimaryKeySelective(notification);
        log.info("是否更新成功：result={}", result);
        AnnouncementIsreadVo vo = new AnnouncementIsreadVo();
        vo.setAnnouncementId(existingNotification.getTypeId());
        return vo;
    }

    /**
     * 点赞或取消点赞帖子
     * @param query 点赞请求参数
     * @return 点赞状态结果
     */
    public LikeIsNotVo likeOrUnlikePost(LikeIsNotQuery query) {
        Long postId = query.getPostId();
        Long userId = query.getUserId();
        PostWithBLOBs post_1 = postMapper.selectByPrimaryKey(postId);
        if(post_1 == null){
            throw new CustomException(POST_NOT_FOUND);
        }

        // 查询是否已经点赞
        Like existingLike = likeMapper.selectByUserIdAndPostId(userId, postId);
        if (existingLike != null) {
            // 如果已经点赞，则取消点赞
            notificationMapper.deleteByTypeIdAndType(existingLike.getId(), (byte) 2);
            likeMapper.deleteByPrimaryKey(existingLike.getId());
            // 直接通过 postId 更新博文点赞数，减1
            postMapper.updateByPrimaryKeySelective(new PostWithBLOBs() {{
                setId(postId);
                setLikeCount(postMapper.selectByPrimaryKey(postId).getLikeCount() - 1);
            }});
            LikeIsNotVo likeIsNotVo = new LikeIsNotVo();
            likeIsNotVo.setNewStatus("0");
            return likeIsNotVo;
        } else {
            // 如果没有点赞，则添加点赞
            Like newLike = new Like();
            newLike.setUserId(userId);
            newLike.setTargetId(postId);
            newLike.setTargetType("BLOG");
            newLike.setCreateTime(new Date()); // 设置 create_time
            likeMapper.insert(newLike);
            // 直接通过 postId 更新博文点赞数，加1
            postMapper.updateByPrimaryKeySelective(new PostWithBLOBs() {{
                setId(postId);
                setLikeCount(postMapper.selectByPrimaryKey(postId).getLikeCount() + 1);
            }});
            // 获取博文作者ID
            Post post = postMapper.selectByPrimaryKey(postId);
            Long postAuthorId = post.getUserId();
            // 添加通知
            Notification notification = new Notification();
            notification.setSenderId(userId);
            notification.setReceiverId(postAuthorId);
            notification.setType((byte) 2); // 2代表点赞类型
            notification.setTypeId(newLike.getId());
            notification.setContent("用户" + userId + "点赞了你的帖子");
            notification.setIsRead(false);
            notification.setCreateTime(new Date()); // 设置 create_time
            notificationMapper.insert(notification);
            LikeIsNotVo likeIsNotVo = new LikeIsNotVo();
            likeIsNotVo.setNewStatus("1");
            return likeIsNotVo;
        }
    }

    /**
     * 设置挑战通知
     * @param challengeId 挑战ID
     * @param userId 用户ID
     * @param createrId 创建者ID
     * @param content 通知内容
     */
    public void setChallengeNotification(Long challengeId, Long userId, Long createrId, String content) {
        // 获取挑战信息
        if(notificationMapper.selectBySenderReceiverTypeAndTypeId(createrId, userId, (byte) 4, challengeId)==null){
            Notification notification = new Notification();
            notification.setSenderId(createrId);
            notification.setReceiverId(userId);
            notification.setType((byte) 4);
            notification.setTypeId(challengeId);
            notification.setContent(content);
            notification.setIsRead(false);
            notification.setCreateTime(new Date());
            notificationMapper.insert(notification);
        }
    }
}