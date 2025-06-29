package org.example.service;

import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import lombok.extern.slf4j.Slf4j;
import org.example.mapper.*;
import org.example.model.entity.*;
import org.example.model.query.SearchInfoQuery.*;
import org.example.model.vo.SearchInfoVo.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Slf4j
@Service
public class SearchInfoService {
    @Autowired
    private UserMapper userMapper;

    @Autowired
    private ChallengeMapper challengeMapper;

    @Autowired
    private PostMapper postMapper;

    @Autowired
    private AnnouncementMapper announcementMapper;

    @Autowired
    private TeamMapper teamMapper;

    @Autowired
    private ParticipationMapper participationMapper;

    @Autowired
    private CommentMapper commentMapper;

    @Autowired
    private LikeMapper likeMapper;

    @Autowired
    private TeamMemberMapper teamMemberMapper;

    public PageInfo<SearchUserVo> searchForUsers(Integer pageNum, Integer pageSize, SearchUserQuery searchUserQUery){
        log.info("Page number: {}, Page size: {}", pageNum, pageSize);
        PageHelper.startPage(pageNum, pageSize); // 添加count查询
        List<User> userList = userMapper.selectByConditions(searchUserQUery.getAccessLevel(),
                searchUserQUery.getUserAccount(),
                searchUserQUery.getStatus(),
                searchUserQUery.getEmail(),
                searchUserQUery.getStartTime(),
                searchUserQUery.getEndTime());

        PageInfo<User> pageInfo = new PageInfo<>(userList);
        List<SearchUserVo> searchUserVoList = pageInfo.getList().stream()
                .map(user -> new SearchUserVo(user))
                .collect(Collectors.toList());
        PageInfo<SearchUserVo> result = new PageInfo<>(searchUserVoList);
        copyPageInfoProperties(pageInfo, result);
        return result;
    }

    public PageInfo<SearchChallengeVo> searchForChallenges(Integer pageNum, Integer pageSize, SearchChallengeQuery searchChallengeQuery){
        PageHelper.startPage(pageNum, pageSize);
        List<Challenge> challenges = challengeMapper.selectByTitleAndCreateTimeRange(searchChallengeQuery.getTitle(),
                searchChallengeQuery.getStartTime(),
                searchChallengeQuery.getEndTime());

        // 使用 PageInfo 包装原始的 challenges 以保留分页信息
        PageInfo<Challenge> pageInfo = new PageInfo<>(challenges);

        // 转换为 SearchChallengeVo 列表
        List<SearchChallengeVo> searchChallengeVoList = pageInfo.getList().stream()
                .map(challenge -> {
                    long count = participationMapper.countByChallengeId(challenge.getId());
                    return new SearchChallengeVo(challenge, count);
                })
                .collect(Collectors.toList());


        // 创建新的 PageInfo 对象并复制分页信息
        PageInfo<SearchChallengeVo> result = new PageInfo<>(searchChallengeVoList);
        copyPageInfoProperties(pageInfo, result);
        return result;
    }

    public PageInfo<SearchPostVo> searchForPosts(Integer pageNum, Integer pageSize, SearchPostQuery searchPostQuery){
        PageHelper.startPage(pageNum, pageSize);
        List<PostWithBLOBs> list = postMapper.selectByTitleAndCreateTimeRange(searchPostQuery.getTitle(),
                searchPostQuery.getStartTime(),
                searchPostQuery.getEndTime());

        // 使用 PageInfo 包装原始的 list 以保留分页信息
        PageInfo<PostWithBLOBs> pageInfo = new PageInfo<>(list);

        // 转换为 SearchPostVo 列表
        List<SearchPostVo> searchPostVoList = pageInfo.getList().stream()
                .map(post -> {
                    Integer commentCount = commentMapper.selectCommentCountByPostId(post.getId());
                    Integer likeCount = likeMapper.countByTargetIdAndType(post.getId(), "BLOG");
                    String publishAccount = userMapper.selectByPrimaryKey(post.getUserId()).getAccount();
                    return new SearchPostVo(post, commentCount, likeCount, publishAccount);
                })
                .collect(Collectors.toList());

        // 创建新的 PageInfo 对象并复制分页信息
        PageInfo<SearchPostVo> result = new PageInfo<>(searchPostVoList);
        copyPageInfoProperties(pageInfo, result);
        return result;
    }

    public PageInfo<SearchAnnouncementVo> searchForAnnouncements(Integer pageNum, Integer pageSize, SearchAnnouncementQuery searchAnnouncementQuery){
        PageHelper.startPage(pageNum, pageSize);
        List<Announcement> announcementList = announcementMapper.selectAnnouncementsByConditions(searchAnnouncementQuery.getTitle(),
                searchAnnouncementQuery.getType(),
                searchAnnouncementQuery.getStartTime(),
                searchAnnouncementQuery.getEndTime());

        // 使用 PageInfo 包装原始的 announcementList 以保留分页信息
        PageInfo<Announcement> pageInfo = new PageInfo<>(announcementList);

        // 转换为 SearchAnnouncementVo 列表
        List<SearchAnnouncementVo> searchAnnouncementVoList = pageInfo.getList().stream()
                .map(announcement -> {
                    String publishedAccount = userMapper.selectByPrimaryKey(announcement.getPublisherId()).getAccount();
                    return new SearchAnnouncementVo(announcement, publishedAccount);
                })
                .collect(Collectors.toList());

        // 创建新的 PageInfo 对象并复制分页信息
        PageInfo<SearchAnnouncementVo> result = new PageInfo<>(searchAnnouncementVoList);
        copyPageInfoProperties(pageInfo, result);

        return result;
    }

    public PageInfo<SearchTeamVo> searchForTeams(Integer pageNum, Integer pageSize, SearchTeamQuery searchTeamQuery){
        PageHelper.startPage(pageNum, pageSize);
        List<Team> teams = teamMapper.selectByNameAndCreateTimeRange(searchTeamQuery.getName(),
                searchTeamQuery.getStartTime(),
                searchTeamQuery.getEndTime());

        // 使用 PageInfo 包装原始的 teams 以保留分页信息
        PageInfo<Team> pageInfo = new PageInfo<>(teams);

        // 转换为 SearchTeamVo 列表
        List<SearchTeamVo> searchTeamVoList = pageInfo.getList().stream()
                .map(team -> {
                    String createdUseraccount = userMapper.selectByPrimaryKey(team.getCreatorId()).getAccount();
                    Integer userNumber = teamMemberMapper.countByTeamId(team.getId());
                    return new SearchTeamVo(team, createdUseraccount, userNumber);
                })
                .collect(Collectors.toList());

        // 创建新的 PageInfo 对象并复制分页信息
        PageInfo<SearchTeamVo> result = new PageInfo<>(searchTeamVoList);
        copyPageInfoProperties(pageInfo, result);

        return result;
    }

    public PageInfo<TeamChallengeListVo> getTeamInfo(Integer pageNum, Integer pageSize,Long teamId){
        PageHelper.startPage(pageNum, pageSize);
        List<Challenge> challenges = challengeMapper.selectByTeamId(teamId);

        // 使用 PageInfo 包装原始的 challenges 以保留分页信息
        PageInfo<Challenge> pageInfo = new PageInfo<>(challenges);

        // 转换为 TeamChallengeListVo 列表
        List<TeamChallengeListVo> teamChallengeListVoList = pageInfo.getList().stream()
                .map(challenge -> {
                    String creatorAccount = userMapper.selectAccountById(challenge.getCreatorId());
                    return new TeamChallengeListVo(challenge, creatorAccount);
                })
                .collect(Collectors.toList());

        // 创建新的 PageInfo 对象并复制分页信息
        PageInfo<TeamChallengeListVo> result = new PageInfo<>(teamChallengeListVoList);
        copyPageInfoProperties(pageInfo, result);

        return result;
    }
    private void copyPageInfoProperties(PageInfo source, PageInfo destination) {
        destination.setTotal(source.getTotal());
        destination.setPageNum(source.getPageNum());
        destination.setPageSize(source.getPageSize());
        destination.setSize(source.getSize());
        destination.setStartRow(source.getStartRow());
        destination.setEndRow(source.getEndRow());
        destination.setPages(source.getPages());
        destination.setPrePage(source.getPrePage());
        destination.setNextPage(source.getNextPage());
        destination.setIsFirstPage(source.isIsFirstPage());
        destination.setIsLastPage(source.isIsLastPage());
        destination.setHasPreviousPage(source.isHasPreviousPage());
        destination.setHasNextPage(source.isHasNextPage());
        destination.setNavigatePages(source.getNavigatePages());
        destination.setNavigatepageNums(source.getNavigatepageNums());
        destination.setNavigateFirstPage(source.getNavigateFirstPage());
        destination.setNavigateLastPage(source.getNavigateLastPage());
    }
}
