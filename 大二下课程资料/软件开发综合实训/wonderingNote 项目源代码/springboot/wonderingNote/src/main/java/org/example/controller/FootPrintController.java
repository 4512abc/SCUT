package org.example.controller;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.model.query.FootPrintQuery.OtherPostLandMarkQuery;
import org.example.model.query.FootPrintQuery.PostLandMarkQuery ;
import org.example.model.query.FootPrintQuery.PostLandMarkQuery;
import org.example.model.vo.FootPrintVo.LandMarkListVo;
import org.example.model.vo.FootPrintVo.OtherPostLandMarkVo;
import org.example.model.vo.FootPrintVo.PostLandMarkVo;
import org.example.model.vo.FootPrintVo.PostLandMarkVo;
import org.example.model.vo.common.PageResultVo;
import org.example.service.FootPrintService;
import org.example.utils.JWTUtils;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;

@RestController
@Slf4j
@RequestMapping("/api/footprint")
public class FootPrintController {

    private final FootPrintService footPrintService;

    public FootPrintController(FootPrintService footPrintService) {
        this.footPrintService = footPrintService;
    }

    @GetMapping("/landmarkList")
    public Result<LandMarkListVo> getLandmarkList(@RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        return Result.success(footPrintService.getLandmarkList(userId));
    }




    @GetMapping("/user_blogs")
    public Result<PageResultVo<PostLandMarkVo>> getLandmarkPosts(
            @RequestHeader("Authorization") String token,
            @RequestParam(required = false) Integer size,
            @RequestParam(required = false) String lastCursor,
            @RequestParam(required = false) String sort,
            @RequestParam(name = "landmark_name", required = false) String landmarkName) {

        // 打印所有传入参数
        log.info("\n====== 请求参数 ======");
        log.info("Token: {}", token);
        log.info("Size: {}", size);
        log.info("LastCursor: {}", lastCursor);
        log.info("Sort: {}", sort);
        log.info("LandMarkName: {}", landmarkName);
        log.info("====================");


        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        log.info("解析出的用户ID: {}", userId);

        PostLandMarkQuery query = new PostLandMarkQuery();
        query.setLandmarkName(landmarkName);
        query.setSort(sort);
        query.setLastCursor(lastCursor);
        query.setSize(size);

        log.info("构建的查询对象: {}", query);

        PageResultVo<PostLandMarkVo> result = footPrintService.getPostsInfo(userId, query);
        return Result.success(result);
    }

    @GetMapping("/other_blogs")
    public Result<PageResultVo<OtherPostLandMarkVo>> getOtherLandmarkPosts(
            @RequestHeader("Authorization") String token,
            @RequestParam(required = false) Integer size,
            @RequestParam(required = false) String lastCursor,
            @RequestParam(required = false) String sort,
            @RequestParam(name = "landmark_name", required = false) String landmarkName) {

        // 打印所有传入参数
        log.info("\n====== 请求参数 ======");
        log.info("Token: {}", token);
        log.info("Size: {}", size);
        log.info("LastCursor: {}", lastCursor);
        log.info("Sort: {}", sort);
        log.info("LandMarkName: {}", landmarkName);
        log.info("====================");


        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        log.info("解析出的用户ID: {}", userId);

        OtherPostLandMarkQuery query = new OtherPostLandMarkQuery();
        query.setLandmarkName(landmarkName);
        query.setSort(sort);
        query.setLastCursor(lastCursor);
        query.setSize(size);

        log.info("构建的查询对象: {}", query);

        PageResultVo<OtherPostLandMarkVo> result = footPrintService.getOtherPostsInfo(userId, query);
        return Result.success(result);
    }
}
