package org.example.service;

import org.example.exception.CustomException;
import org.example.mapper.PostMapper;
import org.example.mapper.UserMapper;
import org.example.model.entity.Post;
import org.example.model.entity.User;
import org.example.model.vo.UserInfoLastVo.UserCommentPostVo;
import org.example.model.vo.UserInfoLastVo.UserInfoLastSetVo;
import org.example.model.vo.UserInfoLastVo.UserInfoLikeAndCommentVo;
import org.example.utils.CursorPageUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.stream.Collectors;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;
import org.example.utils.FileUrlUtil.*;
import org.example.mapper.*;
import org.example.model.dto.UserMsgDto.HomeInfoDto;
import org.example.model.dto.UserMsgDto.PostsInfoDto;
import org.example.model.entity.*;
import org.example.model.query.UserMsgQuery.*;
import org.example.model.utils.Location;
import org.example.model.vo.UserMsgVo.*;
import org.example.model.vo.common.PageResultVo;
import org.example.utils.CursorPageUtil;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.example.model.query.UserMsgQuery.LikeNotificaionQuery;
import org.example.model.vo.UserMsgVo.LikeNotificaionVo;


import java.text.SimpleDateFormat;
import java.util.*;
import java.util.stream.Collectors;

import static org.example.common.result.ResultCode.STATE_SET_ERROR;
import static org.example.common.result.ResultCode.USER_NOT_EXIST_ERROR;
import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;

@Slf4j
@Service
public class UserInfoLastService {

    @Autowired
    private UserMapper userMapper;

    @Autowired
    private PostMapper postMapper;
    @Autowired
    private CommentMapper commentMapper;
    public UserInfoLastSetVo setUserState(Long userId, String userState) {
        // 定义不可变的合法状态值集合（Java 8兼容写法）
        Set<String> validStates = Collections.unmodifiableSet(new HashSet<>(
                Arrays.asList("ACTIVE",  "FORZEN")
        ));

        // 参数校验
        if (userState == null || !validStates.contains(userState)) {
            throw new CustomException(STATE_SET_ERROR);
        }

        // 执行数据库更新
         userMapper.updateUserState(userId, userState);

        return new UserInfoLastSetVo(userState);
    }

    public UserInfoLikeAndCommentVo getUserLikeAndCommentCount(Long userId) {
        User user = userMapper.selectByPrimaryKey(userId);
        if(user == null){
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }
        Integer likeCount = postMapper.selectUserLikeCount(userId);
        Integer commentCount = postMapper.selectUserCommentCount(userId);
        return new UserInfoLikeAndCommentVo(likeCount, commentCount);
    }


    public PageResultVo<UserCommentPostVo> getUserComments(Long userId, Integer size, String lastCursor) {
        log.info("开始获取用户评论列表 - userId: {}, size: {}, lastCursor: {}", userId, size, lastCursor);
        User user_1=userMapper.selectByPrimaryKey(userId);
        if(user_1==null){
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }

        // 1. 分页查询原始评论数据
        CursorPageUtil.PageResult<Comment> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    log.info("[调试] 执行 selectComment 查询，参数: userId={}, size={}, lastCursor={}",
                            params.get("userId"),
                            params.get("size"),
                            params.get("lastCursor"));

                    List<Comment> comments = commentMapper.selectCommentsByUserId(params);

                    log.debug("查询到 {} 条评论数据", comments.size());
                    return comments;
                },
                comment -> String.valueOf(comment.getId()),
                size,
                lastCursor
        );
if(pageResult.getData().isEmpty()){
    return new PageResultVo<>(Collections.emptyList(), null);
}

        log.info("分页查询完成，共获取 {} 条评论", pageResult.getData().size());

        // 2. 转换VO
        List<UserCommentPostVo> voList = pageResult.getData().stream().map(comment -> {
            log.debug("处理评论 ID: {}", comment.getId());

            UserCommentPostVo vo = new UserCommentPostVo();
            // 基础字段
            vo.setMyId(userId);
            vo.setId(comment.getId());
            vo.setPostId(comment.getPostId());
            vo.setContent(comment.getContent());
            vo.setParentId(comment.getParentId());

            // 关联帖子信息
            log.debug("获取关联帖子 ID: {}", comment.getPostId());
            PostWithBLOBs post = postMapper.selectByPrimaryKey(comment.getPostId());
            if (post != null) {
                vo.setPostContent(post.getContent());
                vo.setTitle(post.getTitle());
                vo.setCover(getFirstFileFromJsonArray(post.getImages()));

                log.debug("获取帖子作者 ID: {}", post.getUserId());
                User postUser = userMapper.selectByPrimaryKey(post.getUserId());
                if (postUser != null) {
                    vo.setUserAccount(postUser.getAccount());
                    vo.setUserId(postUser.getId());
                    vo.setUserAvatar(postUser.getAvatar());
                } else {
                    log.warn("未找到帖子作者信息，postId: {}", post.getId());
                }
            } else {
                log.warn("未找到关联帖子，commentId: {}", comment.getId());
            }

            // 父评论信息
            if (comment.getParentId() != null) {
                log.debug("获取父评论 ID: {}", comment.getParentId());
                Comment parentComment = commentMapper.selectByPrimaryKey(comment.getParentId());
                if (parentComment != null) {
                    User parentUser = userMapper.selectByPrimaryKey(parentComment.getUserId());
                    if (parentUser != null) {
                        vo.setParentUserId(parentUser.getId());
                        vo.setParentUserAccount(parentUser.getAccount());
                        vo.setParentContent(parentComment.getContent());
                    } else {
                        log.warn("未找到父评论作者，parentCommentId: {}", parentComment.getId());
                    }
                } else {
                    log.warn("未找到父评论，parentId: {}", comment.getParentId());
                }
            }

            return vo;
        }).collect(Collectors.toList());

        log.info("VO转换完成，有效VO数量: {}", voList.size());
        log.debug("下一页游标: {}", pageResult.getNextCursor());

        // 3. 返回新的分页结果
        return new PageResultVo<>(
                voList,
                pageResult.getNextCursor()
        );
    }
}
