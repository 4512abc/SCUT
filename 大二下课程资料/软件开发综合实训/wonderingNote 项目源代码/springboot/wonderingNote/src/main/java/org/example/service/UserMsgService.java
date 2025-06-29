//该文件由TOTORO编辑
//责任说明！！！

package org.example.service;
import com.alibaba.druid.util.StringUtils;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;
import org.example.exception.CustomException;
import org.example.mapper.*;
import org.example.model.entity.*;
import org.example.model.query.UserMsgQuery.*;
import org.example.model.utils.Location;
import org.example.model.vo.UserMsgVo.*;
import org.example.model.vo.common.PageResultVo;
import org.example.utils.CursorPageUtil;
import org.springframework.stereotype.Service;
import org.example.model.query.UserMsgQuery.LikeNotificaionQuery;
import org.example.model.vo.UserMsgVo.LikeNotificaionVo;


import java.util.*;
import java.util.stream.Collectors;

import static org.example.common.result.ResultCode.*;
import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;

/**
 * 用户信息服务类
 * 功能：处理用户主页、群组、帖子、点赞等业务逻辑
 */
@Slf4j
@Service
public class UserMsgService {

    // ------------------------ 依赖注入 ------------------------
    private final UserMapper userMapper;
    private final UserProfileMapper userProfileMapper;
    private final TeamMapper teamMapper;
    private final PostMapper postMapper;
    private final LikeMapper likeMapper;
    private final ChallengeMapper challengeMapper;
    private final ParticipationMapper participationMapper;
    private final AnnouncementMapper announcementMapper;
    private final NotificationMapper notificationMapper;
    private final CommentMapper commentMapper;
    private final TeamMemberMapper teamMemberMapper;

    /**
     * 构造器注入Mapper依赖
     */
    public UserMsgService(UserMapper userMapper,
                          UserProfileMapper userProfileMapper,
                          TeamMapper teamMapper,
                          PostMapper postMapper,
                          LikeMapper likeMapper,
                          ChallengeMapper challengeMapper,
                          AnnouncementMapper announcementMapper,
                          NotificationMapper notificationMapper,
                          ParticipationMapper participationMapper,
                          CommentMapper commentMapper,
                          TeamMemberMapper teamMemberMapper) {
        this.userMapper = userMapper;
        this.userProfileMapper = userProfileMapper;
        this.teamMapper = teamMapper;
        this.postMapper = postMapper;
        this.likeMapper = likeMapper;
        this.challengeMapper = challengeMapper;
        this.announcementMapper = announcementMapper;
        this.notificationMapper = notificationMapper;
        this.participationMapper = participationMapper;
        this.commentMapper = commentMapper;
        this.teamMemberMapper = teamMemberMapper;
    }

    // ------------------------ 1. 用户主页信息 ------------------------

    /**
     * 获取用户主页信息
     *
     * @param userId 用户ID
     * @return 包含基础信息和资料信息的DTO
     */
// UserMsgService.java 修改后方法
    public HomeInfoVo getHomeInfoVo(Long userId) {
        // 1. 查询数据库
        User user = userMapper.selectByPrimaryKey(userId);
        UserProfile profile = userProfileMapper.selectByPrimaryKey(userId);

        // 2. 直接构建VO对象
        HomeInfoVo vo = new HomeInfoVo();
        HomeInfoVo.BaseInfo baseVo = new HomeInfoVo.BaseInfo();
        HomeInfoVo.ProfileInfo profileVo = new HomeInfoVo.ProfileInfo();

        // 3. 处理用户基础信息（保持Date类型）
        if (user != null) {
            baseVo.setAccount(user.getAccount());
            baseVo.setPhone(user.getPhone());
            baseVo.setEmail(user.getEmail());
            baseVo.setAvatar(user.getAvatar());
            baseVo.setStatus(user.getStatus());
            baseVo.setWxOpenid(user.getWxOpenid());
            baseVo.setWxUnionid(user.getWxUnionid());
            baseVo.setCreateTime(user.getCreateTime()); // 直接传递Date
            baseVo.setUpdateTime(user.getUpdateTime()); // 直接传递Date
            baseVo.setAccessLevel(user.getAccessLevel());
            vo.setBaseInfo(baseVo);
        }

        // 4. 处理用户资料信息（保持Date类型）
        if (profile != null) {
            profileVo.setGender(profile.getGender());
            profileVo.setBirthday(profile.getBirthday()); // 直接传递Date
            profileVo.setBio(profile.getBio());
            profileVo.setLocation(profile.getLocation());
            // 将 settings 字符串转换为 JSON 对象
            String settingsStr = profile.getSettings();
            if (settingsStr != null && !settingsStr.isEmpty()) {
                profileVo.setSettings(parseSettings(profile.getSettings()));
            }
            vo.setProfileInfo(profileVo);
        }

        return vo;
    }
    private JsonNode parseSettings(String settingsStr) {
        if (StringUtils.isEmpty(settingsStr)) {
            return null;
        }

        try {
            return new ObjectMapper().readTree(settingsStr);
        } catch (Exception e) {
            log.error("用户设置解析失败, settings: {}", settingsStr, e);
            return null;
        }
    }

    // ------------------------ 2. 群组信息 ------------------------

    /**
     * 获取用户群组列表
     *
     * @param userId 用户ID
     * @param query  查询参数（分页/排序）
     * @return 群组DTO列表
     */
    public PageResultVo<TeamInfoVo> getTeamInfo(Long userId, TeamInfoQuery query) {
        CursorPageUtil.PageResult<Team> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return teamMapper.selectByParams(params);
                },
                team -> String.valueOf(team.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        List<TeamInfoVo> vos = pageResult.getData().stream()
                .map(team -> {
                    TeamInfoVo vo = new TeamInfoVo();
                    vo.setId(team.getId());
                    vo.setName(team.getName());
                    vo.setLogo(team.getLogo());
                    vo.setCreatorId(team.getCreatorId());
                    vo.setMaxMembers(team.getMaxMembers());
                    vo.setCreateTime(team.getCreateTime()); // 直接传递Date
                    return vo;
                })
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    // ------------------------ 3. 帖子信息 ------------------------

    /**
     * 获取用户帖子列表
     *
     * @param userId 用户ID
     * @param query  查询参数
     * @return 帖子DTO列表
     */
    public PageResultVo<PostsInfoVo> getPostsInfo(Long userId, PostsInfoQuery query) {
        // 1. 执行游标分页查询
        CursorPageUtil.PageResult<PostWithBLOBs> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());

                    log.info("[调试] 执行 selectPostsWithBLOBs 查询，参数: userId={}, size={}, lastCursor={}",
                            params.get("userId"),
                            params.get("size"),
                            params.get("lastCursor"));

                    List<PostWithBLOBs> posts = postMapper.selectPostsWithBLOBs(params);

                    log.info("[调试] SQL 查询结果数量: {}", posts != null ? posts.size() : 0);
                    if (posts != null && !posts.isEmpty()) {
                        log.info("[调试] 第一条记录 ID: {}", posts.get(0).getId());
                    }

                    return posts;
                },
                post -> String.valueOf(post.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        // 2. 转换结果
        List<PostsInfoVo> vos = pageResult.getData().stream()
                .map(post -> {
                    PostsInfoVo vo = new PostsInfoVo();
                    vo.setId(post.getId());
                    vo.setTitle(post.getTitle());
                    vo.setViewCount(post.getViewCount());
                    vo.setLikeCount(post.getLikeCount());
                    vo.setCommentCount(post.getCommentCount());
                    vo.setLandmarkName(post.getLandmarkName());
                    vo.setIsPublic(post.getIsPublic());
                    // 处理封面图片
                    vo.setCover(getFirstFileFromJsonArray(post.getImages()));
                    // 处理时间格式
                    vo.setCreateTime(post.getCreateTime());
                    // 处理位置信息
                    log.info("[调试] 解析位置信息，原始数据: {}", post.getLocation());
                    log.info("原始二进制数据长度: {}", post.getLocation() != null ? post.getLocation().length : 0);
                    log.info("解析结果: {}", Location.fromBytes(post.getLocation()));
                    vo.setLocation(Location.fromBytes(post.getLocation()));
                    return vo;
                })
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    // ------------------------ 4. 点赞信息 ------------------------

    /**
     * 获取用户点赞列表
     *
     * @param userId 用户ID
     * @param query  查询参数
     * @return 点赞DTO列表
     */
    public PageResultVo<LikesInfoVo> getLikesInfo(Long userId, LikesInfoQuery query) {
        // 1. 执行游标分页查询
        CursorPageUtil.PageResult<Like> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor()); // 参数名统一为lastCursor

                    // 打印查询参数
                    log.info("[调试] 执行 selectLikedPostsByUserId 查询，参数: userId={}, size={}, lastCursor={}",
                            params.get("userId"),
                            params.get("size"),
                            params.get("lastCursor"));

                    List<Like> likes = likeMapper.selectLikedPostsByUserId(params);

                    // 打印查询结果
                    log.info("[调试] SQL 查询结果数量: {}", likes != null ? likes.size() : 0);
                    if (likes != null && !likes.isEmpty()) {
                        log.info("[调试] 第一条记录 ID: {}", likes.get(0).getId());
                    }

                    return likes;
                },
                like -> String.valueOf(like.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor() // 使用 lastCursor
        );

        // 2. 获取关联的帖子详情并转换结果
        List<LikesInfoVo> vos = pageResult.getData().stream()
                .map(like -> {
                    PostWithBLOBs post = postMapper.selectPostWithBLOBsById(like.getTargetId());

                    // 打印帖子查询结果
                    log.info("[调试] 查询帖子详情，targetId={}, 帖子是否存在: {}", like.getTargetId(), post != null);
                    if (post != null) {
                        log.info("[调试] 帖子标题: {}", post.getTitle());
                    }

                    return convertToVo(like, post);
                })
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private LikesInfoVo convertToVo(Like like, PostWithBLOBs post) {
        LikesInfoVo vo = new LikesInfoVo();
        // 设置基本属性
        vo.setId(like.getId());
        vo.setPostId(like.getTargetId());
        vo.setTitle(post.getTitle());
        vo.setViewCount(post.getViewCount());
        vo.setLikeCount(post.getLikeCount());
        vo.setCommentCount(post.getCommentCount());

        // 处理封面图片
        vo.setCover(getFirstFileFromJsonArray(post.getImages()));

        // 格式化时间
        vo.setCreateTime(like.getCreateTime());

        // 处理位置信息
        log.info("[调试] 解析位置信息，原始数据: {}", post.getLocation());
        // 在convertToVo方法中添加：
        log.info("原始二进制数据长度: {}", post.getLocation() != null ? post.getLocation().length : 0);
        log.info("解析结果: {}", Location.fromBytes(post.getLocation()));

        vo.setLocation(Location.fromBytes(post.getLocation()));


        return vo;
    }

    // ------------------------ 5. 挑战信息 ------------------------

    /**
     * 获取用户参与的挑战信息
     *
     * @param userId 用户ID
     * @param query  查询参数
     * @return 挑战DTO列表
     */
    public PageResultVo<ChallengeInfoVo> getChallengeInfo(Long userId, ChallengeInfoQuery query) {
        // 1. 执行游标分页查询参与记录
        CursorPageUtil.PageResult<Participation> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return participationMapper.selectParticipationsByUserId(params);
                },
                participation -> String.valueOf(participation.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );
        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }

        // 2. 批量查询关联的挑战信息
        List<Long> challengeIds = pageResult.getData().stream()
                .map(Participation::getChallengeId)
                .collect(Collectors.toList());
        List<Challenge> challenges = challengeMapper.selectByIds(challengeIds);
// 原地反转列表（直接修改原列表）
//        Collections.reverse(challenges);

// 打印反转后的ID（验证）
//        // 3. 查询创建者账号信息
//        Map<Long, String> creatorAccounts = challenges.stream()
//                .collect(Collectors.toMap(
//                        Challenge::getCreatorId,
//                        challenge -> userMapper.selectAccountById(challenge.getCreatorId())
//                ));
        Map<Long, String> creatorAccounts = new HashMap<>();
        for (Challenge challenge : challenges) {
            Long creatorId = challenge.getCreatorId();
            if (!creatorAccounts.containsKey(creatorId)) {  // 避免重复查询
                String account = userMapper.selectAccountById(creatorId);
                creatorAccounts.put(creatorId, account);
            }
        }

        // 4. 转换结果
        List<ChallengeInfoVo> vos = challenges.stream()
                .map(challenge -> convertToVo(challenge, creatorAccounts.get(challenge.getCreatorId())))
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private ChallengeInfoVo convertToVo(Challenge challenge, String creatorAccount) {
        ChallengeInfoVo vo = new ChallengeInfoVo();
        vo.setId(challenge.getId());
        vo.setTitle(challenge.getTitle());
        vo.setCreatorAccount(creatorAccount);
        vo.setObjectType(challenge.getObjectType());
        vo.setGestureType(challenge.getGestureType());
        vo.setLandmarkName(challenge.getLandmarkName());
        vo.setParticipants(challenge.getParticipants());
        vo.setImages(challenge.getImages());
        vo.setEndTime(challenge.getEndTime());
        vo.setRadius(challenge.getRadius());
        vo.setLocation(Location.fromBytes(challenge.getLocation()));
        vo.setDescription(challenge.getDescription());
        vo.setCover(getFirstFileFromJsonArray(challenge.getImages()));
        vo.setCreatorId(challenge.getCreatorId());
        vo.setStartTime(challenge.getStartTime());
        vo.setTeamId(challenge.getTeamId());
        vo.setCreateTime(challenge.getCreateTime());


        return vo;
    }


    // ------------------------ 6. 公告信息 ------------------------

    /**
     * 获取公告列表
     *
     * @param query 查询参数
     * @return 公告DTO列表
     */
    public PageResultVo<AnnouncementInfoVo> getAnnouncementInfo(AnnouncementInfoQuery query) {
        // 1. 执行游标分页查询
        CursorPageUtil.PageResult<Announcement> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return announcementMapper.selectAnnouncements(params);
                },
                announcement -> String.valueOf(announcement.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }
        // 3. 转换结果
        List<AnnouncementInfoVo> vos = pageResult.getData().stream()
                .map(announcement -> convertToVo(announcement))
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private AnnouncementInfoVo convertToVo(Announcement announcement) {
        AnnouncementInfoVo vo = new AnnouncementInfoVo();
        vo.setId(announcement.getId());
        vo.setTitle(announcement.getTitle());
        vo.setUpdateTime(announcement.getUpdateTime());
        vo.setType( Integer.valueOf(announcement.getType()));
        return vo;
    }

    public PageResultVo<AnnouncementInfoVo> getAnnouncementInfomore(AnnouncementInfoQuery query) {
        // 1. 执行游标分页查询
        CursorPageUtil.PageResult<Announcement> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return announcementMapper.selectAnnouncementsmore(params);
                },
                announcement -> String.valueOf(announcement.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }
        // 3. 转换结果
        List<AnnouncementInfoVo> vos = pageResult.getData().stream()
                .map(announcement -> convertToVomore(announcement))
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private AnnouncementInfoVo convertToVomore(Announcement announcement) {
        AnnouncementInfoVo vo = new AnnouncementInfoVo();
        vo.setId(announcement.getId());
        vo.setTitle(announcement.getTitle());
        vo.setUpdateTime(announcement.getUpdateTime());
        vo.setType( Integer.valueOf(announcement.getType()));

        return vo;
    }

    public AnnouncementDataVo getAnnouncementDetail(Long userId, Long id) {
        // 查询公告详情
        Announcement announcement = announcementMapper.selectByPrimaryKey(id);
        if (announcement == null) {
            throw new CustomException(ANNOUNCEMENT_NOT_FOUND);
        }

        // 查询发布者信息
        User user = userMapper.selectByPrimaryKey(announcement.getPublisherId());
        if (user == null) {
            throw new CustomException(USER_NOT_EXIST_ERROR);
        }
        User user_1=userMapper.selectByPrimaryKey(userId);
        log.info("userId:"+user_1.getAccessLevel().equals("user"));
        if (user_1.getAccessLevel().equals("user")){
            if(announcement.getType()==1){
                throw new CustomException(ANNOUNCEMENT_READ_FAILED);
            }
        }

        // 构建返回结果
        AnnouncementDataVo vo = new AnnouncementDataVo();
        vo.setTitle(announcement.getTitle());
        vo.setContent(announcement.getContent());
        vo.setType(announcement.getType().intValue());
        vo.setPublishedId(announcement.getPublisherId());
        vo.setCreateTime(announcement.getCreateTime());
        vo.setUpdateTime(announcement.getUpdateTime());
        vo.setUserAvatar(user.getAvatar());
        vo.setUserAccount(user.getAccount());

        return vo;
    }


    // ------------------------ 7. 评论信息 ------------------------

    /**
     * 获取用户评论通知
     *
     * @param userId 用户ID
     * @param query  查询参数
     * @return 评论DTO列表
     */
    public PageResultVo<CommentInfoVo> getCommentInfo(Long userId, CommentInfoQuery query) {
        // 1. 查询评论通知
        CursorPageUtil.PageResult<Notification> notificationPage = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("receiverId", userId);
                    params.put("type", 1);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return notificationMapper.selectCommentNotifications(params);
                },
                notification -> String.valueOf(notification.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        // 2. 提取评论ID
        Set<Long> commentIds = notificationPage.getData().stream()
                .map(Notification::getTypeId)
                .filter(Objects::nonNull)
                .collect(Collectors.toSet());

        if (commentIds.isEmpty()) {
            return new PageResultVo<>(Collections.emptyList(), null);
        }

        // 3. 批量查询评论（直接返回实体）
        // UserMsgService.java（修改后）
        Map<Long, Comment> comments = commentMapper.selectCommentsByIds(commentIds)
                .stream()
                .collect(Collectors.toMap(Comment::getId, comment -> comment));
        // 4. 转换结果
        List<CommentInfoVo> vos = notificationPage.getData().stream()
                .map(notification -> {
                    Comment comment = comments.get(notification.getTypeId());
                    return comment != null ? convertToVo(notification, comment) : null;
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, notificationPage.getNextCursor());
    }

    private CommentInfoVo convertToVo(Notification notification, Comment comment) {
        CommentInfoVo vo = new CommentInfoVo();
        vo.setId(comment.getId());
        vo.setPostId(comment.getPostId());
        vo.setParentId(comment.getParentId());
        vo.setContent(comment.getContent());
        vo.setLikeCount(comment.getLikeCount());
        vo.setIsRead(notification.getIsRead());
        vo.setCreatedTime(notification.getCreateTime());
        vo.setUserId(comment.getUserId());
        User user=userMapper.selectByPrimaryKey(comment.getUserId());
        vo.setAvatar(user.getAvatar());
        vo.setAccount(user.getAccount());
        Post post=postMapper.selectByPrimaryKey(comment.getPostId());
        vo.setTitle(post.getTitle());
        return vo;
    }
    // ------------------------ 8. 获取点赞信息 ------------------------

    public PageResultVo<LikeNotificaionVo> getLikeNotifications(Long userId, LikeNotificaionQuery query) {
        // 1. 执行游标分页查询
        CursorPageUtil.PageResult<Notification> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("receiverId", userId);//接收者提取
                    params.put("type", 2); // 2代表点赞类型
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return notificationMapper.selectLikeNotifications(params);
                },
                notification -> String.valueOf(notification.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );
        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(Collections.emptyList(), null);
        }

        // 2. 提取点赞ID和发送者ID
        List<Long> likeIds = pageResult.getData().stream()
                .map(Notification::getTypeId)
                .collect(Collectors.toList());
        //提取点赞id
        List<Long> senderIds = pageResult.getData().stream()
                .map(Notification::getSenderId)
                .collect(Collectors.toList());
        // 3. 批量查询点赞记录
        Map<Long, Like> likes = likeMapper.selectByIds(likeIds).stream()
                .collect(Collectors.toMap(Like::getId, like -> like));

        // 4. 提取博文ID和用户ID
        List<Long> postIds = likes.values().stream()
                .map(Like::getTargetId)
                .collect(Collectors.toList());

        // 3. 批量查询用户信息和博文信息
        Map<Long, User> users = userMapper.selectByIds(senderIds).stream()
                .collect(Collectors.toMap(User::getId, user -> user));
        Map<Long, Post> posts = postMapper.selectByIds(postIds).stream()
                .collect(Collectors.toMap(Post::getId, post -> post));


        // 4. 转换结果
        List<LikeNotificaionVo> vos = pageResult.getData().stream()
                .map(notification -> {
                    User user = users.get(notification.getSenderId());
                    Post post = posts.get(likes.get(notification.getTypeId()).getTargetId());
                    return convertToVo(notification, user, post);
                })
                .collect(Collectors.toList());


        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }


    private LikeNotificaionVo convertToVo(Notification notification, User user, Post post) {
        LikeNotificaionVo vo = new LikeNotificaionVo();
        vo.setUserId(user.getId());
        vo.setAccount(user.getAccount());
        vo.setPostId(post.getId());
        vo.setCreatedTime(notification.getCreateTime());
        vo.setTitle(post.getTitle());
        vo.setIsRead(notification.getIsRead());
        vo.setCover(user.getAvatar());
        vo.setId(notification.getTypeId());
        return vo;
    }

    // ------------------------ 公告通知信息 ------------------------

    /**
     * 获取用户公告通知列表
     * @param userId 用户ID
     * @param query 查询参数
     * @return 分页结果
     */
    public PageResultVo<AnnouncementDataUserVo> getAnnouncementNotification(Long userId, AnnouncementDataUserQuery query) {
        // 1. 执行游标分页查询公告通知
        CursorPageUtil.PageResult<Notification> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("receiverId", userId);
                    params.put("type", 3); // 3代表公告类型
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return notificationMapper.selectAnnouncementNotifications(params);
                },
                notification -> String.valueOf(notification.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );
        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(Collections.emptyList(), null);
        }
        // 2. 提取公告ID
        List<Long> announcementIds = pageResult.getData().stream()
                .map(Notification::getTypeId)
                .collect(Collectors.toList());

        if (announcementIds.isEmpty()) {
            return new PageResultVo<>(Collections.emptyList(), null);
        }

        // 3. 批量查询公告信息
        List<Announcement> announcements = announcementMapper.selectByIds(announcementIds);
        log.info("[调试] 公告信息查询结果数量: {}", announcements);
        // 4. 转换结果
        List<AnnouncementDataUserVo> vos = pageResult.getData().stream()
                .map(notification -> {
                    Announcement announcement = announcements.stream()
                            .filter(a -> a.getId().equals(notification.getTypeId()))
                            .findFirst()
                            .orElse(null);
                    return announcement != null ? convertToVo(notification, announcement) : null;
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private AnnouncementDataUserVo convertToVo(Notification notification, Announcement announcement) {
        AnnouncementDataUserVo vo = new AnnouncementDataUserVo();
        vo.setId(announcement.getId());
        vo.setTitle(announcement.getTitle());
        vo.setUpdateTime(announcement.getUpdateTime());
        vo.setIsRead(notification.getIsRead());
        vo.setContent(announcement.getContent());
        vo.setCreatedTime(announcement.getCreateTime());
        vo.setPublishedId(announcement.getPublisherId());
        return vo;
    }

    // ------------------------ 获取我加入的群组信息 ------------------------

    /**
     * 获取我加入的群组信息
     * @param userId 用户ID
     * @param query 查询参数
     * @return 分页结果
     */
    public PageResultVo<MyJoinTeamVo> getMyJoinTeamInfo(Long userId, MyJoinTeamQuery query) {
        // 1. 执行游标分页查询
        log.info("[调试] 执行 getMyJoinTeamInfo 查询，参数: userId={}, size={}, lastCursor={}",userId, query.getSize(), query.getLastCursor());
        CursorPageUtil.PageResult<TeamMember> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    teamMemberMapper.selectByUserId(params);
                    log.info("[调试] 执行 selectByUserId 查询，参数: userId={}, size={}, lastCursor={}", params.get("userId"), params.get("size"), params.get("lastCursor"));
                    List<TeamMember> members = teamMemberMapper.selectByUserId(params);
                    log.info("[调试] selectByUserId 查询结果数量: {}", members != null ? members.size() : 0);
                    return members;
                },
                teamMember -> String.valueOf(teamMember.getTeamId()),
                query.getSize(),
                query.getLastCursor()
        );

        // 2. 提取群组ID
        List<Long> teamIds = pageResult.getData().stream()
                .map(TeamMember::getTeamId)
                .collect(Collectors.toList());
        log.info("teamIds: {}", teamIds);
        if(teamIds==null||teamIds.size()==0||teamIds.isEmpty())
        {
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }
        // 3. 批量查询群组信息
        List<Team> teams = teamMapper.selectByIds(teamIds);

        // 4. 转换结果
        List<MyJoinTeamVo> vos = teams.stream()
                .map(team -> {
                    MyJoinTeamVo vo = new MyJoinTeamVo();
                    vo.setId(team.getId());
                    vo.setName(team.getName());
                    vo.setLogo(team.getLogo());
                    vo.setCreatorId(team.getCreatorId());
                    vo.setMaxMembers(team.getMaxMembers());
                    vo.setCreateTime(team.getCreateTime());
                    vo.setType(team.getCreatorId().equals(userId) ? 0 : 1);
                    return vo;
                })
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    public PageResultVo<FindChallengeNotificationsVo> findChallengeNotifications(Long userId, Byte type, Integer size, String lastCursor) {
        log.info("【开始查询挑战通知】userId={}, type={}, size={}, lastCursor={}", userId, type, size, lastCursor);

        // 实际查询数量：多查1条用于判断是否有下一页
        int querySize = size != null ? size + 1 : 11;

        CursorPageUtil.PageResult<Notification> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("receiverId", userId);
                    params.put("type", type);
                    params.put("size", querySize); // 使用querySize进行查询
                    params.put("lastCursor", lastCursor);
                    return notificationMapper.selectAnnouncementNotifications(params);
                },
                notification -> String.valueOf(notification.getId()),
                size,
                lastCursor
        );
        log.info("【分页查询完成】总数据量={}, 是否有下一页={}", pageResult.getData().size(), pageResult.getNextCursor() != null);

        if (pageResult.getData().isEmpty()) {
            log.info("【空结果】未查询到任何通知");
            return new PageResultVo<>(Collections.emptyList(), null);
        }

        List<FindChallengeNotificationsVo> vos = new ArrayList<>();
        int expiredCount = 0;
        int validCount = 0;

        for (Notification notification : pageResult.getData()) {
            Challenge challenge = challengeMapper.selectById(notification.getTypeId());
            if (!challenge.getEndTime().after(new java.util.Date())) {
                notification.setIsRead(true);
                int updateCount = notificationMapper.updateByPrimaryKey(notification);
            } else {
                vos.add(new FindChallengeNotificationsVo(
                        challenge.getId(),
                        notification.getContent(),
                        challenge.getCreateTime()
                ));
            }
        }

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }



    public PageResultVo<ChallengeCreateVo> getChallengeCreate(Long userId, ChallengeCreateQuery query) {
        // 1. 执行游标分页查询参与记录
        CursorPageUtil.PageResult<Challenge> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return challengeMapper.selectChallengesById(params);
                },
                challenge -> String.valueOf(challenge.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );
        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }

        // 2. 批量查询关联的挑战信息
        List<Long> challengeIds = pageResult.getData().stream()
                .map(Challenge::getId)
                .collect(Collectors.toList());
        List<Challenge> challenges = challengeMapper.selectByIds(challengeIds);
// 原地反转列表（直接修改原列表）
//        Collections.reverse(challenges);

// 打印反转后的ID（验证）
//        // 3. 查询创建者账号信息
//        Map<Long, String> creatorAccounts = challenges.stream()
//                .collect(Collectors.toMap(
//                        Challenge::getCreatorId,
//                        challenge -> userMapper.selectAccountById(challenge.getCreatorId())
//                ));
        Map<Long, String> creatorAccounts = new HashMap<>();
        for (Challenge challenge : challenges) {
            Long creatorId = challenge.getCreatorId();
            if (!creatorAccounts.containsKey(creatorId)) {  // 避免重复查询
                String account = userMapper.selectAccountById(creatorId);
                creatorAccounts.put(creatorId, account);
            }
        }

        // 4. 转换结果
        List<ChallengeCreateVo> vos = challenges.stream()
                .map(challenge -> convertToVo_1(challenge, creatorAccounts.get(challenge.getCreatorId())))
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private ChallengeCreateVo convertToVo_1(Challenge challenge, String creatorAccount) {
        ChallengeCreateVo vo = new ChallengeCreateVo();
        vo.setId(challenge.getId());
        vo.setTitle(challenge.getTitle());
        vo.setCreatorAccount(creatorAccount);
        vo.setObjectType(challenge.getObjectType());
        vo.setGestureType(challenge.getGestureType());
        vo.setLandmarkName(challenge.getLandmarkName());
        vo.setParticipants(challenge.getParticipants());
        vo.setImages(challenge.getImages());
        vo.setEndTime(challenge.getEndTime());
        vo.setRadius(challenge.getRadius());
        vo.setLocation(Location.fromBytes(challenge.getLocation()));
        vo.setDescription(challenge.getDescription());
        vo.setCover(getFirstFileFromJsonArray(challenge.getImages()));
        vo.setCreatorId(challenge.getCreatorId());
        vo.setStartTime(challenge.getStartTime());
        vo.setTeamId(challenge.getTeamId());
        vo.setCreateTime(challenge.getCreateTime());


        return vo;
    }

}







