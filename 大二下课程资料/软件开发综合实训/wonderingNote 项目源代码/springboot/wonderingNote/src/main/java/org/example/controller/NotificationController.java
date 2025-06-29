package org.example.controller;

import org.example.common.result.Result;
import org.example.model.query.NotificatonQuery.*;
import org.example.model.query.NotificatonQuery.AnnouncementIsreadQuery;
import org.example.model.query.NotificatonQuery.CommentCreateQuery;
import org.example.model.query.NotificatonQuery.CommentIsreadQuery;
import org.example.model.query.NotificatonQuery.LikeIsNotQuery;
import org.example.model.query.NotificatonQuery.LikeIsreadQuery;
import org.example.model.vo.NotificationVo.AnnouncementIsreadVo;
import org.example.model.vo.NotificationVo.CommentCreateVo;
import org.example.model.vo.NotificationVo.CommentIsreadVo;
import org.example.model.vo.NotificationVo.LikeIsNotVo;
import org.example.model.vo.NotificationVo.LikeIsreadVo;
import org.example.service.NotificationService;
import org.example.utils.JWTUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

/**
 * 通知相关接口控制器
 */
@RestController
@RequestMapping("/api/v1")
public class NotificationController {

    @Autowired
    private NotificationService notificationService;

    // 更新点赞已读状态
    @PostMapping("/like/{id}")
    public Result updateLikeIsRead(@PathVariable Long id, @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        LikeIsreadQuery query = new LikeIsreadQuery();
        query.setId(id);
        LikeIsreadVo vo = notificationService.updateLikeIsRead(userId, query);
        return Result.success(vo);
    }

    // 更新评论已读状态
    @PostMapping("/comment/{id}")
    public Result updateCommentIsRead(@PathVariable Long id, @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        CommentIsreadQuery query = new CommentIsreadQuery();
        query.setId(id);
        CommentIsreadVo vo = notificationService.updateCommentIsRead(userId, query);
        return Result.success(vo);
    }

    // 更新公告已读状态
    @PostMapping("/annoucement/{id}")
    public Result updateAnnouncementIsRead(@PathVariable Long id, @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        AnnouncementIsreadQuery query = new AnnouncementIsreadQuery();
        query.setId(id);
        AnnouncementIsreadVo vo = notificationService.updateAnnouncementIsRead(userId, query);
        return Result.success(vo);
    }

    // 创建评论
    @PostMapping("/comments/{id}")
    public Result createComment(@PathVariable("id") Long postId, @RequestBody CommentCreateQuery query,
                                @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        CommentCreateVo vo = notificationService.createComment(postId, query, userId);
        return Result.success(vo);
    }

    // 获取评论列表（分页）
    @GetMapping("/comments/{id}")
    public Result getCommentList(@PathVariable("id") Long postId,
                                 @RequestParam(value = "size", defaultValue = "20") Integer size,
                                 @RequestParam(value = "sort", required = false) String sort,
                                 @RequestParam(value = "lastCursor", required = false) String lastCursor) {
        CommentListQuery query = new CommentListQuery();
        query.setPostId(postId);
        query.setSize(size);
        query.setSort(sort);
        query.setLastCursor(lastCursor);
        return Result.success(notificationService.getCommentList(query));
    }

    // 点赞/取消点赞帖子
    @PostMapping("/interactions/{post_id}")
    public Result likeOrUnlikePost(@PathVariable("post_id") Long postId,
                                   @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        LikeIsNotQuery query = new LikeIsNotQuery();
        query.setPostId(postId);
        query.setUserId(userId);
        LikeIsNotVo vo = notificationService.likeOrUnlikePost(query);
        return Result.success(vo);
    }

    // 获取更多评论（分页）
    @GetMapping("/comments/much")
    public Result getMoreCommentList(
            @RequestParam(value = "root_id", required = false) Long rootId,
            @RequestParam(value = "size", defaultValue = "20") Integer size,
            @RequestParam(value = "sort", required = false) String sort,
            @RequestParam(value = "lastCursor", required = false) String lastCursor) {
        MoreCommentListQuery query = new MoreCommentListQuery();
        query.setRootId(rootId);
        query.setSize(size);
        query.setSort(sort);
        query.setLastCursor(lastCursor);
        return Result.success(notificationService.getMoreCommentList(query));
    }
}