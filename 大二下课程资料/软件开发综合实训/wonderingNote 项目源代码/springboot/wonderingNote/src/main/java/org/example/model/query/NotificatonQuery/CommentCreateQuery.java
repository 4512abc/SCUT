package org.example.model.query.NotificatonQuery;

import com.fasterxml.jackson.annotation.JsonProperty;

/**
 * @Author: fs
 * @Date: 2025/4/2300:19
 */
public class CommentCreateQuery {
    private String content;
    @JsonProperty(("parent_id"))
    private Long parentId;

    // Getters and Setters
    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public Long getParentId() {
        return parentId;
    }

    public void setParentId(Long parentId) {
        this.parentId = parentId;
    }
}
