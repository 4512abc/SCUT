package org.example.controller;

import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.model.query.TeamQuery.*;
import org.example.model.vo.Team.UserCheckVo;
import org.example.model.query.TeamQuery.PostInvQuery;
import org.example.service.TeamService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.example.utils.JWTUtils;
import org.example.model.vo.Team.TeamDetailVo;

import java.util.Map;

@Slf4j
@RestController
@RequestMapping(value="/api/teams")
public class TeamController {
    @Autowired
    private TeamService teamService;

    @PostMapping("/create")
    public Result createTeam(@RequestBody CreateTeamQuery createTeamQuery,@RequestHeader("Authorization")String token) {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        //调用方法，插入数据库
        return Result.success(teamService.createTeam(createTeamQuery,(long) claims.get("id")));
    }

    @PostMapping("/{team_id}/join")
    public Result joinTeam(@PathVariable Long team_id,@RequestHeader("Authorization")String token) {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        //调用方法
        return Result.success(teamService.joinTeam(team_id,(long) claims.get("id")));
    }

    @GetMapping("/{team_id}/members")
    public Result getTeamMembers(@PathVariable Long team_id, @RequestParam Integer size, @RequestParam(required = false) String lastCursor) {
        // 调用服务层方法获取团队成员列表
        return Result.success(teamService.getTeamMembers(team_id, size, lastCursor));
    }

    @DeleteMapping("/{team_id}/members")
    public Result deleteMember(@PathVariable Long team_id, @RequestHeader("Authorization")String token, @RequestBody DeleteMemberQuery deleteMemberQuery) {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        //调用方法
        return Result.success(teamService.deleteMember(team_id,(long) claims.get("id"),deleteMemberQuery.getUser_id()));
    }


    @PostMapping("/{team_id}/notifications")
    public Result sendNotification(@PathVariable Long team_id, @RequestHeader("Authorization")String token) {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        //调用方法
        return Result.success(teamService.sendNotification(team_id,(long) claims.get("id")));
    }

    @PostMapping("/{team_id}/challenge_inv")
    public Result sendChallengeInvitation(@PathVariable Long team_id, @RequestHeader("Authorization")String token, @RequestBody ChallengeInvQuery challengeInvQuery) {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        //调用方法
        return Result.success(teamService.sendChallengeInvitation(team_id,(long) claims.get("id"),challengeInvQuery.getChallenge_id()));
    }

    @PostMapping("/{team_id}/check_user")
    public Result failCheck(@PathVariable Long team_id,
                            @RequestBody UserCheckQuery userCheckQuery,
                            @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        return Result.success(teamService.getTeamUserCheck(team_id, userCheckQuery,(long) claims.get("id"), userCheckQuery.getSize(), userCheckQuery.getLastCursor()));
    }

    @GetMapping("/{check_id}")
    public Result getCheckInfo(@PathVariable Long check_id) {
        return Result.success(teamService.getCheckInfo(check_id));
    }

    @PostMapping("/{check_id}/modify")
    public Result modifyCheckInfo(@PathVariable Long check_id, @RequestBody CheckModifyQuery sendNotificationVo) {
        teamService.modifyCheckInfo(check_id, sendNotificationVo);
        return Result.success();
    }

    @PostMapping("/{team_id}/invite")
    public Result inviteMember(@PathVariable Long team_id, @RequestBody InviteMemberQuery inviteMemberQuery, @RequestHeader("Authorization")String token) {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        //调用方法
        return Result.success(teamService.inviteMember(team_id,(long) claims.get("id"),inviteMemberQuery));
    }


    @GetMapping("/{team_id}/info")
    public Result getTeamInfo(@PathVariable("team_id") Long teamId) {
        TeamDetailVo teamInfo = teamService.getTeamInfo(teamId);
        return Result.success(teamInfo);
    }

    @PostMapping("/{team_id}/post_inv")
    public Result postInvitation(@PathVariable Long team_id, @RequestHeader("Authorization")String token, @RequestBody PostInvQuery postInvQuery) {
        Map<String,Object> claims=JWTUtils.getClaims(token);
        //调用方法
        return Result.success(teamService.sendPostInvitation(team_id,(long) claims.get("id"),postInvQuery));
    }

    @GetMapping("/{team_id}/challenge_info")
    public Result getChallengeInfo(@PathVariable Long team_id,
                                   @RequestParam String lastCursor,
                                   @RequestParam Integer size) {
        //调用方法
        return Result.success(teamService.getChallengeInfo(team_id,size, lastCursor));
    }

}

