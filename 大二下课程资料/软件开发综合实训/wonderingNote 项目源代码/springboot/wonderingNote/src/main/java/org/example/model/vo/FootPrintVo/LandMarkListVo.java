package org.example.model.vo.FootPrintVo;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;
import org.example.model.utils.Location;

import java.util.List;

@Data
public class LandMarkListVo {
    private List<LandMark> data;

    @Data
    public static class LandMark {
        @JsonProperty("landmark_name")
        private String landmarkName;
        @JsonProperty("location")
        private Location location;
    }
}

