package org.example.utils;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.example.utils.FileUrlUtil.toJsonString;

@Slf4j
@Component
public class IdJsonUtils {

    private static final ObjectMapper objectMapper = new ObjectMapper();

    // 新增枚举类型表示键值
    public enum KeyIdEnum {
        CHALLENGE_ID("challenge_id"),
        USER_ID("user_id"),
        TEAM_ID("team_id");

        private final String key;

        KeyIdEnum(String key) {
            this.key = key;
        }

        public String getKey() {
            return key;
        }
    }

    /**
     * 根据挑战ID生成包含JSON字符串
     * @param keyId 键值类型
     * @param id ID值
     * @return JSON字符串 格式：{"challenge_id":123}
     */
    public static String generateIdJson(KeyIdEnum keyId, Long id) {
        Map<String, Object> result = new HashMap<>();

        if (id == null) {
            return toJsonString(result);
        }

        result.put(keyId.getKey(), id);

        return toJsonString(result);
    }

    /**
     * 批量生成挑战ID的JSON数组
     * @param keyId 键值类型
     * @param ids ID列表
     * @return JSON数组字符串 格式：[{"challenge_id":123},...]
     */
    public static String generateIdsJson(KeyIdEnum keyId, List<Long> ids) {
        List<Map<String, Object>> result = new ArrayList<>();
        if (ids != null) {
            for (Long id : ids) {
                Map<String, Object> map = new HashMap<>();
                map.put(keyId.getKey(), id);
                result.add(map);
            }
        }
        try {
            return objectMapper.writeValueAsString(result);
        } catch (JsonProcessingException e) {
            log.error("Failed to convert list to JSON string: {}", e.getMessage());
            return "[]"; // 返回空数组作为默认值
        }
    }

    public static String generateMapJson(Map<String,Object> map) {
        try {
            return objectMapper.writeValueAsString(map);
        } catch (JsonProcessingException e) {
            log.error("Failed to convert map to JSON string: {}", e.getMessage());
            return "[]"; // 返回空数组作为默认值
        }
    }

    /**
     * 从JSON字符串中提取第一个挑战ID
     * @param jsonArrayStr JSON数组字符串
     * @return JSON字符串 格式：{"challenge_id":123}
     */
    public static List<Map<String, Long>> getIdFromJsonArray(String jsonArrayStr) {
        if (jsonArrayStr == null || jsonArrayStr.isEmpty()) {
            return new ArrayList<>();
        }

        // 去除转义字符
        jsonArrayStr = jsonArrayStr.replace("\\", "");
        log.info("After removing escape characters: {}", jsonArrayStr); // 添加日志打印

        // 去除首尾的单引号
        jsonArrayStr = jsonArrayStr.replaceAll("^['\"]|['\"]$", "");

        try {
            List<Map<String, Object>> list = objectMapper.readValue(
                    jsonArrayStr,
                    objectMapper.getTypeFactory().constructCollectionType(List.class, Map.class)
            );

            List<Map<String, Long>> result = new ArrayList<>();
            if (list != null && !list.isEmpty()) {
                for (Map<String, Object> map : list) {
                    Map<String, Long> newMap = getStringLongMap(map);
                    result.add(newMap);
                }
            }
            return result;
        } catch (JsonProcessingException e) {
            log.info("在ID转换过程中出错: {}", e.getMessage());
        }

        return new ArrayList<>();
    }

    private static Map<String, Long> getStringLongMap(Map<String, Object> map) {
        Map<String, Long> newMap = new HashMap<>();
        for (Map.Entry<String, Object> entry : map.entrySet()) {
            Object value = entry.getValue();
            if (value instanceof Long) {
                newMap.put(entry.getKey(), (Long) value);
            } else if (value instanceof Integer) {
                newMap.put(entry.getKey(), ((Integer) value).longValue());
            } else {
                // 处理非 Long 和 Integer 类型的情况，可以根据需求进行调整
                throw new IllegalArgumentException("Value is not of type Long or Integer");
            }
        }
        return newMap;
    }

}
