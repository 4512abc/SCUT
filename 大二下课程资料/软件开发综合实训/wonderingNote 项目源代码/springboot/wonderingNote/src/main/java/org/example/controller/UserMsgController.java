//由TOTORO编辑

package org.example.controller;

import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.mapper.NotificationMapper;
import org.example.model.dto.UserMsgDto.HomeInfoDto;
import org.example.model.query.UserMsgQuery.*;
import org.example.model.query.UserUpdateQuery.UserUpdateQuery;
import org.example.model.vo.UserMsgVo.*;
import org.example.model.vo.common.PageResultVo;
import org.example.service.UserMsgService;
import org.example.utils.JWTUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.Map;

import static org.example.common.result.ResultCode.UPDATE_SUCCESS;

/**
 * 用户信息控制器
 * 提供用户主页、群组、帖子、点赞、挑战、公告、评论等信息的查询接口
 * 所有接口路径前缀为：/auth
 *
 * 主要功能：
 * 1. 获取用户主页基础信息和资料信息
 * 2. 查询用户相关的群组信息
 * 3. 查询用户发布的帖子信息
 * 4. 查询用户点赞记录
 * 5. 查询用户参与的挑战信息
 * 6. 查询系统公告信息
 * 7. 查询用户评论记录
 */
@RestController
@Slf4j
@RequestMapping("/api/auth")
public class UserMsgController {

    private final UserMsgService userMsgService;

    @Autowired
    private NotificationMapper notificationMapper;

    /**
     * 构造器注入UserMsgService
     * @param userMsgService 用户信息服务
     */
    public UserMsgController(UserMsgService userMsgService) {
        this.userMsgService = userMsgService;
    }


    /**
     * 获取用户主页信息
     * @param query 查询参数对象，包含可能的筛选条件
     * @return 包含用户主页信息的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/home_info")
    public Result<HomeInfoVo> getHomeInfo(HomeInfoQuery query,@RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getHomeInfoVo(userId));
    }


    // ------------------------ 2. 群组信息接口 ------------------------

    /**
     * 获取用户群组列表
     * @param query 包含分页和排序参数的查询对象
     * @return 包含分页结果的群组列表的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/team_info")
    public Result<PageResultVo<TeamInfoVo>> getTeamInfo(TeamInfoQuery query,@RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        //传入user_id和query
        return Result.success(userMsgService.getTeamInfo(userId, query));
    }

    // ------------------------ 获取我加入的群组信息接口 ------------------------

    /**
     * 获取我加入的群组信息
     * @param query 查询参数对象，包含分页和排序参数
     * @param token JWT token
     * @return 包含分页结果的群组列表的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/team_join")
    public Result<PageResultVo<MyJoinTeamVo>> getMyJoinTeamInfo(MyJoinTeamQuery query, @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getMyJoinTeamInfo(userId, query));
    }

    // ------------------------ 3. 帖子信息接口 ------------------------

    /**
     * 从token中获取用户ID，并进行校验
     * @param token JWT token
     * @return 用户ID
     * @throws IllegalArgumentException 当token无效或未包含用户ID时抛出
     */
    private Long getUserIdFromToken(String token) {
        if (token == null || token.isEmpty()) {
            throw new IllegalArgumentException("Token不能为空");
        }

        Map<String, Object> claims = JWTUtils.getClaims(token);
        if (claims == null) {
            throw new IllegalArgumentException("Token解析失败");
        }

        Object idObj = claims.get("id");
        if (idObj == null) {
            throw new IllegalArgumentException("Token中未包含用户ID");
        }

        try {
            return Long.valueOf(idObj.toString());
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("用户ID格式错误");
        }
    }

    /**
     * 获取用户帖子列表
     * @param query 查询参数对象，包含分页、排序和筛选条件
     * @return 包含分页结果的帖子列表的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/posts_info")
    public Result<PageResultVo<PostsInfoVo>> getPostsInfo(@RequestHeader("Authorization") String token,
                                                          @ModelAttribute PostsInfoQuery query) {
        log.info("[调试] 收到获取帖子请求");
        log.info("[调试] Token: {}", token);
        log.info("[调试] 查询参数: {}", query);
        log.info("[调试] 查询参数: {}", query.getLastCursor());
        log.info("[调试] 查询参数: {}", query.getSort());
        log.info("[参数详情] 完整查询对象: {}", query); // 新增
        log.info("[参数详情] size={}, last_id={}, sort={}",
                query.getSize(), query.getLastCursor(), query.getSort()); // 新增
        Long userId = getUserIdFromToken(token);
        log.info("[调试] 解析出的用户ID: {}", userId);

        log.info("[调试] 开始调用userMsgService.getPostsInfo");
        PageResultVo<PostsInfoVo> result = userMsgService.getPostsInfo(userId, query);
        log.info("[调试] userMsgService.getPostsInfo调用完成，返回结果: {}", result);

        // 添加更详细的结果调试日志
        if (result != null && result.getData() != null) {
            log.info("[调试] 查询到的博文数量: {}", result.getData().size());
            log.info("[调试] 下一页游标: {}", result.getNextCursor());

            for (PostsInfoVo post : result.getData()) {
                log.info("[调试] 博文详情 - ID: {}, 标题: {}, 浏览量: {}, 点赞数: {}, 评论数: {}, 创建时间: {}, 位置: {}，时间戳： {}",
                        post.getId(),
                        post.getTitle(),
                        post.getViewCount(),
                        post.getLikeCount(),
                        post.getCommentCount(),
                        post.getCreateTime(),
                        post.getLocation(),
                        post.getCreateTime().getTime()
                );
            }
        } else {
            log.info("[调试] 未查询到博文数据或结果为空");
        }

        return Result.success(result);
    }
    // ------------------------ 4. 点赞信息接口 ------------------------

    /**
     * 获取用户点赞列表
     * @param query 查询参数对象，包含分页、排序和筛选条件
     * @return 包含分页结果的点赞列表的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/likes_info")
    public Result<PageResultVo<LikesInfoVo>> getLikesInfo(LikesInfoQuery query,@RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getLikesInfo(userId, query));
    }

    // ------------------------ 5. 挑战信息接口 ------------------------

    /**
     * 获取用户挑战信息列表
     * @param query 查询参数对象，包含分页、排序和筛选条件
     * @return 包含分页结果的挑战列表的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/challenge_info")
    public Result<PageResultVo<ChallengeInfoVo>> getChallengeInfo(ChallengeInfoQuery query,@RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getChallengeInfo(userId, query));
    }

    // ------------------------ 6. 公告信息接口 ------------------------

    /**
     * 获取公告列表
     * @param query 查询参数对象，包含分页、排序和筛选条件
     * @return 包含分页结果的公告列表的Result对象
     * @apiNote 此接口不需要用户认证，所有用户均可访问
     */
    @GetMapping("/announcement_info")
    public Result<PageResultVo<AnnouncementInfoVo>> getAnnouncementInfo(AnnouncementInfoQuery query,@RequestHeader("Authorization") String token) {
        return Result.success(userMsgService.getAnnouncementInfo(query));
    }
    @GetMapping("/announcement_infomore")
    public Result<PageResultVo<AnnouncementInfoVo>> getAnnouncementInfomore(AnnouncementInfoQuery query,@RequestHeader("Authorization") String token) {
        return Result.success(userMsgService.getAnnouncementInfomore(query));
    }

    /**
     * 获取公告详情
     * @param id 公告ID
     * @return 包含公告详情的Result对象
     * @apiNote 此接口不需要用户认证，所有用户均可访问
     */
    @GetMapping("/announcement_info/{id}")
    public Result getAnnouncementDetail(@PathVariable Long id,@RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getAnnouncementDetail(userId,id));
    }

    // ------------------------ 7. 评论信息接口 ------------------------

    /**
     * 获取用户评论列表
     * @param query 查询参数对象，包含分页、排序和筛选条件
     * @return 包含分页结果的评论列表的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/comment_info")
    public Result<PageResultVo<CommentInfoVo>> getCommentInfo(CommentInfoQuery query,@RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getCommentInfo(userId, query));
    }

    // ------------------------ 8. 获取点赞信息信息接口 ------------------------
    @GetMapping("/like_notification")
    public Result getLikeNotifications(LikeNotificaionQuery query, @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getLikeNotifications(userId, query));

    }

    // ------------------------ 8. 获取通知挑战信息接口 ------------------------
    @GetMapping("notification/challenge_info")
    public Result<PageResultVo<FindChallengeNotificationsVo>> getChallengeNotifications(
            @RequestParam(value = "size", required = false) Integer size,
            @RequestParam(value = "lastCursor", required = false) String lastCursor,
            @RequestParam(value = "sort", required = false) String sort,
            @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.findChallengeNotifications(userId, (byte) 4, size, lastCursor));
    }

    // ------------------------ 公告通知信息接口 ------------------------

    /**
     * 获取用户公告通知列表
     * @param query 查询参数对象，包含分页、排序和筛选条件
     * @param token JWT token
     * @return 包含分页结果的公告通知列表的Result对象
     * @apiNote 需要用户认证，从Token中获取当前用户ID
     */
    @GetMapping("/announcement_notification")
    public Result<PageResultVo<AnnouncementDataUserVo>> getAnnouncementNotification(AnnouncementDataUserQuery query, @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getAnnouncementNotification(userId, query));
    }


    @GetMapping("/challenge_create")
    public Result<PageResultVo<ChallengeCreateVo>> getChallengeInfo(ChallengeCreateQuery query,@RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(userMsgService.getChallengeCreate(userId, query));
    }


    // ------------------------ 工具方法 ------------------------

    /**
     * 日期格式化工具方法
     * @param date 需要格式化的日期对象
     * @return 格式化后的日期字符串，格式为"yyyy-MM-dd HH:mm:ss"
     */
    private String formatDate(Date date) {
        return date != null ?
                new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date) : null;
    }


}
