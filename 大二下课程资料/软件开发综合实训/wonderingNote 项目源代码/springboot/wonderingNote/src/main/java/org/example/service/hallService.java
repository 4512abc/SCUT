package org.example.service;

import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.exception.CustomException;
import org.example.mapper.ChallengeMapper;
import org.example.mapper.ParticipationMapper;
import org.example.mapper.PostMapper;
import org.example.mapper.UserMapper;
import org.example.model.entity.Challenge;
import org.example.model.entity.PostWithBLOBs;
import org.example.model.entity.User;
import org.example.model.query.hallQuery.ChallengeQuery;
import org.example.model.query.hallQuery.ChallengeSearchQuery;
import org.example.model.query.hallQuery.PostQuery;
import org.example.model.query.hallQuery.PostSearchQuery;
import org.example.model.query.hallQuery.UserSearchQuery;
import org.example.model.utils.Location;
import org.example.model.vo.HallVo.ChallengeSearchVo;
import org.example.model.vo.HallVo.ChallengeVo;
import org.example.model.vo.HallVo.PostSearchVo;
import org.example.model.vo.HallVo.PostVo;
import org.example.model.vo.HallVo.UserSearchVo;
import org.example.model.vo.common.PageResultVo;
import org.example.utils.CursorPageUtil;
import org.example.utils.EmailUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.*;
import java.util.stream.Collectors;

import static org.example.common.result.ResultCode.EAMIL_FORM_ERROR;
import static org.example.common.result.ResultCode.USER_NOT_EXIST_ERROR;
import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;
@Slf4j
@Service
public class hallService {

    private final PostMapper postMapper;
    private final UserMapper userMapper;
    private final ChallengeMapper challengeMapper;
    private final ParticipationMapper participationMapper;

    @Autowired
    public hallService(PostMapper postMapper, UserMapper userMapper, ChallengeMapper challengeMapper, ParticipationMapper participationMapper) {
        this.postMapper = postMapper;
        this.userMapper = userMapper;
        this.challengeMapper = challengeMapper;
        this.participationMapper = participationMapper;
    }

    public PostVo getPosts(PostQuery query) {
        CursorPageUtil.PageResult<PostWithBLOBs> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return postMapper.selectPostsWithBLOBs_1(params);
                },
                post -> String.valueOf(post.getId()),
                query.getSize(),
                query.getLastCursor()
        );
        if(pageResult.getData().isEmpty()){
            return new PostVo();
        }
        return convertToVo(pageResult);
    }

    private PostVo convertToVo(CursorPageUtil.PageResult<PostWithBLOBs> pageResult) {
        PostVo vo = new PostVo();
        vo.setData(pageResult.getData().stream().map(this::convertToPostVo).collect(Collectors.toList()));
        vo.setNextCursor(pageResult.getNextCursor());
        return vo;
    }

    private PostVo.Post convertToPostVo(PostWithBLOBs post) {
        PostVo.Post postVo = new PostVo.Post();
        postVo.setId(post.getId());
        postVo.setCover(getFirstFileFromJsonArray(post.getImages()));
        postVo.setTitle(post.getTitle());
        postVo.setViewCount(post.getViewCount());
        postVo.setLikeCount(post.getLikeCount());
        postVo.setCommentCount(post.getCommentCount());
        postVo.setCreateTime(post.getCreateTime());
        postVo.setLocation(Location.fromBytes(post.getLocation()));
        postVo.setLandmarkName(post.getLandmarkName());
        postVo.setUserId(post.getUserId());
        User user=userMapper.selectByPrimaryKey(post.getUserId());
        postVo.setUserAccount(user.getAccount());
        postVo.setUserAvatar(user.getAvatar());
        postVo.setIsPublic(post.getIsPublic());
        if(post.getVideos()!=null||!post.getVideos().equals("")){
            postVo.setIs_video(true);
        }
        return postVo;
    }

    public PageResultVo<PostSearchVo> searchPostsByTitleAndTime(@RequestParam(required = false) Integer size, @RequestParam(required = false) String lastCursor, @RequestParam(required = false) String sort, @RequestParam(required = false) String title, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime) {
        // 调用游标分页工具
        log.info("Searching posts by title and time range...={},={}",startTime,endTime);
        CursorPageUtil.PageResult<PostWithBLOBs> pageResult = CursorPageUtil.paginate(
            param -> {
                Map<String, Object> params = new HashMap<>();
                params.put("title", title);
                params.put("startTime", startTime);
                params.put("endTime", endTime);
                params.put("size", param.getSize());
                params.put("lastCursor", param.getLastCursor());
                return postMapper.selectByTitleAndCreateTimeRange_1(params);
            },
            post -> String.valueOf(post.getId()),
            size != null ? size : 10,
            lastCursor
        );
        if (pageResult.getData().isEmpty()){
            return new PageResultVo<>(Collections.emptyList(), null);
        }

        List<PostSearchVo> vos = pageResult.getData().stream()
            .map(this::convertToPostSearchVo)
            .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private PostSearchVo convertToPostSearchVo(PostWithBLOBs post) {
        PostSearchVo vo = new PostSearchVo();
        vo.setId(post.getId());
        vo.setCover(getFirstFileFromJsonArray(post.getImages()));
        vo.setTitle(post.getTitle());
        vo.setViewCount(post.getViewCount());
        vo.setLikeCount(post.getLikeCount());
        vo.setCommentCount(post.getCommentCount());
        vo.setCreateTime(post.getCreateTime());
        vo.setLandmarkName(post.getLandmarkName());
        vo.setUserId(post.getUserId());
        User user=userMapper.selectByPrimaryKey(post.getUserId());
        vo.setUserAccount(user.getAccount());
        vo.setUserAvatar(user.getAvatar());
        vo.setIsPublic(post.getIsPublic());
        if(post.getVideos()!=null||!post.getVideos().equals("")){
            vo.setIs_video(true);
        }
        return vo;
    }

    public ChallengeVo getChallenges(ChallengeQuery query) {
        CursorPageUtil.PageResult<Challenge> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return challengeMapper.selectUnfinishedChallenges(params);
                },
                challenge -> String.valueOf(challenge.getId()),
                query.getSize(),
                query.getLastCursor()
        );

        if (pageResult.getData().isEmpty()) {
            return new ChallengeVo();
        }

        // 使用方法引用更简洁
        List<ChallengeVo.Challenge> vos = pageResult.getData().stream()
                .map(this::convertToVo)
                .collect(Collectors.toList());

        ChallengeVo vo = new ChallengeVo();
        vo.setData(vos);
        vo.setNextCursor(pageResult.getNextCursor());
        return vo;
    }

    private ChallengeVo.Challenge convertToVo(Challenge challenge) {
        ChallengeVo.Challenge vo = new ChallengeVo.Challenge();
        User user=userMapper.selectByPrimaryKey(challenge.getCreatorId());
        vo.setId(challenge.getId());
        vo.setTitle(challenge.getTitle());
        vo.setCreatorAccount(user.getAccount());
        vo.setObjectType(challenge.getObjectType());
        vo.setGestureType(challenge.getGestureType());
        vo.setLandmarkName(challenge.getLandmarkName());
        vo.setParticipants(challenge.getParticipants());
        vo.setEndTime(challenge.getEndTime());
        vo.setCover(getFirstFileFromJsonArray(challenge.getImages()));
        vo.setLocation(Location.fromBytes(challenge.getLocation()));
        vo.setCreatedId(challenge.getCreatorId());
        vo.setCreatedAvatar(user.getAvatar());
        return vo;
    }

    public PageResultVo<ChallengeSearchVo> searchChallengesByTitleAndTime(@RequestParam(required = false) Integer size, @RequestParam(required = false) String lastCursor, @RequestParam(required = false) String sort, @RequestParam(required = false) String title, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime) {
        log.info("Searching challenges by title and time range...={},={}",startTime,endTime);
        CursorPageUtil.PageResult<Challenge> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("title", title);
                    params.put("startTime", startTime);
                    params.put("endTime", endTime);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    return challengeMapper.selectByTitleAndCreateTimeRange_1(params);
                },
                challenge -> String.valueOf(challenge.getId()),
                size != null ? size : 10,
                lastCursor
        );
        if (pageResult.getData().isEmpty()){
            return new PageResultVo<>(Collections.emptyList(), null);
        }
        List<ChallengeSearchVo> vos = pageResult.getData().stream()
                .map(this::convertToChallengeSearchVo)
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }
    private ChallengeSearchVo convertToChallengeSearchVo(Challenge challenge) {
        ChallengeSearchVo vo = new ChallengeSearchVo();
        vo.setId(challenge.getId());
        vo.setCover(getFirstFileFromJsonArray(challenge.getImages()));
        vo.setCreateId(challenge.getCreatorId());
        vo.setCreatedTime(challenge.getCreateTime());
        vo.setCount(participationMapper.countByChallengeId(challenge.getId()));
        vo.setTitle(challenge.getTitle());
        return vo;
    }
    public UserSearchVo getUser(UserSearchQuery query) {
        if(EmailUtil.isValidEmail(query.getEmail())){
            User user=userMapper.selectByEmail(query.getEmail());
            if(user!=null){
                UserSearchVo vo=new UserSearchVo(user);
                return vo;
            }else{
                throw new CustomException(USER_NOT_EXIST_ERROR);
            }
        }else{
            throw new CustomException(EAMIL_FORM_ERROR);
        }
    }

    public PageResultVo<PostSearchVo> searchMyPostsByTitleAndTime(Long userId,@RequestParam(required = false) Integer size, @RequestParam(required = false) String lastCursor, @RequestParam(required = false) String sort, @RequestParam(required = false) String title, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime) {
        // 调用游标分页工具
        log.info("Searching posts by title and time range...={},={}",startTime,endTime);
        CursorPageUtil.PageResult<PostWithBLOBs> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("title", title);
                    params.put("startTime", startTime);
                    params.put("endTime", endTime);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    params.put("userId", userId);
                    return postMapper.selectByTitleAndCreateTimeRange_2(params);
                },
                post -> String.valueOf(post.getId()),
                size != null ? size : 10,
                lastCursor
        );
        if (pageResult.getData().isEmpty()){
            return new PageResultVo<>(Collections.emptyList(), null);
        }

        List<PostSearchVo> vos = pageResult.getData().stream()
                .map(this::convertToMyPostSearchVo)
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }

    private PostSearchVo convertToMyPostSearchVo(PostWithBLOBs post) {
        PostSearchVo vo = new PostSearchVo();
        vo.setId(post.getId());
        vo.setCover(getFirstFileFromJsonArray(post.getImages()));
        vo.setTitle(post.getTitle());
        vo.setViewCount(post.getViewCount());
        vo.setLikeCount(post.getLikeCount());
        vo.setCommentCount(post.getCommentCount());
        vo.setCreateTime(post.getCreateTime());
        vo.setLandmarkName(post.getLandmarkName());
        vo.setUserId(post.getUserId());
        User user=userMapper.selectByPrimaryKey(post.getUserId());
        vo.setUserAccount(user.getAccount());
        vo.setUserAvatar(user.getAvatar());
        vo.setIsPublic(post.getIsPublic());
        return vo;
    }

    public PageResultVo<ChallengeSearchVo> searchmyChallengesByTitleAndTime(Long userId,@RequestParam(required = false) Integer size, @RequestParam(required = false) String lastCursor, @RequestParam(required = false) String sort, @RequestParam(required = false) String title, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date startTime, @RequestParam(required = false)@DateTimeFormat(pattern="yyyy-MM-dd HH:mm:ss")  Date endTime) {
        log.info("Searching challenges by title and time range...={},={}",startTime,endTime);
        CursorPageUtil.PageResult<Challenge> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("title", title);
                    params.put("startTime", startTime);
                    params.put("endTime", endTime);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    params.put("userId", userId);
                    return challengeMapper.selectByTitleAndCreateTimeRange_2(params);
                },
                challenge -> String.valueOf(challenge.getId()),
                size != null ? size : 10,
                lastCursor
        );
        if (pageResult.getData().isEmpty()){
            return new PageResultVo<>(Collections.emptyList(), null);
        }
        List<ChallengeSearchVo> vos = pageResult.getData().stream()
                .map(this::convertToMyChallengeSearchVo)
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }
    private ChallengeSearchVo convertToMyChallengeSearchVo(Challenge challenge) {
        ChallengeSearchVo vo = new ChallengeSearchVo();
        vo.setId(challenge.getId());
        vo.setCover(getFirstFileFromJsonArray(challenge.getImages()));
        vo.setCreateId(challenge.getCreatorId());
        vo.setCreatedTime(challenge.getCreateTime());
        vo.setCount(participationMapper.countByChallengeId(challenge.getId()));
        vo.setTitle(challenge.getTitle());
        return vo;
    }

}

