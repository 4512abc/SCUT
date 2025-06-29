package org.example.controller;

import org.example.common.result.Result;
import org.example.service.HomeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/admin/top_page")
public class HomeController {

    @Autowired
    private HomeService homeService;

    @GetMapping("/Sys_number")
    public Result getSystemNumbers() {
        return  Result.success(homeService.getSystemNumbers());
    }

    @GetMapping("/challenge_level")
    public Result getChallengeLevel() {
        return Result.success(homeService.getChallengeLevel());
    }

    @GetMapping("/challenge_data")
    public Result getMonthlyData() {
        return Result.success(homeService.getMonthlyData());
    }

    @GetMapping("/announcement_data")
    public Result getAnnouncements() {
        return Result.success(homeService.getAnnouncements());
    }
}