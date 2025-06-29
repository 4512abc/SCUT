package org.example.mapper;

import org.example.model.entity.ChallengeTagKey;

public interface ChallengeTagMapper {

    int deleteByPrimaryKey(ChallengeTagKey key);

    int insert(ChallengeTagKey row);

    int insertSelective(ChallengeTagKey row);
}