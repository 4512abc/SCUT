package org.example.model.vo.FileInfoVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class FileInfoVo {

    private Long id;
    @JsonProperty("file_name")
    private String fileName;
    @JsonProperty("origin_name")
    private String originName;
}
