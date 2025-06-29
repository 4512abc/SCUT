package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.model.entity.User;
import org.example.model.vo.SearchInfoVo.SearchUserVo;
import org.springframework.stereotype.Repository;

import java.util.Date;
import java.util.List;
import java.util.Map;

@Repository
public interface UserMapper {
    // 基础CRUD方法（必须与XML中的SQL对应）
    int deleteByPrimaryKey(Long id);
    int insert(User user);
    int insertSelective(User user);
    User selectByPrimaryKey(Long id);
    int updateByPrimaryKeySelective(User user);
    int updateByPrimaryKey(User user);

    //由TOTORO编辑
    List<User> selectByIds(@Param("ids") List<Long> ids);
    //
    User selectByAccount(@Param("account") String account); // 通过用户名查找
    User selectByEmail(String email);
    String selectAccountById(@Param("id") Long userId);
    User selectByWxOpenid(@Param("openid") String openid);

//由TOTORO编辑
    Map<Long, String> selectAccountsByIds(@Param("ids") List<Long> ids); // 将 Set<Long> 改为 List<Long>
//如此！
    // 新增方法
    int selectUserTotal();
    int selectUserAddToday(@Param("date") Date date);

    int updateUserState(@Param("id") Long id, @Param("status") String status);
    List<User> selectAdmins();
    List<User> selectAllUsers();
    /**
     * 按条件检索用户
     * @param accessLevel 访问级别（可选）
     * @param account 用户名（模糊匹配，可选）
     * @param status 用户状态（可选）
     * @param email 邮箱（模糊匹配，可选）
     * @param startTime 创建时间起始时间（可选）
     * @param endTime 创建时间结束时间（可选）
     * @return 符合条件的用户列表
     */
    List<User> selectByConditions(
            @Param("accessLevel") String accessLevel,
            @Param("account") String account,
            @Param("status") String status,
            @Param("email") String email,
            @Param("startTime") java.util.Date startTime,
            @Param("endTime") java.util.Date endTime
    );

}