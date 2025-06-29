package org.example.model.dto.FileInfoDto;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class FileInfoDto {
    @JsonProperty("id")
    private Long id;
    @JsonProperty("file_name")
    private String fileName;
    @JsonProperty("origin_name")
    private String originName;
    @JsonProperty("file_path")
    private String filePath;
}
