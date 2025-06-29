package org.example.model.vo.SearchInfoVo;


import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.example.model.entity.PostWithBLOBs;

import java.util.Date;

@Data
public class SearchPostVo {
    private Integer commentCount;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date createdTime;
    private Integer likeCount;
    private Long postId;
    private String publishedAccount;
    private Long publishedId;
    private String title;

    public SearchPostVo(PostWithBLOBs postWithBLOBs, Integer commentCount, Integer likeCount,String publishAccount) {
        this.commentCount = commentCount;
        this.createdTime = postWithBLOBs.getCreateTime();
        this.likeCount = likeCount;
        this.postId = postWithBLOBs.getId();
        this.publishedAccount = publishAccount;
        this.publishedId = postWithBLOBs.getUserId();
        this.title = postWithBLOBs.getTitle();
    }
}