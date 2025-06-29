package org.example.model.query.PostQuery;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Data;

@Data
public class PostCreateQuery {
    private String title;
    private String content;
    private String images;
    private String videos;
    private Double[] location;
    @JsonProperty("is_public")
    private Boolean isPublic;
    @JsonProperty("landmark_name")
    private String landmarkName;

}