package org.example.model.vo.common;

import com.fasterxml.jackson.annotation.JsonProperty;
import java.util.List;

public class PageResultVo<T> {
    @JsonProperty("data")
    private List<T> data;

    @JsonProperty("nextCursor")
    private String nextCursor;

    public PageResultVo(List<T> data, String nextCursor) {
        this.data = data;
        this.nextCursor = nextCursor;
    }

    // Getters
    public List<T> getData() {
        return data;
    }

    public String getNextCursor() {
        return nextCursor;
    }


}