package org.example.model.vo.HomeVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class HomeMonthDataVo {
    @JsonProperty("month")
    private String month;
    @JsonProperty("post_count")
    private int postCount;
    @JsonProperty("challenge_count")
    private int challengeCount;

    public HomeMonthDataVo(String month, int postCount, int challengeCount) {
        this.month = month;
        this.postCount = postCount;
        this.challengeCount = challengeCount;
    }


}
