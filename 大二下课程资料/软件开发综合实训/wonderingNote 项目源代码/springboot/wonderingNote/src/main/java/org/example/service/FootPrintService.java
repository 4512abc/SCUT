package org.example.service;

import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.mapper.PostMapper;
import org.example.model.entity.PostWithBLOBs;
import org.example.model.query.FootPrintQuery.OtherPostLandMarkQuery;
import org.example.model.query.FootPrintQuery.PostLandMarkQuery ;
import org.example.model.query.FootPrintQuery.PostLandMarkQuery;
import org.example.model.utils.Location;
import org.example.model.vo.FootPrintVo.LandMarkListVo;
import org.example.model.vo.FootPrintVo.OtherPostLandMarkVo;
import org.example.model.vo.FootPrintVo.PostLandMarkVo;
import org.example.model.vo.common.PageResultVo;
import org.example.utils.CursorPageUtil;
import org.example.utils.JWTUtils;
import org.springframework.stereotype.Service;

import java.util.*;
import java.util.stream.Collectors;

import static org.example.utils.FileUrlUtil.getFirstFileFromJsonArray;
@Slf4j
@Service
public class FootPrintService {

    private final PostMapper postMapper;

    public FootPrintService(PostMapper postMapper) {
        this.postMapper = postMapper;
    }

    public LandMarkListVo getLandmarkList(Long userId) {


        // 查询用户的所有博文
        Map<String, Object> params = new HashMap<>();
        params.put("userId", userId);
        List<PostWithBLOBs> posts = postMapper.selectLandmarkPostsWithBLOBs(params);
        if(posts==null){
            return null;
        }
        // 筛选不重名的地标
        LandMarkListVo vo = new LandMarkListVo();
        vo.setData(posts.stream()
                .filter(post -> post.getLandmarkName() != null && post.getLocation() != null&& !Objects.equals(post.getLandmarkName(), ""))
                .collect(Collectors.toMap(
                        PostWithBLOBs::getLandmarkName,
                        post -> Location.fromBytes(post.getLocation()),
                        (existing, replacement) -> existing // 如果有重复的地标名，保留第一个
                ))
                .entrySet().stream()
                .map(entry -> {
                    LandMarkListVo.LandMark landMark = new LandMarkListVo.LandMark();
                    landMark.setLandmarkName(entry.getKey());
                    landMark.setLocation(entry.getValue());
                    return landMark;
                })
                .collect(Collectors.toList()));

        return vo;
    }


    public PageResultVo<PostLandMarkVo> getPostsInfo(Long userId, PostLandMarkQuery query) {
        // 1. 执行游标分页查询
        CursorPageUtil.PageResult<PostWithBLOBs> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    params.put("landmarkName", query.getLandmarkName());

                    log.info("[调试] 执行 selectPostsWithBLOBs 查询，参数: userId={}, size={}, lastCursor={}",
                            params.get("userId"),
                            params.get("size"),
                            params.get("lastCursor"));

                    List<PostWithBLOBs> posts = postMapper.selectPostsWithBLOBsbyLandmarkName(params);

                    log.info("[调试] SQL 查询结果数量: {}", posts != null ? posts.size() : 0);
                    if (posts != null && !posts.isEmpty()) {
                        log.info("[调试] 第一条记录 ID: {}", posts.get(0).getId());
                    }

                    return posts;
                },
                post -> String.valueOf(post.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );
        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }
        // 2. 转换结果
        List<PostLandMarkVo> vos = pageResult.getData().stream()
                .map(post -> {
                    PostLandMarkVo vo = new PostLandMarkVo();
                    vo.setId(post.getId());
                    vo.setTitle(post.getTitle());
                    vo.setViewCount(post.getViewCount());
                    vo.setLikeCount(post.getLikeCount());
                    vo.setCommentCount(post.getCommentCount());
                    vo.setLandmarkName(post.getLandmarkName());
                    vo.setIsPublic(post.getIsPublic());
                    // 处理封面图片
                    vo.setCover(getFirstFileFromJsonArray(post.getImages()));
                    // 处理时间格式
                    vo.setCreateTime(post.getCreateTime());
                    // 处理位置信息
                    log.info("[调试] 解析位置信息，原始数据: {}", post.getLocation());
                    log.info("原始二进制数据长度: {}", post.getLocation() != null ? post.getLocation().length : 0);
                    log.info("解析结果: {}", Location.fromBytes(post.getLocation()));
                    vo.setLocation(Location.fromBytes(post.getLocation()));
                    return vo;
                })
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }


    public PageResultVo<OtherPostLandMarkVo> getOtherPostsInfo(Long userId, OtherPostLandMarkQuery query) {

        // 1. 执行游标分页查询
        CursorPageUtil.PageResult<PostWithBLOBs> pageResult = CursorPageUtil.paginate(
                param -> {
                    Map<String, Object> params = new HashMap<>();
                    params.put("userId", userId);
                    params.put("size", param.getSize());
                    params.put("lastCursor", param.getLastCursor());
                    params.put("landmarkName", query.getLandmarkName());

                    log.info("[调试] 执行 selectPostsWithBLOBs 查询，参数: userId={}, size={}, lastCursor={}",
                            params.get("userId"),
                            params.get("size"),
                            params.get("lastCursor"));

                    List<PostWithBLOBs> posts = postMapper.selectOtherPostsWithBLOBsbyLandmarkName(params);

                    log.info("[调试] SQL 查询结果数量: {}", posts != null ? posts.size() : 0);
                    if (posts != null && !posts.isEmpty()) {
                        log.info("[调试] 第一条记录 ID: {}", posts.get(0).getId());
                    }

                    return posts;
                },
                post -> String.valueOf(post.getId()), // 直接使用 ID 作为游标
                query.getSize(),
                query.getLastCursor()
        );

        if(pageResult.getData().isEmpty()){
            return new PageResultVo<>(new ArrayList<>(), pageResult.getNextCursor());
        }
        // 2. 转换结果
        List<OtherPostLandMarkVo> vos = pageResult.getData().stream()
                .map(post -> {
                    OtherPostLandMarkVo vo = new OtherPostLandMarkVo();
                    vo.setId(post.getId());
                    vo.setTitle(post.getTitle());
                    vo.setViewCount(post.getViewCount());
                    vo.setLikeCount(post.getLikeCount());
                    vo.setCommentCount(post.getCommentCount());
                    vo.setLandmarkName(post.getLandmarkName());
                    vo.setIsPublic(post.getIsPublic());
                    // 处理封面图片
                    vo.setCover(getFirstFileFromJsonArray(post.getImages()));
                    // 处理时间格式
                    vo.setCreateTime(post.getCreateTime());
                    vo.setUserId(post.getUserId());
                    // 处理位置信息
                    log.info("[调试] 解析位置信息，原始数据: {}", post.getLocation());
                    log.info("原始二进制数据长度: {}", post.getLocation() != null ? post.getLocation().length : 0);
                    log.info("解析结果: {}", Location.fromBytes(post.getLocation()));
                    vo.setLocation(Location.fromBytes(post.getLocation()));
                    return vo;
                })
                .collect(Collectors.toList());

        return new PageResultVo<>(vos, pageResult.getNextCursor());
    }
    
}
