package org.example.service;

import lombok.extern.slf4j.Slf4j;
import org.example.exception.CustomException;
import org.example.mapper.ChallengeMapper;
import org.example.mapper.LandmarkMapper;
import org.example.mapper.ParticipationMapper;
import org.example.mapper.UserMapper;
import org.example.model.entity.Challenge;
import org.example.model.entity.Landmark;
import org.example.model.entity.Participation;
import org.example.model.query.ChallengesQuery.CreateChallengeQuery;
import org.example.model.query.ChallengesQuery.SubmitChallengeQuery;
import org.example.model.query.ChallengesQuery.SubmitLocationQuery;
import org.example.model.utils.Location;
import org.example.model.vo.ChallengeVo.ChallengeInfoVo;
import org.example.utils.IdJsonUtils;
import org.example.utils.LocationDistance;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.*;
import java.util.stream.Collectors;

import static org.example.common.result.ResultCode.*;
import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;
import static org.example.utils.IdJsonUtils.KeyIdEnum.USER_ID;

@Slf4j
@Service
public class ChallengeService {

    @Autowired
    private ChallengeMapper challengeMapper;

    @Autowired
    private UserMapper userMapper;

    @Autowired
    private ParticipationMapper participationMapper;

    @Autowired
    private LandmarkMapper landmarkMapper;

    public Challenge createChallenge(CreateChallengeQuery query, Long userId) {
        //我们希望创建者后续自己参见挑战，因此paticipantid为空
        if(query.getTitle()==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(query.getDescription()==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(query.getStart_time()==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(query.getEnd_time()==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(query.getLocation()==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(query.getDescription()==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(query.getLandmark_name()==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(query.getNeed_face_verify()==null)
            throw new CustomException(FACE_INFO_ERROR);
        if(query.getNeed_face_verify()!=0&&query.getNeed_face_verify()!=1)
            throw new CustomException(FACE_INFO_ERROR);
        log.info("Title: {}", query.getTitle());
        //设置参数，准备写入challenge表中
        Challenge challenge = new Challenge();
        challenge.setTitle(query.getTitle());
        challenge.setDescription(query.getDescription());
        challenge.setCreatorId(userId);
        challenge.setObjectType(query.getObject_type());
        challenge.setGestureType(query.getGesture_type());
        log.info("Start_time");
        challenge.setStartTime(query.getStart_time());
        challenge.setEndTime(query.getEnd_time());
        challenge.setImages(query.getImages());
        challenge.setRadius(query.getRadius());
        log.info("经度={},纬度={}",query.getLocation().getLng(),query.getLocation().getLat());
        challenge.setLocation(query.getLocation().toBytes());
        challenge.setTeamId(query.getTeam_id());
        challenge.setCreateTime(new Date());
        challenge.setLandmarkName(query.getLandmark_name());
        challenge.setNeedFaceVerify(query.getNeed_face_verify());

        //准备地标擦参数，写入地标表中
//        if(landmarkMapper.selectByLocation(query.getLocation().toBytes())!=null)
//            throw new CustomException(LANDMARK_EXIST_ERROR);
//        Landmark landmark = new Landmark();
//        landmark.setName(query.getLandmark_name());
//        landmark.setLocation(query.getLocation().toBytes());

        challengeMapper.insert(challenge);
        if(challenge.getId()==null)
            throw new CustomException(CHALLENGE_CREATE_ERROR);
        log.info("ChallengeId: {}", challenge.getId());

//        landmarkMapper.insert(landmark);
//        if(landmark.getId()==null)
//            throw new CustomException(CHALLENGE_CREATE_ERROR);

        return challenge;
    }

    public String joinChallenge(Long userId, Long challengeId) {
        Challenge challenge = challengeMapper.selectByPrimaryKey(challengeId);
        if(challenge==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        Participation participationTest =participationMapper.selectByUserIdAndChallengeId(userId,challengeId);
        if(participationTest!=null)
            throw new CustomException(CHALLENGE_EXITJOIN_ERROR);

        //写入participate表，记录用户和挑战的一一对应关系
        participationTest = new Participation();
        participationTest.setCompleteState((byte) 2);
        participationTest.setChallengeId(challengeId);
        participationTest.setUserId(userId);
        participationMapper.insert(participationTest);

        if(challenge==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(challenge.getParticipants()!=null) {
            //查询是否在队列中
            List<Long> exitList = IdJsonUtils.getIdFromJsonArray(challenge.getParticipants()).stream()
                    .map(map -> map.get(USER_ID.getKey()))
                    .collect(Collectors.toList());
            for (Long list : exitList) {
                if(list.equals(userId)){
                    throw new CustomException(CHALLENGE_EXITJOIN_ERROR);
                }
            }
            exitList.add(userId);
            challenge.setParticipants(IdJsonUtils.generateIdsJson(USER_ID,exitList));
            challengeMapper.updateByPrimaryKey(challenge);
            return IdJsonUtils.generateIdsJson(USER_ID,exitList);
        }
        else{
            //无
            List<Long> list = new ArrayList<>();
            list.add(userId);
            challenge.setParticipants(IdJsonUtils.generateIdsJson(USER_ID,list));
            challengeMapper.updateByPrimaryKey(challenge);
            return IdJsonUtils.generateIdsJson(USER_ID,list);
        }
    }

    public boolean submitChallenge(Long userId, Long challengeId, SubmitChallengeQuery query) {
        log.info("submitChallenge"+query);
        Challenge challenge = challengeMapper.selectById(challengeId);
//        log.info("location", query.getLocation().getLat());
//        log.info("location", query.getLocation().getLng());
//        log.info("location", Location.fromBytes(challenge.getLocation()));
//        if(challenge.getLocation()==null)
//            throw new CustomException(CHALLENGE_PARAM_ERROR);

        if(Location.fromBytes(challenge.getLocation())==null)
            throw new CustomException(CHALLENGE_PARAM_ERROR);
        if(challenge==null)
            throw new CustomException(CHALLENGE_NOT_EXIST_ERROR);

        boolean locationEnd = LocationDistance.isWithinRadius(query.getLocation(), Location.fromBytes(challenge.getLocation()), challenge.getRadius());
        Participation participationTest = participationMapper.selectByUserIdAndChallengeId(userId,challengeId);
        if(participationTest==null) {
            if (!locationEnd)
                throw new CustomException(CHALLENGE_LOCATION_ERROR);
            else {
                Participation participantion = new Participation();
                participantion.setChallengeId(challengeId);
                participantion.setUserId(userId);
                participantion.setCompleteTime(new Date());
                participantion.setEvidence(query.getFile_url());
                if (query.isAi_verified()) {
                    participantion.setCompleteState(Byte.valueOf("1"));
                    //修改了insert部分，id自增
                    participationMapper.insert(participantion);
                    if(participantion.getId()==null)
                        throw new CustomException(CHALLENGE_HAVENT_JOIN);
                    return true;
                } else {
                    participantion.setCompleteState(Byte.valueOf("0"));
                    participationMapper.insert(participantion);
                    throw new CustomException(IMG_IDENTIFY_ERROR);
                }
            }
        }
        else{
            if(participationTest.getCompleteState().equals(Byte.valueOf("1")))
                throw new CustomException(CHALLENGE_COMPLETE_ERROR);
            if(!participationTest.getCompleteState().equals(Byte.valueOf("1"))){
                if(query.isAi_verified()){
                    participationTest.setCompleteTime(new Date());
                    participationTest.setCompleteState(Byte.valueOf("1"));
                    participationTest.setEvidence(query.getFile_url());
                    participationMapper.updateByPrimaryKeySelective(participationTest);
                    return true;
                }
                else {
                    participationTest.setEvidence(query.getFile_url());
                    log.info("更新失败记录的失败结果"+participationTest);
                    participationMapper.updateByPrimaryKeySelective(participationTest);
                    return false;
                }
            }
        }
        return true;
    }

    public ChallengeInfoVo getChallengeInfo(Long challengeId) {
        Challenge challenge = challengeMapper.selectById(challengeId);
        if(challenge==null)
            throw new CustomException(CHALLENGE_NOT_EXIST_ERROR);
        ChallengeInfoVo vo = new ChallengeInfoVo();
        vo.setCreateTime(challenge.getCreateTime());
        vo.setCreatorid(challenge.getCreatorId());
        vo.setDescription(challenge.getDescription());
        vo.setEndTime(challenge.getEndTime());
        vo.setGestureType(challenge.getGestureType());
        vo.setImages(getFirstFileFromJsonArray(challenge.getImages()));
        vo.setLandmarkName(challenge.getLandmarkName());
        vo.setObjectType(challenge.getObjectType());
        vo.setRadius(challenge.getRadius());
        vo.setStartTime(challenge.getStartTime());
        vo.setTeamid(challenge.getTeamId());
        vo.setTitle(challenge.getTitle());
        vo.setLocation(Location.fromBytes(challenge.getLocation()));
        vo.setNeedFaceVerify(challenge.getNeedFaceVerify());
        log.info("location", Location.fromBytes(challenge.getLocation()));
        log.info("NeedFaceVerify", challenge.getNeedFaceVerify());
        return vo;
    }

    public boolean deleteChallenge(Long challengeId, Long userId) {
        Challenge challenge = challengeMapper.selectById(challengeId);
        if(challenge==null)
            throw new CustomException(CHALLENGE_NOT_EXIST_ERROR);
        if(challenge.getCreatorId().equals(userId)||userMapper.selectByPrimaryKey(userId).getAccessLevel().equals("admin")||userMapper.selectByPrimaryKey(userId).getAccessLevel().equals("superadmin"))
        {
            participationMapper.deleteByChallengeId(challengeId);
            challengeMapper.deleteByPrimaryKey(challengeId);
        }
        else{
            throw new CustomException(CHALLENGE_NOT_CREATOR_ERROR);
        }
        return true;
    }

    public boolean submitLocation(Long challengeId, SubmitLocationQuery locationData) {
        Challenge challenge = challengeMapper.selectById(challengeId);
        if(challenge==null)
            throw new CustomException(CHALLENGE_NOT_EXIST_ERROR);
        return LocationDistance.isWithinRadius(locationData.getLocation(), Location.fromBytes(challenge.getLocation()), challenge.getRadius());
    }
    public String getChallengeUsers(Long challengeId) {
        return challengeMapper.selectById(challengeId).getParticipants();
    }
}