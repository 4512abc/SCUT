package org.example.utils;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.example.model.dto.FileInfoDto.FileInfoDto;
import org.example.service.FileInfoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
//根据id生成对应文件URL，存储到数据库和返回给前端都会以这种形式进行！
@Component
public class FileUrlUtil {

    private static FileInfoService staticFileInfoService;

    @Autowired
    private FileInfoService fileInfoService;

    @PostConstruct
    public void init() {
        staticFileInfoService = this.fileInfoService;
    }

    private static final ObjectMapper objectMapper = new ObjectMapper();

    /**
     * 根据文件ID生成包含URL的JSON字符串
     * @param fileId 文件ID
     * @return JSON字符串 格式：{"id":1,"url":"/api/files/1/download"}
     */
    public static String generateFileUrlJson(Long fileId) {
        Map<String, Object> result = new HashMap<>();

        if (fileId == null) {
            return toJsonString(result);
        }

        FileInfoDto fileInfo = staticFileInfoService.findById(fileId);
        if (fileInfo == null) {
            return toJsonString(result);
        }

        result.put("id", fileId);
        result.put("url", "/api/files/" + fileId + "/download");

        return toJsonString(result);
    }

    /**
     * 批量生成文件URL JSON数组
     * @param fileIds 文件ID列表
     * @return JSON数组字符串 格式：[{"id":1,"url":"..."},...]
     */
    public static String generateBatchFileUrlsJson(List<Long> fileIds) {
        List<Map<String, Object>> result = new ArrayList<>();
        if (fileIds != null) {
            for (Long fileId : fileIds) {
                String singleJson = generateFileUrlJson(fileId);
                try {
                    Map<String, Object> map = objectMapper.readValue(singleJson, HashMap.class);
                    if (!map.isEmpty()) {
                        result.add(map);
                    }
                } catch (JsonProcessingException ignored) {
                    // 忽略转换异常
                }
            }
        }
        return toJsonString(result);
    }

    static String toJsonString(Object obj) {
        try {
            return objectMapper.writeValueAsString(obj);
        } catch (JsonProcessingException e) {
            return "{}"; // 或返回"[]"对于数组情况
        }
    }
    public static String getFirstFileFromJsonArray(String jsonArrayStr) {
        if (jsonArrayStr == null || jsonArrayStr.isEmpty()) {
            return "{}";
        }

        try {
            List<Map<String, Object>> fileList = objectMapper.readValue(
                    jsonArrayStr,
                    objectMapper.getTypeFactory().constructCollectionType(List.class, Map.class)
            );

            if (fileList != null && !fileList.isEmpty()) {
                Map<String, Object> firstFile = fileList.get(0);
                return toJsonString(firstFile);
            }
        } catch (JsonProcessingException e) {
            // 忽略解析异常
        }

        return "{}";
    }

}


