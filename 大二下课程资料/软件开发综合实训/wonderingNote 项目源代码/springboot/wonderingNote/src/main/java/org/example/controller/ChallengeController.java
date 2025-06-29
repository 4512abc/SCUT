package org.example.controller;

import org.example.common.result.Result;
import org.example.model.query.ChallengesQuery.CreateChallengeQuery;
import org.example.model.query.ChallengesQuery.SubmitChallengeQuery;
import org.example.model.query.ChallengesQuery.SubmitLocationQuery;
import org.example.service.ChallengeService;
import org.example.utils.JWTUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/api/challenges")
public class ChallengeController {

    @Autowired
    private ChallengeService challengeService;

    @PostMapping("/create")
    public Result createChallenge(@RequestBody CreateChallengeQuery query, @RequestHeader("Authorization")String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        return Result.success(challengeService.createChallenge(query,(long) claims.get("id")).getId());
    }

    @PostMapping("/{challenge_id}/join")
    public Result joinChallenge(@PathVariable Long challenge_id, @RequestHeader("Authorization")String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        return Result.success(challengeService.joinChallenge((long) claims.get("id"),challenge_id));
    }

    @PostMapping("/{challenge_id}/submit")
    public Result submitChallenge(@PathVariable Long challenge_id, @RequestHeader("Authorization")String token, @RequestBody SubmitChallengeQuery query) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
//        return Result.success(challengeService.submitChallenge((long) claims.get("id"),challenge_id), query);
        return Result.success(challengeService.submitChallenge((long) claims.get("id"),challenge_id, query));
    }

    @GetMapping("/{challenge_id}")
    public Result getChallengeInfo(@PathVariable Long challenge_id) {
        return Result.success(challengeService.getChallengeInfo(challenge_id));
    }

    @DeleteMapping("/{challenge_id}/delete")
    public Result deleteChallenge(@PathVariable Long challenge_id, @RequestHeader("Authorization")String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        return Result.success(challengeService.deleteChallenge(challenge_id,(long) claims.get("id")));
    }

    @PostMapping("{challenge_id}/location_submit")
    public Result submitLocation(@PathVariable Long challenge_id, @RequestBody SubmitLocationQuery locationData) {
        if(challengeService.submitLocation(challenge_id,locationData))
        return Result.success(true);
        else{
            return Result.success(false);
        }
    }

    @GetMapping("/{challenge_id}/users")
    public Result getChallengeUsers(@PathVariable Long challenge_id) {
        return Result.success(challengeService.getChallengeUsers(challenge_id));
    }

}

