package org.example.model.vo.FileInfoVo;

import lombok.Data;
import org.example.model.dto.FileInfoDto.FileUpLoadDto;

@Data
public class FileUploadVo {
    private String origin_name;
    private String file_url;

    public FileUploadVo(FileUpLoadDto fileUpLoadDto) {
        this.origin_name = fileUpLoadDto.getOrigin_name();
        this.file_url = fileUpLoadDto.getFile_url();
    }
    public FileUploadVo() {
        this.origin_name = "";
        this.file_url = "";
    }
}
