package org.example.service;

import lombok.extern.slf4j.Slf4j;
import org.example.exception.CustomException;
import org.example.mapper.*;
import org.example.model.entity.*;
import org.example.model.query.TeamQuery.*;
import org.example.model.utils.Location;
import org.example.model.vo.Team.*;
import org.example.model.vo.common.PageResultVo;
import org.example.utils.CursorPageUtil;
import org.example.utils.IdJsonUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.*;
import java.util.stream.Collectors;

import static org.example.common.result.ResultCode.*;
import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;
import static org.example.utils.IdJsonUtils.KeyIdEnum.CHALLENGE_ID;
import static org.example.utils.IdJsonUtils.KeyIdEnum.USER_ID;



@Slf4j
@Service
public class TeamService {
    @Autowired
    private TeamMapper teamMapper;

    @Autowired
    private TeamMemberMapper teamMemberMapper;

    @Autowired
    private ChallengeMapper challengeMapper;

    @Autowired
    private ParticipationMapper participantsMapper;
    @Autowired
    private UserMapper userMapper;

    @Autowired
    private UserProfileMapper userProfileMapper;

    @Autowired
    private ChallengeService challengeService;

    @Autowired
    private NotificationMapper notificationMapper;

    @Autowired
    private NotificationService notificationService;

    public Long createTeam(CreateTeamQuery createTeamQuery,Long id) {
        if(createTeamQuery.getName()==null)
            throw new CustomException(TEAM_NAME_NULL_ERROR);
        if(createTeamQuery.getMax_members()<=0)
            throw new CustomException(TEAM_MAX_SIZE_ERROR);

        Team team = new Team();
        team.setName(createTeamQuery.getName());
        team.setLogo(createTeamQuery.getLogo());
        team.setCreatorId(id);
        team.setMaxMembers(createTeamQuery.getMax_members());
        team.setCreateTime(new java.util.Date());
        //修改了xml的insert，使得自动填补id，同时id自增，但配置中仍需要指定id也被修改
        teamMapper.insert(team);

        //表二
        TeamMember teamMember = new TeamMember();
        teamMember.setTeamId(team.getId());
        teamMember.setUserId(id);
        teamMember.setJoinTime(new java.util.Date());
        teamMember.setRole((byte) 1);
        teamMemberMapper.insert(teamMember);
        return team.getId();
    }

    public Team getTeamById(Long teamId) {
        return teamMapper.selectByPrimaryKey(teamId);
    }

    public boolean joinTeam(Long teamId, Long userId) {
        Team team =getTeamById(teamId);
        if (team != null) {
            TeamMember teamMember1 = teamMemberMapper.selectByTeamIdAndUserId(teamId, userId);
            if (teamMember1 != null) {
                //已经加入过群
                throw new CustomException(TEAM_MEMBER_EXIST_ERROR);
            }
            //表一，加入成员
            if(teamMemberMapper.countByTeamId(teamId)>=team.getMaxMembers())
                throw new CustomException(TEAM_MEMBER_FULL_ERROR);

            team.setMaxMembers(team.getMaxMembers()+1);

            TeamMember teamMember = new TeamMember();
            teamMember.setTeamId(teamId);
            teamMember.setUserId(userId);
            teamMember.setJoinTime(new java.util.Date());
            teamMember.setRole((byte) 0);
            teamMemberMapper.insert(teamMember);

            //表二，加入过往挑战
//            List<Challenge> challenges = challengeMapper.selectByTeamId(teamId);
//            for (Challenge challenge : challenges) {
//                if (challenge.getEndTime().after(new java.util.Date())) {
//                    // 如果挑战没结束
//                    challengeService.joinChallenge(userId, challenge.getId());
//                }
//            }
            return true;
        } else {
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }
    }

    public boolean deleteMember(Long teamId, Long userId, Long deleteUserId) {
        Team team =getTeamById(teamId);
        if (team != null) {
            if (!userId.equals(team.getCreatorId())) {
                //群成员不能删除群成员
                throw new CustomException(TEAM_CREATOR_ERROR);
            }
            if (deleteUserId.equals(team.getCreatorId())) {
                //群主不能删除自己
                throw new CustomException(TEAM_CREATOR_DELETE_ERROR);
            }
            if(userMapper.selectByPrimaryKey(deleteUserId)==null)
                throw new CustomException(USER_NOT_EXIST_ERROR);
            TeamMemberKey teamMemberKey = new TeamMemberKey();
            teamMemberKey.setTeamId(teamId);
            teamMemberKey.setUserId(deleteUserId);
            teamMemberMapper.deleteByPrimaryKey(teamMemberKey);
            return true;
        }else {
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }
    }

    public SendNotificationVo sendNotification(Long teamId, Long userId) {
        TeamMember teamMember = teamMemberMapper.selectByTeamIdAndUserId(teamId, userId);
        if(teamMember==null)
            throw new CustomException(TEAM_MEMBER_NOT_EXIST_ERROR);
        List<Long> unfinishedChallengeIds = new ArrayList<>();
        List<Long> nonChallengeIds = new ArrayList<>();
        //修改了challengeMapper.selectByTeamId(teamId)，使得返回List<Challenge>
        List<Challenge> challenge = challengeMapper.selectByTeamId(teamId);
        log.info("teamId:{},challenge:{}",teamId,challenge);
        if (!challenge.isEmpty()) {
            //检索某个群组下的所有challenge
            for (Challenge challengeItem : challenge) {
                log.info("teamId:{},challengeId:{}",teamId,challengeItem.getId());
                List<Map<String,Long>> list = IdJsonUtils.getIdFromJsonArray(challengeItem.getParticipants());
                //检查是否参加了这个challenge
                boolean flag = true;
                //检索此challeng下的所有userId，查看是否有参加或未参加
                for (Map<String,Long> map : list) {
                    Long userId1 = map.get("user_id");
                    if (userId1.equals(userId)) {
                        flag = false;
                        //修改了participantsMapper，增加了根据用户和群组同时查找的方法，使得记录只有一条
                        Participation participation = participantsMapper.selectByUserIdAndChallengeId(userId,challengeItem.getId());
                        if (participation == null||participation.getCompleteState()==0||participation.getCompleteState()==2) {
                            unfinishedChallengeIds.add(challengeItem.getId());
                        }
                        break;
                    }
                }
                if(flag){
                    //如果没有参加这个challenge
                    nonChallengeIds.add(challengeItem.getId());
                }
            }
            SendNotificationVo sendNotificationVo = new SendNotificationVo();
            sendNotificationVo.setUnfinish_challenge(IdJsonUtils.generateIdsJson(CHALLENGE_ID, unfinishedChallengeIds));
            sendNotificationVo.setNon_challenge(IdJsonUtils.generateIdsJson(CHALLENGE_ID, nonChallengeIds));
            return sendNotificationVo;
        } else {
            throw new CustomException(TEAM_CHALLENGE_ERROR);
        }
    }

    public List<ChallengeInvVo> sendChallengeInvitation(Long teamId, Long userId, Long challengeId) {
        Team team =getTeamById(teamId);
        if (team != null) {
            if (!userId.equals(team.getCreatorId())) {
                //限定群主
                throw new CustomException(TEAM_CREATOR_ERROR);
            }
            Challenge challenge = challengeMapper.selectByPrimaryKey(challengeId);
            if(challenge==null)
                throw new CustomException(CHALLENGE_NOT_EXIST_ERROR);
            //生成只包含userId的list
            //挑战成员
            List<Long> userIds = IdJsonUtils.getIdFromJsonArray(challenge.getParticipants()).stream()
                    .map(map -> map.get("user_id"))
                    .collect(Collectors.toList());
            //群组成员
            List<Long> teamMembers = teamMemberMapper.selectUserIdsByTeamId(teamId);

            //开始对比
            Set<Long> intersection = new HashSet<>(userIds);
            List<ChallengeInvVo> result = new ArrayList<>();

            for (Long userIdItem : teamMembers) {
                if(!intersection.contains(userIdItem)){
                    ChallengeInvVo challengeInvVo = new ChallengeInvVo();
                    challengeInvVo.setUser_id(userIdItem);
                    User user = userMapper.selectByPrimaryKey(userIdItem);
                    challengeInvVo.setUser_account(user.getAccount());
                    challengeInvVo.setUser_avatar(user.getAvatar());
                    result.add(challengeInvVo);
                    log.info("userIdItem:"+userIdItem);
                    notificationService.setChallengeNotification(challengeId,userIdItem,userId,"有未参加的挑战："+challenge.getTitle());
                }
            }
            //完成合并
            return result;
        }else {
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }
    }

    public List<PostInvVo> sendPostInvitation(Long teamId, Long userId, PostInvQuery postInvitationQuery) {
        Team team =getTeamById(teamId);
        Long challengeId = postInvitationQuery.getChallenge_id();
        if (team != null) {
            if (!userId.equals(team.getCreatorId())) {
                //限定群主
                throw new CustomException(TEAM_CREATOR_ERROR);
            }
            Challenge challenge = challengeMapper.selectByPrimaryKey(challengeId);
            if(challenge==null)
                throw new CustomException(CHALLENGE_NOT_EXIST_ERROR);
            //生成只包含userId的list
            //挑战成员
            List<Long> userIds = IdJsonUtils.getIdFromJsonArray(challenge.getParticipants()).stream()
                    .map(map -> map.get("user_id"))
                    .collect(Collectors.toList());

            List<PostInvVo> result = new ArrayList<>();
            for(Long userIdItem:userIds) {
                Participation participation = participantsMapper.selectByUserIdAndChallengeId(userIdItem, challengeId);
                if(participation==null||participation.getCompleteState()==2){
                    PostInvVo postInvVo = new PostInvVo();
                    postInvVo.setUser_id(userIdItem);
                    User user = userMapper.selectByPrimaryKey(userIdItem);
                    postInvVo.setUser_account(user.getAccount());
                    postInvVo.setUser_avatar(user.getAvatar());
                    result.add(postInvVo);
                    log.info("userIdItem:"+userIdItem);
                    notificationService.setChallengeNotification(challengeId,userIdItem,userId,"有未提交的挑战："+challenge.getTitle());
                }

            }
            //完成合并
            return result;
        }else {
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }
    }

    public PageResultVo<UserCheckVo> getTeamUserCheck(Long teamId, UserCheckQuery userCheckQuery, Long userId, Integer size, String lastCursor) {
        Team team = getTeamById(teamId);
        if (team.getCreatorId() != userId)
            throw new CustomException(TEAM_CREATOR_ERROR);

        Challenge challenge = challengeMapper.selectByPrimaryKey(userCheckQuery.getChallenge_id());
        if (challenge.getCreatorId() != userId)
            throw new CustomException(CHALLENGE_NOT_CREATOR_ERROR);

        // 生成只包含userId的list
        List<Long> allUserIds = IdJsonUtils.getIdFromJsonArray(challenge.getParticipants()).stream()
                .map(map -> map.get("user_id"))
                .collect(Collectors.toList());

        // 分页处理
        int actualSize = size != null ? size : 10; // 默认每页10条

        // 计算起始位置
        int start = 0;
        if (lastCursor != null && !lastCursor.isEmpty()) {
            try {
                int cursorIndex = Integer.parseInt(lastCursor);
                start = Math.min(cursorIndex, allUserIds.size());
            } catch (NumberFormatException e) {
                // 如果游标不是有效的数字索引，则从头开始
                log.warn("Invalid lastCursor value: {}", lastCursor);
            }
        }

        // 计算结束位置（多取一条用于判断是否有下一页）
        int end = Math.min(start + actualSize + 1, allUserIds.size());

        // 获取当前页的数据（多取了一条用于判断是否有下一页）
        List<Long> userIdItems = allUserIds.subList(start, end);

        // 判断是否有更多数据
        boolean hasMore = userIdItems.size() > actualSize;

        // 截断结果（移除多余的最后一条）
        List<Long> truncatedUserIds = userIdItems.stream()
                .limit(actualSize)
                .collect(Collectors.toList());

        // 处理用户检查信息
        List<UserCheckVo> result = new ArrayList<>();

        for (Long userIdItem : truncatedUserIds) {
            Participation participation = participantsMapper.selectByUserIdAndChallengeId(userIdItem, userCheckQuery.getChallenge_id());
            if (participation == null) {
                participation = new Participation();
                participation.setCompleteState((byte) 2);
                participation.setChallengeId(userCheckQuery.getChallenge_id());
                participation.setUserId(userIdItem);
                participantsMapper.insert(participation);
            }

            UserCheckVo userCheckVo = new UserCheckVo();
            userCheckVo.setUser_id(userIdItem);
            User user = userMapper.selectByPrimaryKey(userIdItem);
            userCheckVo.setUser_account(user.getAccount());
            userCheckVo.setUser_avatar(user.getAvatar());
            userCheckVo.setParticipant_record_id(participation.getId());
            userCheckVo.setComplete_state(participation.getCompleteState().toString());
            userCheckVo.setEvidence(participation.getEvidence());
            userCheckVo.setComplete_time(participation.getCompleteTime());
            result.add(userCheckVo);

            if (participation.getCompleteState() == 2) {
                notificationService.setChallengeNotification(userCheckQuery.getChallenge_id(), userIdItem, userId, "有未提交的挑战：" + challenge.getTitle());
            } else if (participation.getCompleteState() == 0) {
                notificationService.setChallengeNotification(userCheckQuery.getChallenge_id(), userIdItem, userId, "有未成功的挑战：" + challenge.getTitle());
            }
        }

        // 计算下一个游标
        String nextCursor = null;
        if (hasMore && !truncatedUserIds.isEmpty()) {
            // 使用最后一个元素的索引作为下一个游标
            int nextIndex = start + actualSize;
            if (nextIndex < allUserIds.size()) {
                nextCursor = String.valueOf(nextIndex);
            }
        }

        return new PageResultVo<>(result, nextCursor);
    }


    public GetCheckInfoVo getCheckInfo(Long checkId) {
        Participation participation = participantsMapper.selectByPrimaryKey(checkId);
        if(participation==null)
            throw new CustomException(PARTICIPANT_NOT_EXIST);
        GetCheckInfoVo getCheckInfoVo = new GetCheckInfoVo();
        BeanUtils.copyProperties(participation, getCheckInfoVo);
        return getCheckInfoVo;
    }

    public void modifyCheckInfo(Long checkId, CheckModifyQuery checkModifyQuery) {
        Byte completeState = Byte.valueOf(checkModifyQuery.getComplete_state());
        log.info("completeState:"+completeState);
        if(completeState==0||completeState==1||completeState==2){
            Participation participation = participantsMapper.selectByPrimaryKey(checkId);
            if(participation==null)
                throw new CustomException(PARTICIPANT_NOT_EXIST);
            participation.setCompleteState(Byte.valueOf(checkModifyQuery.getComplete_state()));
            participantsMapper.updateByPrimaryKeySelective(participation);
        }
        else {
            throw new CustomException(INVAILD_STATE);
        }

    }

    public PageResultVo<TeamMemberVo> getTeamMembers(Long teamId, Integer size, String lastCursor) {
        // 使用游标分页查询团队成员
        CursorPageUtil.PageResult<TeamMember> pageResult = CursorPageUtil.paginate(
                params -> {
                    Map<String, Object> paramsMap = new HashMap<>();
                    paramsMap.put("teamId", teamId);
                    paramsMap.put("size", params.getSize());
                    paramsMap.put("lastCursor", params.getLastCursor());
                    return teamMemberMapper.selectByTeamId(paramsMap);
                },
                TeamMember::getUserId, // 使用 userId 作为游标
                size,
                lastCursor
        );

        if(teamMapper.selectByPrimaryKey(teamId)==null){
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }

        // 获取用户信息
        List<TeamMemberVo> members = pageResult.getData().stream().map(member -> {
            User user = userMapper.selectByPrimaryKey(member.getUserId());
            UserProfile userProfile = userProfileMapper.selectByPrimaryKey(member.getUserId());
            TeamMemberVo memberVo = new TeamMemberVo();
            memberVo.setId(user.getId());
            memberVo.setUserAccount(user.getAccount());
            memberVo.setUserAvatar(user.getAvatar());
            memberVo.setUpdateTime(user.getUpdateTime());
            memberVo.setJoinTime(member.getJoinTime());

            return memberVo;
        }).collect(Collectors.toList());

        return new PageResultVo<>(members, pageResult.getNextCursor());
    }

    public boolean inviteMember(Long teamId, Long userId, InviteMemberQuery teamMemberQuery) {
        Team team =getTeamById(teamId);
        if (team != null) {
            if (!userId.equals(team.getCreatorId())) {
                //限定群主
                throw new CustomException(TEAM_CREATOR_ERROR);
            }
            TeamMember teamMember = teamMemberMapper.selectByTeamIdAndUserId(teamId, teamMemberQuery.getUserId());
            if (teamMember != null) {
                //已经加入过群
                throw new CustomException(TEAM_MEMBER_EXIST_ERROR);
            }
            if (teamMemberMapper.countByTeamId(teamId) >= team.getMaxMembers()) {
                // 群成员数量已达上限
                throw new CustomException(TEAM_MEMBER_FULL_ERROR);
            }

            team.setMaxMembers(team.getMaxMembers()+1);

            teamMember = new TeamMember();
            teamMember.setTeamId(teamId);
            teamMember.setUserId(teamMemberQuery.getUserId());
            teamMember.setJoinTime(new java.util.Date());
            teamMember.setRole((byte) 0);
            teamMemberMapper.insert(teamMember);

            //表二，加入过往挑战
//            List<Challenge> challenges = challengeMapper.selectByTeamId(teamId);
//            for (Challenge challenge : challenges) {
//                if (challenge.getEndTime().after(new java.util.Date())) {
//                    // 如果挑战没结束
//                    challengeService.joinChallenge(userId, challenge.getId());
//                }
//            }
            return true;
        }else{
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }
    }

    public TeamDetailVo getTeamInfo(Long teamId) {
        Team team = teamMapper.selectByPrimaryKey(teamId);
        if(teamMapper.selectByPrimaryKey(teamId)==null){
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }
        if (team == null) {
            throw new CustomException(TEAM_NOT_EXIST_ERROR);
        }

        TeamDetailVo vo = new TeamDetailVo();
        vo.setMembersCount(teamMemberMapper.countByTeamId(teamId));
        vo.setName(team.getName());
        vo.setLogo(team.getLogo());
        vo.setCreatorId(team.getCreatorId());
        vo.setMaxMembers(team.getMaxMembers());
        vo.setCreateTime(team.getCreateTime());

        return vo;
    }

    public PageResultVo<GetChallengeInfoVo> getChallengeInfo(Long teamId, Integer size, String lastCursor) {
        // 使用 CursorPageUtil 进行游标分页
        CursorPageUtil.PageResult<Challenge> pageResult = CursorPageUtil.paginate(
                params -> {
                    Map<String, Object> paramsMap = new HashMap<>();
                    paramsMap.put("teamId", teamId);
                    paramsMap.put("size", params.getSize());
                    paramsMap.put("lastCursor", params.getLastCursor());
                    return challengeMapper.selectByTeamId_1(paramsMap); // 确保该方法支持分页参数
                },
                Challenge::getId, // 使用 id 作为游标
                size,
                lastCursor
        );

        // 转换为 VO 对象
        List<GetChallengeInfoVo> result = pageResult.getData().stream()
                .map(challenge -> {
                    GetChallengeInfoVo vo = new GetChallengeInfoVo();
                    vo.setId(challenge.getId());
                    vo.setTitle(challenge.getTitle());
                    User user = userMapper.selectByPrimaryKey(challenge.getCreatorId());
                    vo.setCreatorAccount(user != null ? user.getAccount() : null);
                    vo.setObjectType(challenge.getObjectType());
                    vo.setGestureType(challenge.getGestureType());
                    vo.setLandmarkName(challenge.getLandmarkName());
                    vo.setParticipants(challenge.getParticipants());
                    vo.setEndTime(challenge.getEndTime());
                    vo.setCover(getFirstFileFromJsonArray(challenge.getImages()));
                    vo.setLocation(Location.fromBytes(challenge.getLocation()));
                    vo.setCreatedId(challenge.getCreatorId());
                    vo.setCreatedAvatar(user != null ? user.getAvatar() : null);
                    return vo;
                })
                .collect(Collectors.toList());

        return new PageResultVo<>(result, pageResult.getNextCursor());
    }



}

