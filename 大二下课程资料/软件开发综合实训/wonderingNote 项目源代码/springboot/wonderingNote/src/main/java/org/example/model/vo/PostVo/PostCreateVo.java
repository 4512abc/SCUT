package org.example.model.vo.PostVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class PostCreateVo {
    @JsonProperty("id")
    private Long id;
}