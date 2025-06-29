package org.example.controller;

import cn.hutool.core.io.FileUtil;
import cn.hutool.core.util.StrUtil;
import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.exception.CustomException;
import org.example.model.dto.FileInfoDto.FileInfoDto;
import org.example.model.entity.FileInfo;
import org.example.model.vo.FileInfoVo.FileUploadVo;
import org.example.service.FileInfoService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.URLEncoder;
import java.util.List;

import static org.example.common.result.ResultCode.*;

@Slf4j
@RestController
@RequestMapping(value="/api/files")
public class FileInfoController {

    @Autowired
    private FileInfoService fileInfoService;

    private static final Logger logger = LoggerFactory.getLogger(FileInfoService.class);

    /**
     * 上传文件
     */
    @PostMapping("/upload")
    public Result upload(MultipartFile file) throws IOException {
        FileUploadVo fileUploadVo = new FileUploadVo(fileInfoService.add(file));
        if (fileUploadVo!= null) {
            return Result.success(fileUploadVo);
        } else {
            return Result.error(FILE_CREATE_ERROR);
        }
    }

    /**
     * 批量上传文件
     */
    @PostMapping("/batch_upload")
    public Result<List<FileUploadVo>> batchUpload(List<MultipartFile> files) {
        try {
            List<FileUploadVo> result = fileInfoService.batchAdd(files);
            return Result.success(result);
        } catch (Exception e) {
            log.error("批量上传文件失败", e);
            return Result.error(FILE_CREATE_ERROR);
        }
    }

    @DeleteMapping("/{id}")
    public Result delete(@PathVariable Long id){
        fileInfoService.delete(id);
        return Result.success(FILE_DELETE_SUCCESS);
    }

    @GetMapping("/{id}")
    public Result<FileInfoDto> findById(@PathVariable Long id){
        FileInfoDto fileInfoDto = fileInfoService.findById(id);
        if (fileInfoDto!= null) {
            return Result.success(fileInfoDto);
        } else {
            return Result.error(FILE_NOT_EXIST_ERROR);
        }
    }

    @GetMapping("/{id}/download")
    public void download(@PathVariable Long id, HttpServletResponse response) throws IOException {
        FileInfoDto fileInfoDto = fileInfoService.download(id);
        String fullFilePath = System.getProperty("user.dir")+fileInfoDto.getFilePath() + fileInfoDto.getFileName();

        byte[] bytes = FileUtil.readBytes(fullFilePath);
        if(bytes==null){
            throw new CustomException(FILE_NOT_EXIST_ERROR);
        }
        response.reset();
        // 设置response的header
        response.addHeader("Content-Disposition", "attachment;filename=" +
                URLEncoder.encode(fileInfoDto.getOriginName(), "UTF-8"));
        response.addHeader("Content-Length", "" + bytes.length);
        response.setContentType("application/octet-stream");
        OutputStream toClient = new BufferedOutputStream(response.getOutputStream());
        toClient.write(bytes);
        toClient.flush();
        toClient.close();
    }

}
