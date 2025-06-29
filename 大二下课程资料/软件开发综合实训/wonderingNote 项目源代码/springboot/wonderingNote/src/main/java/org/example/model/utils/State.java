package org.example.model.utils;

import lombok.extern.slf4j.Slf4j;
import org.example.exception.CustomException;

import static org.example.common.result.ResultCode.ENUM_ERROR;

@Slf4j
public enum State {
    ACTIVE("ACTIVE"),
    SUSPENDED("SUSPENDED"),
    FORZEN("FORZEN"),
    DELETED("DELETED");

    private final String value;

    State(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    // 可选：添加一个方法，根据字符串值返回对应的枚举
    public static State fromValue(String value) {
        for (State state : State.values()) {
            if (state.getValue().equals(value)) {
                return state;
            }
        }
        log.error("Invalid state value: {}", value);
        throw new CustomException(ENUM_ERROR);
    }
}
