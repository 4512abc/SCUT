package org.example.mapper;

import org.example.model.entity.FaceEncoding;

public interface FaceEncodingMapper {

    int deleteByPrimaryKey(Long id);

    int insert(FaceEncoding row);

    int insertSelective(FaceEncoding row);

    FaceEncoding selectByPrimaryKey(Long id);

    int updateByPrimaryKeySelective(FaceEncoding row);

    int updateByPrimaryKeyWithBLOBs(FaceEncoding row);

    int updateByPrimaryKey(FaceEncoding row);
}