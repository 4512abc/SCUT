package org.example.common.result;

/*
 * 统一返回前端结果类
 * */
public class Result<T> {
    /* 返回码 */
    private String code;
    /* 返回中文信息 */
    private String msg;
    /* 返回的对象类，为一个泛型 */
    private T data;

    /* 不带参数的成功返回 */
    public static Result success() {
        Result result = new Result<>();
        result.setCode(ResultCode.SUCCESS.code);
        result.setMsg(ResultCode.SUCCESS.msg);
        return result;
    }

    /* 带参数的成功返回 */
    public static <T> Result<T> success(T data) {
        Result<T> result = new Result<>(data);
        result.setCode(ResultCode.SUCCESS.code);
        result.setMsg(ResultCode.SUCCESS.msg);
        return result;
    }

    /* 不带参数的失败返回 */
    public static Result error() {
        Result result = new Result<>();
        result.setCode(ResultCode.ERROR.code);
        result.setMsg(ResultCode.ERROR.msg);
        return result;
    }

    /* 带参数的失败返回 自定义的 */
    public static Result error(String code, String msg) {
        Result result = new Result<>();
        result.setCode(code);
        result.setMsg(msg);
        return result;
    }

    /* 带参数的失败返回 根据ResultCode */
    public static Result error(ResultCode resultCode) {
        Result result = new Result<>();
        result.setCode(resultCode.code);
        result.setMsg(resultCode.msg);
        return result;
    }

    public static <T> Result<T> error(T data) {
        Result<T> result = new Result<>(data);
        result.setCode(ResultCode.ERROR.code);
        result.setMsg(ResultCode.ERROR.msg);
        return result;
    }

    /* 带参数的成功返回 根据ResultCode */
    public static <T> Result<T> success(ResultCode resultCode, T data) {
        Result<T> result = new Result<>(data);
        result.setCode(resultCode.code);
        result.setMsg(resultCode.msg);
        return result;
    }

    public static <T> Result<T> error(ResultCode resultCode, T data) {
        Result<T> result = new Result<>(data);
        result.setCode(resultCode.code);
        result.setMsg(resultCode.msg);
        return result;
    }

    public Result(T data) {
        this.data = data;
    }

    public Result() {
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }
}
