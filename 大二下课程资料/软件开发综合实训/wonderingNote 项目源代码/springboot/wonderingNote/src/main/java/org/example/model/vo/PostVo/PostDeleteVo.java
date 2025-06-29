package org.example.model.vo.PostVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class PostDeleteVo {
    @JsonProperty("success")
    private boolean success;

}