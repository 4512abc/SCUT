package org.example.mapper;

import org.example.model.entity.Forward;

public interface ForwardMapper {
    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table forward
     *
     * @mbg.generated
     */
    int deleteByPrimaryKey(Long id);

    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table forward
     *
     * @mbg.generated
     */
    int insert(Forward row);

    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table forward
     *
     * @mbg.generated
     */
    int insertSelective(Forward row);

    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table forward
     *
     * @mbg.generated
     */
    Forward selectByPrimaryKey(Long id);

    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table forward
     *
     * @mbg.generated
     */
    int updateByPrimaryKeySelective(Forward row);

    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table forward
     *
     * @mbg.generated
     */
    int updateByPrimaryKeyWithBLOBs(Forward row);

    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table forward
     *
     * @mbg.generated
     */
    int updateByPrimaryKey(Forward row);
}