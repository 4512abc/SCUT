package org.example.model.utils;

import lombok.extern.slf4j.Slf4j;
import org.example.exception.CustomException;

import static org.example.common.result.ResultCode.ENUM_ERROR;

@Slf4j
public enum AccessLevel {
    SUPER_ADMIN("super_admin"),
    ADMIN("admin"),
    USER("user");

    private final String value;

    AccessLevel(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public static AccessLevel fromValue(String value) {
        for (AccessLevel accessLevel : AccessLevel.values()) {
            if (accessLevel.getValue().equals(value)) {
                return accessLevel;
            }
        }
        log.error("Invalid access level value: {}", value);
        throw new CustomException(ENUM_ERROR);
    }
}
