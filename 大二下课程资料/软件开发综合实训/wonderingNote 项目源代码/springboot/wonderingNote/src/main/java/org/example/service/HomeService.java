package org.example.service;

import org.example.mapper.*;
import org.example.model.entity.User;
import org.example.model.vo.HomeVo.HomeAnnouncementVo;
import org.example.model.vo.HomeVo.HomeChallengeRankVo;
import org.example.model.vo.HomeVo.HomeDataVo;
import org.example.model.vo.HomeVo.HomeMonthDataVo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

@Service
public class HomeService {

    @Autowired
    UserMapper userMapper;

    @Autowired
    PostMapper postMapper;

    @Autowired
    ChallengeMapper challengeMapper;
    @Autowired
    ParticipationMapper participationMapper;
    @Autowired
    AnnouncementMapper announcementMapper;

    public HomeDataVo getSystemNumbers() {
        HomeDataVo homeDataVo = new HomeDataVo();

        // 获取用户总数和今日新增用户数
        Integer userTotal = userMapper.selectUserTotal();
        Integer userAdd = userMapper.selectUserAddToday(new Date());

        // 获取博文总数和今日新增博文数
        Integer postTotal = postMapper.selectPostTotal();
        Integer postAdd = postMapper.selectPostAddToday(new Date());

        // 获取挑战总数和今日新增挑战数
        Integer challengeTotal = challengeMapper.selectChallengeTotal();
        Integer challengeAdd = challengeMapper.selectChallengeAddToday(new Date());

        homeDataVo.setUserTotal(userTotal);
        homeDataVo.setUserAdd(userAdd);
        homeDataVo.setPostTotal(postTotal);
        homeDataVo.setPostAdd(postAdd);
        homeDataVo.setChallengeTotal(challengeTotal);
        homeDataVo.setChallengeAdd(challengeAdd);

        return homeDataVo;
    }

    public List<HomeChallengeRankVo> getChallengeLevel() {
        // 获取完成挑战数前十的用户ID及其完成数

        List<Map<String, Object>> userChallengeCounts = participationMapper.selectTopUsersByChallengeComplete(10);
        if(userChallengeCounts==null){
            return null;
        }

        // 获取这些用户的详细信息
        List<Long> userIds = userChallengeCounts.stream()
                .map(map -> Long.parseLong(map.get("user_id").toString()))
                .collect(Collectors.toList());
        if (userIds.isEmpty()) {
            return Collections.emptyList(); // 直接返回空列表
        }
        Map<Long, User> userMap = userMapper.selectByIds(userIds).stream()
                .collect(Collectors.toMap(User::getId, Function.identity()));

        // 构建返回结果
        return userChallengeCounts.stream()
                .map(map -> {
                    Long userId = Long.parseLong(map.get("user_id").toString());
                    User user = userMap.get(userId);
                    return new HomeChallengeRankVo(
                            user.getAccount(),
                            user.getAvatar(),
                            Integer.parseInt(map.get("number").toString()),
                            userId.toString()
                    );
                })
                .collect(Collectors.toList());
    }

    public List<HomeMonthDataVo> getMonthlyData() {
        // 获取当前月份往前五个月份的博文和挑战总数
        List<HomeMonthDataVo> monthlyData = postMapper.selectMonthlyPostAndChallengeCount();
        return monthlyData;
    }

    public List<HomeAnnouncementVo> getAnnouncements() {
        return Optional.ofNullable(announcementMapper.selectAnnouncements_1())
                .orElseGet(Collections::emptyList) // 如果null则返回空列表
                .stream()
                .filter(Objects::nonNull) // 过滤掉列表中的null元素
                .map(announcement -> new HomeAnnouncementVo(
                        announcement.getId(),
                        announcement.getTitle(),
                        announcement.getContent(),
                        announcement.getCreateTime(),
                        announcement.getUpdateTime()
                ))
                .collect(Collectors.toList());
    }
}
