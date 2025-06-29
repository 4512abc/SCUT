// dto/UserMsgDto/HomeInfoDto.java
package org.example.model.dto.UserMsgDto;

import java.util.Date;

public class HomeInfoDto {
    private UserBaseDto baseInfo;
    private UserProfileDto profileInfo;

    // Getters and Setters
    public UserBaseDto getBaseInfo() {
        return baseInfo;
    }

    public void setBaseInfo(UserBaseDto baseInfo) {
        this.baseInfo = baseInfo;
    }

    public UserProfileDto getProfileInfo() {
        return profileInfo;
    }

    public void setProfileInfo(UserProfileDto profileInfo) {
        this.profileInfo = profileInfo;
    }

    public static class UserBaseDto {
        private String account;
        private String phone;
        private String email;
        private String avatar;
        private String status;
        private String wxOpenid;
        private String wxUnionid;
        private Date createTime;
        private Date updateTime;
        private String accessLevel;
        private String password;

        // Getters and Setters
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
        public String getPassword() {
            return password;
        }
        public void setPassword(String password) {
            this.password = password;
        }
    }

    public static class UserProfileDto {
        private Integer gender;
        private String nickname;
        private Date birthday;
        private String bio;
        private String location;
        private String settings;

        // Getters and Setters
        public Integer getGender() {
            return gender;
        }

        public void setGender(Integer gender) {
            this.gender = gender;
        }

        public String getNickName() {
            return nickname;
        }

        public void setNickName(String nickName) {
            this.nickname = nickName;
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

        public String getSettings() {
            return settings;
        }

        public void setSettings(String settings) {
            this.settings = settings;
        }
    }
}