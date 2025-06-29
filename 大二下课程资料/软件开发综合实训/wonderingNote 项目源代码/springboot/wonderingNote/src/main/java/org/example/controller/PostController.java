package org.example.controller;

import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.model.dto.FileInfoDto.FileInfoDto;
import org.example.model.query.PostQuery.PostCreateQuery;
import org.example.model.query.PostQuery.PostInfoQuery;
import org.example.model.query.PostQuery.PostDeleteQuery;
import org.example.model.vo.PostVo.PostCreateVo;
import org.example.model.vo.PostVo.PostInfoVo;
import org.example.model.vo.PostVo.PostDeleteVo;
import org.example.service.PostService;
import org.example.utils.JWTUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.Map;

import static org.example.common.result.ResultCode.FILE_CREATE_ERROR;

@RestController
@RequestMapping("/api/posts")
@Slf4j
public class PostController {

    @Autowired
    private PostService postService;


    @GetMapping("/{post_id}")
    public Result<PostInfoVo> getPostDetail(@PathVariable("post_id") Long postId) {
        PostInfoQuery query = new PostInfoQuery();
        query.setPostId(postId);

        PostInfoVo postInfo = postService.getPostDetail(query);

        return Result.success(postInfo) ;
    }

    @DeleteMapping("/{post_id}/delete")
    public Result<PostDeleteVo> deletePost(@PathVariable("post_id") Long postId, @RequestHeader("Authorization") String token) {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long currentUserId = (long) claims.get("id");

        PostDeleteQuery query = new PostDeleteQuery();
        query.setPostId(postId);

        PostDeleteVo vo = postService.deletePost(query, currentUserId);
        return Result.success(vo);
    }

    @PostMapping("/create")
    public Result<PostCreateVo> createPost(@RequestBody PostCreateQuery query,@RequestHeader("Authorization") String token) throws Exception {
        Map<String, Object> claims = JWTUtils.getClaims(token);
        Long currentUserId = (long) claims.get("id");
        log.info(query.toString());
        PostCreateVo vo = postService.createPost(query,currentUserId);
        return Result.success(vo);
    }
}

