package org.qogir.simulation.scanner;

import java.util.HashSet;
import java.util.Set;

public class Tag {
    public static Set<String> tags = new HashSet<>();

    public Tag(){
    }

    public Set<String> getTags() {
        return tags;
    }

    public void setTags(Set<String> tags) {
        this.tags = tags;
    }

    public void addTag(String tag){
        tags.add(tag);
    }
}
