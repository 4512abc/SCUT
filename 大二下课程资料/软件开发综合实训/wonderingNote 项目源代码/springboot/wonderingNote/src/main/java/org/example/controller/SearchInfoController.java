package org.example.controller;

import com.github.pagehelper.Page;
import com.github.pagehelper.PageInfo;
import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.model.entity.*;
import org.example.model.query.SearchInfoQuery.*;
import org.example.model.vo.SearchInfoVo.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.web.bind.annotation.*;
import org.example.service.SearchInfoService;

import java.util.Date;

@Slf4j
@RestController
@RequestMapping("/api/admin")
public class SearchInfoController {

    @Autowired
    private SearchInfoService searchInfoService;

    @GetMapping("/users/search")
    public Result<PageInfo<SearchUserVo>> searchForUsers(@RequestParam(defaultValue = "1") Integer pageNum,
                                                         @RequestParam(defaultValue = "10") Integer pageSize,
                                                         @RequestParam(required = false) String accessLevel,
                                                         @RequestParam(required = false) String userAccount,
                                                         @RequestParam(required = false) String status,
                                                         @RequestParam(required = false) String email,
                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date startTime,
                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date endTime){

        SearchUserQuery searchUserQUery = new SearchUserQuery();
        searchUserQUery.setAccessLevel(accessLevel);
        searchUserQUery.setUserAccount(userAccount);
        searchUserQUery.setStatus(status);
        searchUserQUery.setEmail(email);
        searchUserQUery.setStartTime(startTime);
        searchUserQUery.setEndTime(endTime);
        //log.info("searchForUsers"+searchUserQUery);
        return Result.success(searchInfoService.searchForUsers(pageNum, pageSize, searchUserQUery));

    }
    @GetMapping("/challenges/search")
    public Result<PageInfo<SearchChallengeVo>> searchForChallenges(@RequestParam(defaultValue = "1") Integer pageNum,
                                                                   @RequestParam(defaultValue = "10") Integer pageSize,
                                                                   @RequestParam(required = false) String title,
                                                                   @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date startTime,
                                                                   @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date endTime) {
        SearchChallengeQuery searchChallengeQuery = new SearchChallengeQuery();
        searchChallengeQuery.setTitle(title);
        searchChallengeQuery.setStartTime(startTime);
        searchChallengeQuery.setEndTime(endTime);
        log.info("searchForChallenges"+searchChallengeQuery);
        return Result.success(searchInfoService.searchForChallenges(pageNum, pageSize, searchChallengeQuery));

    }

    @GetMapping("/posts/search")
    public Result<PageInfo<SearchPostVo>> searchForPosts(@RequestParam(defaultValue = "1") Integer pageNum,
                                                         @RequestParam(defaultValue = "10") Integer pageSize,
                                                         @RequestParam(required = false) String title,
                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date startTime,
                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date endTime) {
        SearchPostQuery searchPostQuery = new SearchPostQuery();
        searchPostQuery.setTitle(title);
        searchPostQuery.setStartTime(startTime);
        searchPostQuery.setEndTime(endTime);
        log.info("searchForPosts"+searchPostQuery);
        return Result.success(searchInfoService.searchForPosts(pageNum, pageSize, searchPostQuery));

    }

    @GetMapping("/announcements/search")
    public Result<PageInfo<SearchAnnouncementVo>> searchForAnnouncements(@RequestParam(defaultValue = "1") Integer pageNum,
                                                                         @RequestParam(defaultValue = "10") Integer pageSize,
                                                                         @RequestParam(required = false) String title,
                                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date startTime,
                                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date endTime,
                                                                         @RequestParam(required = false)Integer type){
        SearchAnnouncementQuery searchPostQuery = new SearchAnnouncementQuery();
        searchPostQuery.setTitle(title);
        searchPostQuery.setStartTime(startTime);
        searchPostQuery.setEndTime(endTime);
        searchPostQuery.setType(type);
        log.info("searchForAnnouncements"+searchPostQuery);
        return Result.success(searchInfoService.searchForAnnouncements(pageNum, pageSize, searchPostQuery));

    }

    @GetMapping("/team/search")
    public Result<PageInfo<SearchTeamVo>> searchForTeams(@RequestParam(defaultValue = "1") Integer pageNum,
                                                         @RequestParam(defaultValue = "10") Integer pageSize,
                                                         @RequestParam(required = false) String name,
                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date startTime,
                                                         @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss") Date endTime) {
        SearchTeamQuery searchTeamQuery = new SearchTeamQuery();
        searchTeamQuery.setName(name);
        searchTeamQuery.setStartTime(startTime);
        searchTeamQuery.setEndTime(endTime);
        log.info("searchForTeams"+searchTeamQuery);
        return Result.success(searchInfoService.searchForTeams(pageNum, pageSize, searchTeamQuery));

    }

    @GetMapping("/team/{team_id}")
    public Result<PageInfo<TeamChallengeListVo>> getTeamInfo(@RequestParam(defaultValue = "1") Integer pageNum,
                                                         @RequestParam(defaultValue = "10") Integer pageSize,
                                                         @PathVariable("team_id") Long teamId) {
        log.info("getTeamInfo"+teamId);
        return Result.success(searchInfoService.getTeamInfo(pageNum, pageSize, teamId));
    }
}
