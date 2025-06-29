package org.example.controller;

import org.example.common.result.Result;
import org.example.model.query.AnnouncementQuery.AnnouncementCreatQuery;
import org.example.model.query.AnnouncementQuery.AnnouncementModifyQuery;
import org.example.model.vo.AnnouncementVo.AnnouncementCreatVo;
import org.example.model.vo.AnnouncementVo.AnnouncementModifyVo;
import org.example.service.AnnouncementService;
import org.example.utils.JWTUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/api/admin/announcements")
public class AnnouncementController {

    @Autowired
    private AnnouncementService announcementService;

    @PostMapping("/create")
    public Result<AnnouncementCreatVo> createAnnouncement(
            @RequestBody AnnouncementCreatQuery query,
            @RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        AnnouncementCreatVo result = announcementService.createAnnouncement(userId, query);
        return Result.success(result);
    }

    @PostMapping("/{announcement_id}/modify")
    public Result<AnnouncementModifyVo> modifyAnnouncement(
            @PathVariable("announcement_id") Long announcementId,
            @RequestBody AnnouncementModifyQuery query,
            @RequestHeader("Authorization") String token) {
        Map<String,Object> claims= JWTUtils.getClaims(token);
        Long userId = (long) claims.get("id");
        AnnouncementModifyVo result = announcementService.modifyAnnouncement(userId,announcementId, query);
        return Result.success(result);
    }
}