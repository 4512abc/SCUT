package org.example.utils;

import lombok.extern.slf4j.Slf4j;

import java.util.Collections;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

/**
 * 游标分页工具类
 */
@Slf4j
public class CursorPageUtil {

    /**
     * 执行游标分页查询
     * @param queryFunction 查询函数
     * @param cursorExtractor 游标值提取函数
     * @param requestSize 请求大小
     * @param lastCursor 上一页游标
     * @param <T> 数据类型
     * @param <R> 游标类型
     * @return 分页结果
     */
    public static <T, R> PageResult<T> paginate(
            Function<PageParam, List<T>> queryFunction,
            Function<T, R> cursorExtractor,
            Integer requestSize,
            String lastCursor) {

        // 检查游标是否为空，如果为空则直接返回空数据
        if (lastCursor == null || lastCursor.isEmpty()) {
            return new PageResult<>(Collections.emptyList(), null);
        }

        // 实际查询数量：多查1条用于判断是否有下一页
        int querySize = requestSize != null ? requestSize + 1 : 11;
        log.info("【分页查询完成】总数据量={}, lastCursor={}", querySize, lastCursor);
        
        // 执行查询
        List<T> items = queryFunction.apply(new PageParam(querySize, lastCursor));
        log.info("【分页查询详情】");
        log.info("│─ 请求参数: requestSize={}, lastCursor={}", requestSize, lastCursor);
        log.info("│─ 实际查询: querySize={}", querySize);
        log.info("│─ 获取数据: 实际查询到{}条记录", items.size());
        // 计算是否有更多数据
        boolean hasMore = items.size() > (requestSize != null ? requestSize : 10);
        String nextCursor = hasMore ?
                String.valueOf(cursorExtractor.apply(items.get(items.size() - 1))) : null;

        // 截取结果（移除多余的最后一条）
        List<T> resultList = items.stream()
                .limit(requestSize != null ? requestSize : 10)
                .collect(Collectors.toList());

        return new PageResult<>(resultList, nextCursor);
    }

    /**
     * 分页参数
     */
    public static class PageParam {
        private final Integer size;
        private final String lastCursor;

        public PageParam(Integer size, String lastCursor) {
            this.size = size;
            this.lastCursor = lastCursor;
        }

        public Integer getSize() {
            return size;
        }

        public String getLastCursor() {
            return lastCursor;
        }
    }

    /**
     * 分页结果
     * @param <T> 数据类型
     */
    public static class PageResult<T> {
        private final List<T> data;
        private final String nextCursor;

        public PageResult(List<T> data, String nextCursor) {
            this.data = data;
            this.nextCursor = nextCursor;
        }

        public List<T> getData() {
            return data;
        }

        public String getNextCursor() {
            return nextCursor;
        }
    }
}