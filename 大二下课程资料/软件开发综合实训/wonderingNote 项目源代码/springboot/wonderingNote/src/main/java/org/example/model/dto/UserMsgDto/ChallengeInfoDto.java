package org.example.model.dto.UserMsgDto;
import java.util.Date;

public class ChallengeInfoDto {
    private ChallengeDto challenge;
    private ParticipationDto participation;
    private String creatorAccount;

    // Getters and Setters
    public ChallengeDto getChallenge() {
        return challenge;
    }

    public void setChallenge(ChallengeDto challenge) {
        this.challenge = challenge;
    }

    public ParticipationDto getParticipation() {
        return participation;
    }

    public void setParticipation(ParticipationDto participation) {
        this.participation = participation;
    }

    public String getCreatorAccount() {
        return creatorAccount;
    }

    public void setCreatorAccount(String creatorAccount) {
        this.creatorAccount = creatorAccount;
    }

    public static class ChallengeDto {
        private Long id;
        private String title;
        private String description;
        private Long creatorId;
        private String objectType;
        private String gestureType;
        private Long landmarkId;
        private Double radius;
        private Date startTime;
        private Date endTime;
        private Integer participants;
        private Date createTime;
        private byte[] location;

        // Getters and Setters
        public Long getId() {
            return id;
        }

        public void setId(Long id) {
            this.id = id;
        }

        public String getTitle() {
            return title;
        }

        public void setTitle(String title) {
            this.title = title;
        }

        public String getDescription() {
            return description;
        }

        public void setDescription(String description) {
            this.description = description;
        }

        public Long getCreatorId() {
            return creatorId;
        }

        public void setCreatorId(Long creatorId) {
            this.creatorId = creatorId;
        }

        public String getObjectType() {
            return objectType;
        }

        public void setObjectType(String objectType) {
            this.objectType = objectType;
        }

        public String getGestureType() {
            return gestureType;
        }

        public void setGestureType(String gestureType) {
            this.gestureType = gestureType;
        }

        public Long getLandmarkId() {
            return landmarkId;
        }

        public void setLandmarkId(Long landmarkId) {
            this.landmarkId = landmarkId;
        }

        public Double getRadius() {
            return radius;
        }

        public void setRadius(Double radius) {
            this.radius = radius;
        }

        public Date getStartTime() {
            return startTime;
        }

        public void setStartTime(Date startTime) {
            this.startTime = startTime;
        }

        public Date getEndTime() {
            return endTime;
        }

        public void setEndTime(Date endTime) {
            this.endTime = endTime;
        }

        public Integer getParticipants() {
            return participants;
        }

        public void setParticipants(Integer participants) {
            this.participants = participants;
        }

        public Date getCreateTime() {
            return createTime;
        }

        public void setCreateTime(Date createTime) {
            this.createTime = createTime;
        }

        public byte[] getLocation() {
            return location;
        }

        public void setLocation(byte[] location) {
            this.location = location;
        }
    }
    public static class ParticipationDto {
        private Long id;
        private Long userId;
        private Long challengeId;
        private Date completeTime;
        private String evidence;

        // Getters and Setters
        public Long getId() {
            return id;
        }

        public void setId(Long id) {
            this.id = id;
        }

        public Long getUserId() {
            return userId;
        }

        public void setUserId(Long userId) {
            this.userId = userId;
        }

        public Long getChallengeId() {
            return challengeId;
        }

        public void setChallengeId(Long challengeId) {
            this.challengeId = challengeId;
        }

        public Date getCompleteTime() {
            return completeTime;
        }

        public void setCompleteTime(Date completeTime) {
            this.completeTime = completeTime;
        }

        public String getEvidence() {
            return evidence;
        }

        public void setEvidence(String evidence) {
            this.evidence = evidence;
        }
    }
}