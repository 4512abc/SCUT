package org.example.model.entity;

/**
 * Database Table Remarks:
 *   地标表：存储地理位置标志点信息
 *
 * This class was generated by MyBatis Generator.
 * This class corresponds to the database table landmark
 */
public class Landmark {
    /**
     * Database Column Remarks:
     *   地标ID
     *
     * This field was generated by MyBatis Generator.
     * This field corresponds to the database column landmark.id
     *
     * @mbg.generated
     */
    private Long id;

    /**
     * Database Column Remarks:
     *   地标名称
     *
     * This field was generated by MyBatis Generator.
     * This field corresponds to the database column landmark.name
     *
     * @mbg.generated
     */
    private String name;

    /**
     * Database Column Remarks:
     *   地标位置坐标
     *
     * This field was generated by MyBatis Generator.
     * This field corresponds to the database column landmark.location
     *
     * @mbg.generated
     */
    private byte[] location;

    /**
     * This method was generated by MyBatis Generator.
     * This method returns the value of the database column landmark.id
     *
     * @return the value of landmark.id
     *
     * @mbg.generated
     */
    public Long getId() {
        return id;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method sets the value of the database column landmark.id
     *
     * @param id the value for landmark.id
     *
     * @mbg.generated
     */
    public void setId(Long id) {
        this.id = id;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method returns the value of the database column landmark.name
     *
     * @return the value of landmark.name
     *
     * @mbg.generated
     */
    public String getName() {
        return name;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method sets the value of the database column landmark.name
     *
     * @param name the value for landmark.name
     *
     * @mbg.generated
     */
    public void setName(String name) {
        this.name = name == null ? null : name.trim();
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method returns the value of the database column landmark.location
     *
     * @return the value of landmark.location
     *
     * @mbg.generated
     */
    public byte[] getLocation() {
        return location;
    }

    /**
     * This method was generated by MyBatis Generator.
     * This method sets the value of the database column landmark.location
     *
     * @param location the value for landmark.location
     *
     * @mbg.generated
     */
    public void setLocation(byte[] location) {
        this.location = location;
    }
}