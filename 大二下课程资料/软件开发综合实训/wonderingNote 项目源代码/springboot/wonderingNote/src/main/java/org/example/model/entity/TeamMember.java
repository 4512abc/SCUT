package org.example.model.entity;

import java.util.Date;

/**
 * Database Table Remarks:
 *   群组成员表：记录群组成员及其角色信息
 *
 * This class was generated by MyBatis Generator.
 * This class corresponds to the database table team_member
 */
public class TeamMember extends TeamMemberKey {
    /**
     * Database Column Remarks:
     *   成员角色：0-普通成员 1-管理员
     *
     * This field was generated by MyBatis Generator.
     * This field corresponds to the database column team_member.role
     *
     * @mbg.generated
     */
    private Byte role;

    /**
     * Database Column Remarks:
     *   加入时间
     *
     * This field was generated by MyBatis Generator.
     * This field corresponds to the database column team_member.join_time
     *
     * @mbg.generated
     */
    private Date joinTime;

    /**
     * Database Column Remarks:
     *   其他信息(JSON格式)
     *
     * This field was generated by MyBatis Generator.
     * This field corresponds to the database column team_member.other_info
     *
     * @mbg.generated
     */
    private String otherInfo;

    /**
     * This method was generated by MyBatis Generator.
     * This method returns the value of the database column team_member.role
     *
     * @return the value of team_member.role
     *
     * @mbg.generated
     */
    public Byte getRole() {
        return role;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method sets the value of the database column team_member.role
     *
     * @param role the value for team_member.role
     *
     * @mbg.generated
     */
    public void setRole(Byte role) {
        this.role = role;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method returns the value of the database column team_member.join_time
     *
     * @return the value of team_member.join_time
     *
     * @mbg.generated
     */
    public Date getJoinTime() {
        return joinTime;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method sets the value of the database column team_member.join_time
     *
     * @param joinTime the value for team_member.join_time
     *
     * @mbg.generated
     */
    public void setJoinTime(Date joinTime) {
        this.joinTime = joinTime;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method returns the value of the database column team_member.other_info
     *
     * @return the value of team_member.other_info
     *
     * @mbg.generated
     */
    public String getOtherInfo() {
        return otherInfo;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method sets the value of the database column team_member.other_info
     *
     * @param otherInfo the value for team_member.other_info
     *
     * @mbg.generated
     */
    public void setOtherInfo(String otherInfo) {
        this.otherInfo = otherInfo == null ? null : otherInfo.trim();
    }
}