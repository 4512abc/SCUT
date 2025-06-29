package org.example.service;

import cn.hutool.core.io.FileUtil;
import lombok.extern.slf4j.Slf4j;
import org.example.common.result.Result;
import org.example.exception.CustomException;
import org.example.mapper.FileInfoMapper;
import org.example.model.dto.FileInfoDto.FileInfoDto;
import org.example.model.entity.FileInfo;
import org.example.model.vo.FileInfoVo.FileUploadVo;
import org.example.utils.FileUrlUtil;
import org.example.utils.IdJsonUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;
import org.example.model.dto.FileInfoDto.FileUpLoadDto;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import static org.example.common.constants.Constants.BASEIMG_PATH;
import static org.example.common.constants.Constants.BASEVIDEO_PATH;
import static org.example.common.result.ResultCode.*;
import static org.example.common.result.ResultCode.FILE_PATH_ERROR;

@Slf4j
@Service
public class FileInfoService {
    @Autowired
    private FileInfoMapper fileInfoMapper;

    public FileUpLoadDto add(MultipartFile file) throws IOException {
        String originalFilename = file.getOriginalFilename();
        if (file.isEmpty()) {
            throw new CustomException(FILE_NOT_EXIST_ERROR);
        }
        if (originalFilename == null || originalFilename.equals("")) {
          throw new CustomException(FILE_NAME_NULL);
        }

        // 检查文件扩展名
        String extension = FileUtil.extName(originalFilename).toLowerCase();
        String filePath;

        if (extension.matches("png|jpg|jpeg|gif|webp")) {
            filePath = BASEIMG_PATH;
        } else if (extension.matches("mp4|avi|mov|mkv|flv|wmv")) {
            filePath = BASEVIDEO_PATH;
        } else {
            throw new CustomException(FILE_TYPE_ERROR);
        }
        // 确保目录存在
        FileUtil.mkdir(System.getProperty("user.dir") +filePath);

        // 给文件名加时间戳
        String fileName = FileUtil.mainName(originalFilename) + System.currentTimeMillis() + "."+FileUtil.extName(originalFilename);
        // 上传文件
        FileUtil.writeBytes(file.getBytes(), System.getProperty("user.dir")+filePath + fileName);

        // 信息入库，获取到文件id
        FileInfo fileInfo = new FileInfo();
        fileInfo.setFileName(fileName);
        fileInfo.setOriginName(originalFilename);
        fileInfo.setFilePath(filePath);
        fileInfo.setFileSuffix(extension);

        fileInfoMapper.insert(fileInfo);
        FileUpLoadDto fileUpLoadDto = new FileUpLoadDto();
        fileUpLoadDto.setFile_url(FileUrlUtil.generateFileUrlJson(fileInfo.getId()));
        fileUpLoadDto.setOrigin_name(originalFilename);
        fileUpLoadDto.setId(fileInfo.getId());
        return fileUpLoadDto;
    }

    /**
     * 批量上传文件
     */
    public List<FileUploadVo> batchAdd(List<MultipartFile> files) throws IOException {
        List<FileUploadVo> result = new ArrayList<>();
        List<String> failedFiles = new ArrayList<>(); // 记录上传失败的文件名
        List<FileInfo> uploadedFiles = new ArrayList<>(); // 记录成功上传的文件信息

        for (MultipartFile file : files) {
            try {
                FileUpLoadDto fileUpLoadDto = add(file);
                result.add(new FileUploadVo(fileUpLoadDto)); // 将成功上传的文件信息添加到结果列表
                uploadedFiles.add(fileInfoMapper.selectByPrimaryKey(fileUpLoadDto.getId())); // 记录成功上传的文件信息
            } catch (Exception e) {
                log.error("文件上传失败: {}", file.getOriginalFilename(), e);
                failedFiles.add(file.getOriginalFilename()); // 记录失败的文件名
            }
        }

        // 如果有文件上传失败，删除所有已上传的文件
        if (!failedFiles.isEmpty()) {
            for (FileInfo fileInfo : uploadedFiles) {
                FileUtil.del(fileInfo.getFilePath() + fileInfo.getFileName());
                fileInfoMapper.deleteByPrimaryKey(fileInfo.getId());
            }
            throw new CustomException(FILE_UPLOAD_PARTIAL_FAILURE);
        }

        return result;
    }

    public void delete(Long id) {
        FileInfo fileInfo = fileInfoMapper.selectByPrimaryKey(id);
        if(fileInfo==null){
            throw new CustomException(FILE_NOT_EXIST_ERROR);
        }
        FileUtil.del(fileInfo.getFilePath()+fileInfo.getFileName());
        fileInfoMapper.deleteByPrimaryKey(id);
    }

    public FileInfoDto findById(Long id) {
        FileInfo fileInfo = fileInfoMapper.selectByPrimaryKey(id);
        if(fileInfo==null)
            throw new CustomException(FILE_NOT_EXIST_ERROR);
        FileInfoDto fileInfoDto = new FileInfoDto();
        BeanUtils.copyProperties(fileInfo,fileInfoDto);
//        fileInfoDto.setId(fileInfo.getId());
//        fileInfoDto.setFileName(fileInfo.getFileName());
//        fileInfoDto.setOriginName(fileInfo.getOriginName());
//        fileInfoDto.setFilePath(fileInfo.getFilePath());
        return fileInfoDto;
    }

    public FileInfoDto download(Long id) {
        if (id == null) {
            throw new CustomException(FILE_NOT_EXIST_ERROR);
        }
        FileInfoDto fileInfoDto = findById(id);
        if (fileInfoDto == null) {
            throw new CustomException(FILE_PATH_ERROR);
        }

        log.info("FileInfoDto: {}", fileInfoDto);
        log.info("FilePath: {}", fileInfoDto.getFilePath());
        log.info("FileName: {}", fileInfoDto.getFileName());

        return fileInfoDto;
    }

}
