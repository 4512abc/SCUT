package org.example.model.query.UserQuery;

public class WxLoginQuery {
    /**
     * 临时登录凭证
     */
    private String code;

    /**
     * 微信服务器上的唯一id
     */
    private String openId;

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public String getOpenId() {
        return openId;
    }

    public void setOpenId(String openId) {
        this.openId = openId;
    }
}
