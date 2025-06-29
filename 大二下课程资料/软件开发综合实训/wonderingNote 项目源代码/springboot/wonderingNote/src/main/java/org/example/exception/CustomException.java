package org.example.exception;

/**
 * @Author: fs
 * @Date: 2025/4/1709:23
 */

import org.example.common.result.ResultCode;

/*
 * 用户自定义异常，用于前端返回错误信息
 * */
public class CustomException extends RuntimeException {
    private String code;
    private String msg;

    public CustomException(String code, String msg) {
        this.code = code;
        this.msg = msg;
    }

    public CustomException(ResultCode resultCode) {
        this.code = resultCode.code;
        this.msg = resultCode.msg;
    }

    public String getCode() {
        return code;
    }
    public String getMessage() {
        return msg;
    }
}
