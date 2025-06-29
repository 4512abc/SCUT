package org.example.mapper;

import org.example.model.entity.FaceFeatures;

public interface FaceFeaturesMapper {

    int deleteByPrimaryKey(Long id);

    int insert(FaceFeatures row);

    int insertSelective(FaceFeatures row);

    FaceFeatures selectByPrimaryKey(Long id);


    int updateByPrimaryKeySelective(FaceFeatures row);


    int updateByPrimaryKeyWithBLOBs(FaceFeatures row);

    int updateByPrimaryKey(FaceFeatures row);
}