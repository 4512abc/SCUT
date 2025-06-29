package org.example.model.vo.UserMsgVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.databind.JsonNode;
import java.util.Date;

public class HomeInfoVo {


    @JsonProperty("base_info")
    private BaseInfo baseInfo;

    @JsonProperty("profile_info")
    private ProfileInfo profileInfo;

    // ------------------------ Getters & Setters ------------------------
    public BaseInfo getBaseInfo() {
        return baseInfo;
    }

    public void setBaseInfo(BaseInfo baseInfo) {
        this.baseInfo = baseInfo;
    }

    public ProfileInfo getProfileInfo() {
        return profileInfo;
    }

    public void setProfileInfo(ProfileInfo profileInfo) {
        this.profileInfo = profileInfo;
    }

    // ------------------------ 嵌套类：基础信息 ------------------------
    public static class BaseInfo {
@JsonProperty("account")
        private String account;

@JsonProperty("phone")
        private String phone;

@JsonProperty("email")
        private String email;

@JsonProperty("avatar")
        private String avatar;


        @JsonProperty("status")
        private String status;


        @JsonProperty("wx_openid")
        private String wxOpenid;


        @JsonProperty("wx_unionid")
        private String wxUnionid;


        @JsonProperty("create_time")
        private Date createTime;


        @JsonProperty("update_time")
        private Date updateTime;

        @JsonProperty("access_level")
        private String accessLevel;

        // ------------------------ Getters & Setters ------------------------
        public String getAccount() {
            return account;
        }

        public void setAccount(String account) {
            this.account = account;
        }

        public String getPhone() {
            return phone;
        }

        public void setPhone(String phone) {
            this.phone = phone;
        }

        public String getEmail() {
            return email;
        }

        public void setEmail(String email) {
            this.email = email;
        }

        public String getAvatar() {
            return avatar;
        }

        public void setAvatar(String avatar) {
            this.avatar = avatar;
        }

        public String getStatus() {
            return status;
        }

        public void setStatus(String status) {
            this.status = status;
        }

        public String getWxOpenid() {
            return wxOpenid;
        }

        public void setWxOpenid(String wxOpenid) {
            this.wxOpenid = wxOpenid;
        }

        public String getWxUnionid() {
            return wxUnionid;
        }

        public void setWxUnionid(String wxUnionid) {
            this.wxUnionid = wxUnionid;
        }

        public Date getCreateTime() {
            return createTime;
        }

        public void setCreateTime(Date createTime) {
            this.createTime = createTime;
        }

        public Date getUpdateTime() {
            return updateTime;
        }

        public void setUpdateTime(Date updateTime) {
            this.updateTime = updateTime;
        }

        public String getAccessLevel() {
            return accessLevel;
        }

        public void setAccessLevel(String accessLevel) {
            this.accessLevel = accessLevel;
        }
    }

    // ------------------------ 嵌套类：资料信息 ------------------------
    public static class ProfileInfo {
@JsonProperty("gender")
        private String gender;
@JsonProperty("birthday")
        private Date birthday;
@JsonProperty("bio")
        private String bio;

@JsonProperty("location")
        private String location;
@JsonProperty("settings")
        private JsonNode settings;

        // ------------------------ Getters & Setters ------------------------
        public String getGender() {
            return gender;
        }

        public void setGender(String gender) {
            this.gender = gender;
        }

        public Date getBirthday() {
            return birthday;
        }

        public void setBirthday(Date birthday) {
            this.birthday = birthday;
        }

        public String getBio() {
            return bio;
        }

        public void setBio(String bio) {
            this.bio = bio;
        }

        public String getLocation() {
            return location;
        }

        public void setLocation(String location) {
            this.location = location;
        }

        public JsonNode getSettings() {
            return settings;
        }

        public void setSettings(JsonNode settings) {
            this.settings = settings;
        }
    }
}