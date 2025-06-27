package org.qogir.compiler.util.graph;

import java.io.Serial;
import java.io.Serializable;

public class LabelEdge implements Serializable {

    @Serial
    private static final long serialVersionUID = 7048748617452671098L;

    private Object source;
    private Object target;
    private Character label;

    public LabelEdge(Object source, Object target, Character label) {
        this.source = source;
        this.target = target;
        this.label = label;
    }

    public Object getSource(){
        return this.source;
    }

    public boolean setSource(Object obj){
        if(obj == null)
            return false;
        if(obj.getClass() != source.getClass())
            return false;
        this.source = obj;
        return true;
    }

    public Object getTarget(){
        return this.target;
    }

    public boolean setTarget(Object obj){
        if(obj == null)
            return false;
        if(obj.getClass() != target.getClass())
            return false;
        this.target = obj;
        return true;
    }

    public Character getLabel(){
        return this.label;
    }

    public boolean setLabel(Character l){
        this.label = l;
        return true;
    }

    @Override
    public int hashCode(){
        int result = 1;
        final int prime = 31;
        result = prime + result + ((this.source == null) ? 0 : this.source.hashCode());
        result = prime + result + ((this.target == null) ? 0 : this.target.hashCode());
        result = prime + result + ((this.label == null) ? 0 : this.label.hashCode());
        return result;
    }

    public boolean equals(Object obj){
        if(obj == null)
            return false;
        if(this == obj)
            return true;
        if(obj.getClass() != this.getClass())
            return false;
        if(!((LabelEdge)obj).getSource().equals(this.source))
            return false;
        if(!((LabelEdge)obj).getTarget().equals(this.target))
            return false;
        else return (((LabelEdge)obj).getLabel().equals(this.label));
    }

    @Override
    public String toString() {
        return this.source.toString() + "->" + this.target.toString() + "@" + this.label;
    }
}
