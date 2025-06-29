package org.example.model.vo.SearchInfoVo;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;
import org.example.model.entity.Announcement;

import java.util.Date;

@Data
public class SearchAnnouncementVo {
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date createTime;
    private long id;
    private String publishedAccount;
    private long publishedId;
    private String title;
    private long type;
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")
    private Date updateTime;

    public SearchAnnouncementVo(Announcement announcement,String publishedAccount){
        this.createTime = announcement.getCreateTime();
        this.id = announcement.getId();
        this.publishedAccount = publishedAccount;
        this.publishedId = announcement.getPublisherId();
        this.title = announcement.getTitle();
        this.type = announcement.getType();
        this.updateTime = announcement.getUpdateTime();
    }
}
