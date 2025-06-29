package org.example.model.vo.HomeVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

/**
 * 首页数据统计视图对象
 */
@Data
public class HomeDataVo {
    /**
     * 用户总数
     */
    @JsonProperty("user_total")
    private Integer userTotal;
    /**
     * 今天增加的用户数量
     */
    @JsonProperty("user_add")
    private Integer userAdd;

    /**
     * 博文总数
     */
    @JsonProperty("post_total")
    private Integer postTotal;

    /**
     * 今天增加的博文数量
     */
    @JsonProperty("post_add")
    private Integer postAdd;

    /**
     * 挑战总数
     */
    @JsonProperty("challenge_total")
    private Integer challengeTotal;

    /**
     * 今天增加的挑战数量
     */
    @JsonProperty("challenge_add")
    private Integer challengeAdd;
}