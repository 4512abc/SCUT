package org.example.service;

import org.example.exception.CustomException;
import org.example.mapper.*;
import org.example.model.entity.Challenge;
import org.example.model.entity.PostWithBLOBs;
import org.example.model.entity.User;
import org.example.model.entity.UserProfile;
import org.example.model.query.OtherUserInfoQuery.ChallengeListQuery;
import org.example.model.query.OtherUserInfoQuery.PostListQuery;
import org.example.model.utils.Location;
import org.example.model.vo.OtherUserInfoVo.ChallengeListVo;
import org.example.model.vo.OtherUserInfoVo.PostListVo;
import org.example.model.vo.OtherUserInfoVo.UserInfoVo;
import org.example.model.vo.common.PageResultVo;
import org.example.utils.CursorPageUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

import static org.example.common.result.ResultCode.USER_NOT_EXIST_ERROR;
import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;
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

import java.text.SimpleDateFormat;
import java.util.*;
import java.util.stream.Collectors;

import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;

import java.text.SimpleDateFormat;
import java.util.*;
import java.util.stream.Collectors;

import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;
/**
 * 其他用户信息服务类
 * 提供获取其他用户信息、挑战列表和帖子列表的功能
 */
@Slf4j
@Service
public class OtherUserInfoService {
    private final UserMapper userMapper;
    private final UserProfileMapper userProfileMapper;
    private final ChallengeMapper challengeMapper;
    private final PostMapper postMapper;
    private final ParticipationMapper participationMapper;
    private final CommentMapper commentMapper;
    /**
     * 构造器注入Mapper依赖
     */
    @Autowired
    public OtherUserInfoService(UserMapper userMapper,
                                UserProfileMapper userProfileMapper,
                                ChallengeMapper challengeMapper,
                                PostMapper postMapper,
                                ParticipationMapper participationMapper,
                                CommentMapper commentMapper) {
        this.userMapper = userMapper;
        this.userProfileMapper = userProfileMapper;
        this.challengeMapper = challengeMapper;
        this.postMapper = postMapper;
        this.participationMapper = participationMapper;
        this.commentMapper= commentMapper;
    }

    /**
     * 获取用户基本信息
     * @param userId 用户ID
     * @return 用户信息视图对象
     * @throws CustomException 当用户不存在时抛出异常
     */
    public UserInfoVo getUserInfo(Long userId) {
        User user = userMapper.selectByPrimaryKey(userId);
        if (user == null) {
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }

        UserProfile profile = userProfileMapper.selectByPrimaryKey(userId);
        return convertToVo(user, profile);
    }

    /**
     * 将User和UserProfile实体转换为视图对象
     */
    private UserInfoVo convertToVo(User user, UserProfile profile) {
        UserInfoVo vo = new UserInfoVo();
        vo.setAccount(user.getAccount());
        vo.setStatus(user.getStatus());
        vo.setCreateTime(user.getCreateTime());
        vo.setUpdateTime(user.getUpdateTime());
        vo.setAvatar(user.getAvatar());
        vo.setPostCount(postMapper.selectUserPostCount(user.getId()));
        vo.setChallengeCount(challengeMapper.selectUserChallengeCount(user.getId()));
        vo.setParticipantCount(participationMapper.selectUserChallengeCount(user.getId()));
        vo.setCommentCount(commentMapper.selectUserCommentCount(user.getId()));
        if (profile != null) {
            vo.setBio(profile.getBio());
            vo.setGender(profile.getGender());
            vo.setBirthday(profile.getBirthday());
            if (profile.getLocation() != null) {
                vo.setLocation(profile.getLocation());
            }
        }
        return vo;
    }

    /**
     * 获取用户挑战列表（分页）
     * @param userId 用户ID
     * @param query 查询参数
     * @return 分页结果
     */
    public PageResultVo<ChallengeListVo> getChallengeList(Long userId, ChallengeListQuery query) {
        // 1. 执行游标分页查询
        if(userMapper.selectByPrimaryKey(userId)==null){
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }
        CursorPageUtil.PageResult<Challenge> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("creatorId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    
                    // 调试日志：输出分页参数
                    log.info("[调试] 执行 selectChallengesByCreator 查询，参数: creatorId={}, size={}, lastCursor={}",
                            params.get("creatorId"),
                            params.get("size"),
                            params.get("lastCursor"));
                    
                    List<Challenge> challenges = challengeMapper.selectChallengesByCreator(params);
                    
                    // 调试日志：输出查询结果
                    log.info("[调试] SQL 查询结果数量: {}", challenges != null ? challenges.size() : 0);
                    if (challenges != null && !challenges.isEmpty()) {
                        log.info("[调试] 第一条记录 ID: {}", challenges.get(0).getId());
                        log.info("[调试] 最后一条记录 ID: {}", challenges.get(challenges.size() - 1).getId());
                    }
                    
                    return challenges;
                },
                challenge -> String.valueOf(challenge.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }
        // 2. 获取创建者账号信息
        List<Long> creatorIds = pageResult.getData().stream()
                .map(Challenge::getCreatorId)
                .collect(Collectors.toList());
        Map<Long, String> creatorAccounts = userMapper.selectAccountsByIds(creatorIds);
        log.info("[调试] 根据ID查询用户账号 | 参数ids={} | 结果记录数={} | 结果={}",
                creatorIds,
                creatorAccounts.size(),
                creatorAccounts);
        log.info("[调试] 用户账号映射详情:");
        for (Map.Entry<Long, String> entry : creatorAccounts.entrySet()) {
            log.info("  用户ID: {} => 账号: {}", entry.getKey(), entry.getValue() != null ? entry.getValue() : "NULL");
        }

        // 3. 转换结果
        List<ChallengeListVo> vos = pageResult.getData().stream()
                .map(challenge -> convertToVo(challenge, userMapper.selectAccountById(challenge.getCreatorId())))
                .collect(Collectors.toList());
        log.info("[调试] 账户={}", creatorAccounts.get(1L));
        // 调试日志：输出分页结果
        log.info("[调试] 分页结果: 当前页数量={}, 下一页游标={}", vos.size(), pageResult.getNextCursor());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    /**
     * 将Challenge实体转换为视图对象
     */
    private ChallengeListVo convertToVo(Challenge challenge, String creatorAccount) {
        ChallengeListVo vo = new ChallengeListVo();
        vo.setId(challenge.getId());
        vo.setTitle(challenge.getTitle());
        log.info("[调试] 账户={}", creatorAccount);
        vo.setCreatorAccount(creatorAccount);
        vo.setObjectType(challenge.getObjectType());
        vo.setGestureType(challenge.getGestureType());
        vo.setLandmarkName(challenge.getLandmarkName());
        vo.setParticipants(challenge.getParticipants());
        vo.setEndTime(challenge.getEndTime());
        vo.setCover(getFirstFileFromJsonArray(challenge.getImages()));
        vo.setLocation(Location.fromBytes(challenge.getLocation()));
        return vo;
    }

    /**
     * 获取用户帖子列表（分页）
     * @param userId 用户ID
     * @param query 查询参数
     * @return 分页结果
     */
    public PageResultVo<PostListVo> getPostList(Long userId, PostListQuery query) {

        if(userMapper.selectByPrimaryKey(userId)==null){
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }
        CursorPageUtil.PageResult<PostWithBLOBs> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return postMapper.selectPostsWithBLOBs(params);
                },
                post -> String.valueOf(post.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        return new PageResultVo<>(
                pageResult.getData().stream()
                        .map(this::convertToVo)
                        .collect(Collectors.toList()),
                pageResult.getNextCursor()
        );
    }

    /**
     * 将PostWithBLOBs实体转换为视图对象
     */
    private PostListVo convertToVo(PostWithBLOBs post) {
        PostListVo vo = new PostListVo();
        vo.setId(post.getId());
        vo.setTitle(post.getTitle());
        vo.setViewCount(post.getViewCount());
        vo.setLikeCount(post.getLikeCount());
        vo.setCommentCount(post.getCommentCount());
        vo.setCreateTime(post.getCreateTime());
        vo.setCover(getFirstFileFromJsonArray(post.getImages()));
        vo.setLandmarkName(post.getLandmarkName());
        // 位置解析
        if (post.getLocation() != null) {
            vo.setLocation(Location.fromBytes(post.getLocation()));
            log.info("[调试] 解析位置信息，原始数据: {}", post.getLocation());
            log.info("原始二进制数据长度: {}", post.getLocation() != null ? post.getLocation().length : 0);
            log.info("解析结果: {}", Location.fromBytes(post.getLocation()));
        }

        return vo;
    }

}