package org.example.mapper;

import org.example.model.entity.AuditLog;
import org.springframework.stereotype.Repository;

@Repository
public interface AuditLogMapper  {

    int deleteByPrimaryKey(Long id);


    int insert(AuditLog row);


    int insertSelective(AuditLog row);

    AuditLog selectByPrimaryKey(Long id);


    int updateByPrimaryKeySelective(AuditLog row);

    int updateByPrimaryKey(AuditLog row);
}