//获取大厅相关！！！
package org.example.controller;

import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.model.query.hallQuery.ChallengeSearchQuery;
import org.example.model.query.hallQuery.PostQuery;
import org.example.model.query.hallQuery.ChallengeQuery;
import org.example.model.query.hallQuery.PostSearchQuery;
import org.example.model.vo.HallVo.ChallengeSearchVo;
import org.example.model.vo.HallVo.PostSearchVo;
import org.example.model.query.hallQuery.UserSearchQuery;
import org.example.model.vo.HallVo.PostVo;
import org.example.model.vo.HallVo.ChallengeVo;
import org.example.model.vo.common.PageResultVo;
import org.example.service.hallService;
import org.example.utils.JWTUtils;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.Date;
import java.util.List;
import java.util.Map;

@Slf4j
@RestController
@RequestMapping("/api/hall")
public class hallController {

    private final hallService hallService;

    public hallController(hallService hallService) {
        this.hallService = hallService;
    }

    @GetMapping("/posts")
    public Result<PostVo> getPosts(PostQuery query) {
        return Result.success(hallService.getPosts(query));
    }

    @GetMapping("/posts/search")
    public Result<PageResultVo<PostSearchVo>> searchPostsByTitleAndTime(
            @RequestParam(required = false) Integer size,
            @RequestParam(required = false) String lastCursor,
            @RequestParam(required = false) String sort,
            @RequestParam(required = false) String title,
            @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime,
            @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime
    ) {
        log.info("searchPostsByTitleAndTime={}",startTime);
        return Result.success(hallService.searchPostsByTitleAndTime(size, lastCursor, sort, title,startTime, endTime));
    }

    @GetMapping("/challenges")
    public Result<ChallengeVo> getChallenges(ChallengeQuery query) {
        return Result.success(hallService.getChallenges(query));
    }

    @PostMapping("/users/search")
    public Result searchUsers(@RequestBody UserSearchQuery query) {
        return Result.success(hallService.getUser(query));
    }

    @GetMapping("/challenges/search")
    public Result<PageResultVo<ChallengeSearchVo>> searchChallengesByTitleAndTime(
        @RequestParam(required = false) Integer size,
        @RequestParam(required = false) String lastCursor,
        @RequestParam(required = false) String sort,
        @RequestParam(required = false) String title,
        @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime,
        @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime
    ) {
        log.info("searchChallengesByTitleAndTime={},={}",startTime,endTime);
        return Result.success(hallService.searchChallengesByTitleAndTime(size, lastCursor, sort, title,startTime, endTime));
    }


    @GetMapping("/myposts/search")
    public Result<PageResultVo<PostSearchVo>> searchMyPostsByTitleAndTime(
            @RequestParam(required = false) Integer size,
            @RequestParam(required = false) String lastCursor,
            @RequestParam(required = false) String sort,
            @RequestParam(required = false) String title,
            @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime,
            @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime,
            @RequestHeader("Authorization") String token
    ) {
        log.info("searchPostsByTitleAndTime={}",startTime);
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(hallService.searchMyPostsByTitleAndTime(userId,size, lastCursor, sort, title,startTime, endTime));
    }

    @GetMapping("/mychallenges/search")
    public Result<PageResultVo<ChallengeSearchVo>> searchChallengesByTitleAndTime(
            @RequestParam(required = false) Integer size,
            @RequestParam(required = false) String lastCursor,
            @RequestParam(required = false) String sort,
            @RequestParam(required = false) String title,
            @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime,
            @RequestParam(required = false) @DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime,
            @RequestHeader("Authorization") String token
    ) {
        log.info("searchChallengesByTitleAndTime={},={}",startTime,endTime);
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(hallService.searchmyChallengesByTitleAndTime(userId,size, lastCursor, sort, title,startTime, endTime));
    }

}

