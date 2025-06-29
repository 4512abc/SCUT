package org.example.service;

import org.example.exception.CustomException;
import org.example.mapper.AnnouncementMapper;
import org.example.mapper.NotificationMapper;
import org.example.mapper.UserMapper;
import org.example.model.entity.Announcement;
import org.example.model.entity.Notification;
import org.example.model.entity.User;
import org.example.model.query.AnnouncementQuery.AnnouncementCreatQuery;
import org.example.model.query.AnnouncementQuery.AnnouncementModifyQuery;
import org.example.model.vo.AnnouncementVo.AnnouncementCreatVo;
import org.example.model.vo.AnnouncementVo.AnnouncementModifyVo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import lombok.extern.slf4j.Slf4j;

import java.util.Date;
import java.util.List;
import java.util.Objects;

import static org.example.common.result.ResultCode.*;

@Slf4j
@Service
public class AnnouncementService {

    @Autowired
    private AnnouncementMapper announcementMapper;

    @Autowired
    private UserMapper userMapper;

    @Autowired
    private NotificationMapper notificationMapper;

    public AnnouncementCreatVo createAnnouncement(Long userId, AnnouncementCreatQuery query) {
        User user_1= userMapper.selectByPrimaryKey(userId);
        if (Objects.equals(user_1.getAccessLevel(), "user")){
            throw new CustomException(Announcement_CREATE_ERROR);
        }

        if(query.getContent()==null||query.getContent().isEmpty()|| Objects.equals(query.getContent(), "")){
            throw new CustomException(Announcement_CONTENT_ERROR);
        }
        if(query.getTitle()==null||query.getTitle().isEmpty()|| Objects.equals(query.getTitle(), "")){
            throw new CustomException(Announcement_TITLE_ERROR);
        }
        if(query.getType()!=1&&query.getType()!=2){
            throw new CustomException(Anouncement_TYPE_ERROR);
        }
        // 创建公告
        Announcement announcement = new Announcement();
        announcement.setTitle(query.getTitle());
        announcement.setContent(query.getContent());
        announcement.setType(query.getType().byteValue()); // 调用Integer的byteValue()方法
        announcement.setPublisherId(userId);
        announcement.setPushType((byte)1);
        announcement.setCreateTime(new Date());
        announcement.setUpdateTime(new Date());
        announcementMapper.insertSelective(announcement);

        // 根据公告类型发送通知
        List<User> users;
        if (query.getType() == 1) {
            // 后台公告，发送给所有管理员
            users = userMapper.selectAdmins();
        } else {
            // 用户端公告，发送给所有用户
            users = userMapper.selectAllUsers();
        }

        for (User user : users) {
            Notification notification = new Notification();
            notification.setSenderId(userId);
            notification.setReceiverId(user.getId());
            notification.setType((byte) 3); // 3表示系统通知
            notification.setContent("新公告: " + query.getTitle());
            notification.setIsRead(false);
            notification.setCreateTime(announcement.getCreateTime());
            notification.setTypeId(announcement.getId());
            notificationMapper.insertSelective(notification);
        }

        // 返回公告ID
        AnnouncementCreatVo vo = new AnnouncementCreatVo();
        vo.setId(announcement.getId());
        return vo;
    }

    public AnnouncementModifyVo modifyAnnouncement(Long userId,Long announcementId, AnnouncementModifyQuery query) {
        // 更新公告内容

        User user_1= userMapper.selectByPrimaryKey(userId);
        if (Objects.equals(user_1.getAccessLevel(), "user")){
            throw new CustomException(Announcement_CREATE_ERROR);
        }
        Announcement announcement_1 = announcementMapper.selectByPrimaryKey(announcementId);
        if (announcement_1 == null) {
            throw new CustomException(ANNOUNCEMENT_NOT_EXIST_ERROR);
        }

        if(query.getContent()==null||query.getContent().isEmpty()|| Objects.equals(query.getContent(), "")){
            throw new CustomException(Announcement_CONTENT_ERROR);
        }
        if(query.getTitle()==null||query.getTitle().isEmpty()|| Objects.equals(query.getTitle(), "")){
            throw new CustomException(Announcement_TITLE_ERROR);
        }
        Announcement announcement = new Announcement();
        announcement.setId(announcementId);
        announcement.setTitle(query.getTitle());
        announcement.setContent(query.getContent());
        announcement.setUpdateTime(new Date());
        announcementMapper.updateByPrimaryKeySelective(announcement);

        // 更新相关通知的 is_read 状态
        Notification notification = new Notification();
        notification.setIsRead(false);
        notification.setContent("新公告: " + query.getTitle());
        notificationMapper.updateByTypeIdAndType(announcementId, (byte) 3, notification);

        // 返回结果
        AnnouncementModifyVo vo = new AnnouncementModifyVo();
        vo.setId(announcementId);
        return vo;
    }

}
