package org.qogir.compiler.util.graph;

import java.io.Serial;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

public class LabeledDirectedGraph<V> implements Serializable {
    @Serial
    private static final long serialVersionUID = -554762429816584355L;

    Set<V> vertexSet;
    Set<LabelEdge> edgeSet;

    public LabeledDirectedGraph(){
        this.vertexSet = new HashSet<>();
        this.edgeSet = new HashSet<>();
    }

    public Set<V> vertexSet(){
        return this.vertexSet;
    }

    public Set<LabelEdge> edgeSet() {
        return edgeSet;
    }

    public boolean containsVertex(V v){
        for(V vertex : vertexSet){
            if(v.equals(vertex))
                return true;
        }
        return false;
    }

    public boolean containsEdge(LabelEdge e){
        for(LabelEdge edge : edgeSet){
            if(e.equals(edge))
                return true;
        }
        return false;
    }

    public boolean containsEdge(V source, V target, Character label){
        for(LabelEdge edge : edgeSet){
            if(edge.getSource().equals(source)&&edge.getTarget().equals(target)&&edge.getLabel().equals(label))
                return true;
        }
        return false;
    }

    public boolean addVertex(V v){
        if(v == null)
            return false;
        if(!containsVertex(v)) {
            vertexSet.add(v);
            return true;
        }
        return false;
    }

    public boolean addEdge(LabelEdge le){
        if(le == null)
            return false;
        if(!containsEdge(le)) {
            return edgeSet.add(le);
        }
        return false;
    }

    public boolean addEdge(V source, V target, Character label){
        if(source == null || target == null)
            return false;
        if(!containsEdge(source, target, label)){
            LabelEdge le = new LabelEdge(source, target, label);
            return addEdge(le);
        }
        return false;
    }

    public V getEdgeTarget(LabelEdge le){
        return (V)le.getTarget();
    }

    public V getEdgeSource(LabelEdge le){
        return (V) le.getSource();
    }

    public Character getEdgeLabel(LabelEdge le){
        return le.getLabel();
    }
    @Override
    public String toString() {
        StringBuilder graphInfo = new StringBuilder();
        int num = edgeSet().size();
        graphInfo.append("Total edges:").append(num).append("\n");
        for(LabelEdge le : edgeSet()){
            graphInfo.append(le.toString()).append("\n");
        }

        return graphInfo.toString();
    }

    public boolean merge(LabeledDirectedGraph graph){
        if(graph == null)
            return false;
        if(!vertexSet.addAll(graph.vertexSet())){
            return false;
        }
        return (edgeSet.addAll(graph.edgeSet()));
    }
}
