package org.example.model.dto.UserDto;

public class WxLoginDto {
    /**
     * 微信服务器上辨识用户的唯一id
     */
    private String openid;

    /**
     * 身份凭证
     */
    private String session_key;

    /**
     * 错误代码
     */
    private String errcode;

    public String getErrmsg() {
        return errmsg;
    }

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrcode() {
        return errcode;
    }

    public void setErrcode(String errcode) {
        this.errcode = errcode;
    }

    public String getSession_key() {
        return session_key;
    }

    public void setSession_key(String session_key) {
        this.session_key = session_key;
    }

    public String getOpenid() {
        return openid;
    }

    public void setOpenid(String openid) {
        this.openid = openid;
    }

    /**
     * 错误信息
     */
    private String errmsg;
}
