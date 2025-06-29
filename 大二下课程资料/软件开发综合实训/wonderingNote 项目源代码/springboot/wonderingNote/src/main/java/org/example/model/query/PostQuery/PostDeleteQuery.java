package org.example.model.query.PostQuery;

import com.fasterxml.jackson.annotation.JsonProperty;

public class PostDeleteQuery {
    @JsonProperty("post_id")
    private Long postId;

    public Long getPostId() {
        return postId;
    }

    public void setPostId(Long postId) {
        this.postId = postId;
    }
}