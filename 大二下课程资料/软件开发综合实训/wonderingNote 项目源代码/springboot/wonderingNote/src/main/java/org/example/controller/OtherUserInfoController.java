package org.example.controller;

import org.example.common.result.Result;
import org.example.model.query.OtherUserInfoQuery.ChallengeListQuery;
import org.example.model.query.OtherUserInfoQuery.PostListQuery;
import org.example.model.vo.OtherUserInfoVo.ChallengeListVo;
import org.example.model.vo.OtherUserInfoVo.PostListVo;
import org.example.model.vo.OtherUserInfoVo.UserInfoVo;
import org.example.model.vo.common.PageResultVo;
import org.example.service.OtherUserInfoService;
import org.springframework.web.bind.annotation.*;

/**
 * 其他用户信息控制器
 * 提供获取其他用户信息、挑战列表和帖子列表的API接口
 */
@RestController
@RequestMapping("/api/users")
public class OtherUserInfoController {
    private final OtherUserInfoService userService;

    /**
     * 构造器注入服务依赖
     */
    public OtherUserInfoController(OtherUserInfoService userService) {
        this.userService = userService;
    }

    /**
     * 获取用户基本信息
     * @param userId 用户ID
     * @return 用户信息结果
     */
    @GetMapping("/{user_id}")
    public Result<UserInfoVo> getUserInfo(
            @PathVariable("user_id") Long userId) {
        return Result.success(userService.getUserInfo(userId));
    }

    /**
     * 获取用户挑战列表
     * @param userId 用户ID
     * @param size 每页大小
     * @param lastCursor 上一页最后一条记录的游标
     * @param sort 排序方式
     * @return 分页结果
     */
    @GetMapping("/{user_id}/challenges")
    public Result<PageResultVo<ChallengeListVo>> getChallengeList(
            @PathVariable("user_id") Long userId,
            @RequestParam(required = false) Integer size,
            @RequestParam(required = false) String lastCursor,
            @RequestParam(required = false) String sort) {
        ChallengeListQuery query = new ChallengeListQuery();
        query.setSize(size);
        query.setLastCursor(lastCursor);
        query.setSort(sort);
        return Result.success(userService.getChallengeList(userId, query));
    }

    /**
     * 获取用户帖子列表
     * @param userId 用户ID
     * @param size 每页大小（默认12）
     * @param sort 排序方式（默认按时间）
     * @param lastCursor 上一页最后一条记录的游标
     * @return 分页结果
     */
    @GetMapping("/{user_id}/posts")
    public Result<PageResultVo<PostListVo>> getPostList(
            @PathVariable("user_id") Long userId,
            @RequestParam(required = false, defaultValue = "12") Integer size,
            @RequestParam(required = false, defaultValue = "time") String sort,
            @RequestParam(required = false) String lastCursor) {

        PostListQuery query = new PostListQuery();
        query.setSize(size);
        query.setSort(sort);
        query.setLastCursor(lastCursor);

        return Result.success(userService.getPostList(userId, query));
    }
}