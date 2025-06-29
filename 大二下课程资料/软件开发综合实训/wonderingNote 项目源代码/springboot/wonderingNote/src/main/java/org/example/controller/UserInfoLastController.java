package org.example.controller;

import org.example.common.result.Result;
import org.example.model.query.UserInfoLastQuery.UserInfoLastQuery;
import org.example.model.vo.UserInfoLastVo.UserCommentPostVo;
import org.example.model.vo.UserInfoLastVo.UserInfoLastSetVo;
import org.example.model.vo.UserInfoLastVo.UserInfoLikeAndCommentVo;
import org.example.service.UserInfoLastService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.model.dto.UserMsgDto.HomeInfoDto;
import org.example.model.query.UserMsgQuery.*;
import org.example.model.query.UserUpdateQuery.UserUpdateQuery;
import org.example.model.vo.UserMsgVo.*;
import org.example.model.vo.common.PageResultVo;
import org.example.service.UserMsgService;
import org.example.utils.JWTUtils;
import org.springframework.web.bind.annotation.*;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;

@RestController
@RequestMapping("/api/admin/users")
public class UserInfoLastController {

    @Autowired
    private UserInfoLastService userInfoLastService;

    @PostMapping("/{user_id}/set_state")
    public Result<UserInfoLastSetVo> setUserState(@PathVariable("user_id") Long userId, @RequestBody UserInfoLastQuery query) {
        return Result.success( userInfoLastService.setUserState(userId, query.getUserState()));
    }

    @GetMapping("/{user_id}/data")
    public Result<UserInfoLikeAndCommentVo> getUserLikeAndCommentCount(@PathVariable("user_id") Long userId) {
        return Result.success(userInfoLastService.getUserLikeAndCommentCount(userId));
    }

    @GetMapping("/{user_id}/user_info")
    public Result<PageResultVo<UserCommentPostVo>> getUserComments(
            @PathVariable("user_id") Long userId,
            @RequestParam(value = "size", required = false) Integer size,
            @RequestParam(value = "lastCursor", required = false) String lastCursor) {
        return Result.success(userInfoLastService.getUserComments(userId, size, lastCursor));
    }
}
