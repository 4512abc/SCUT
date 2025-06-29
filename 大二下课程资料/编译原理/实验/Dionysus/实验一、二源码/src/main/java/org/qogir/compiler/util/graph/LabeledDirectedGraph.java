package org.qogir.compiler.util.graph;

import java.io.Serial;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/**
 * LabeledDirectedGraph 类表示一个带标签的有向图，实现了 Serializable 接口，可进行序列化操作。
 * 该类包含顶点集合和边集合，并提供了一系列操作图的方法，如添加顶点、添加边、判断元素是否存在等。
 *
 * @param <V> 图中顶点的类型
 */
public class LabeledDirectedGraph<V> implements Serializable {
    // 序列化版本号，确保序列化和反序列化过程中类的版本一致性
    @Serial
    private static final long serialVersionUID = -554762429816584355L;

    // 图的顶点集合
    Set<V> vertexSet;
    // 图的边集合，边使用 LabelEdge 表示
    Set<LabelEdge> edgeSet;

    /**
     * 构造函数，初始化一个空的带标签的有向图。
     * 使用 HashSet 存储顶点和边集合。
     */
    public LabeledDirectedGraph(){
        this.vertexSet = new HashSet<>();
        this.edgeSet = new HashSet<>();
    }

    /**
     * 获取图的顶点集合。
     *
     * @return 图的顶点集合
     */
    public Set<V> vertexSet(){
        return this.vertexSet;
    }

    /**
     * 获取图的边集合。
     *
     * @return 图的边集合
     */
    public Set<LabelEdge> edgeSet() {
        return edgeSet;
    }

    /**
     * 判断图中是否包含指定的顶点。
     *
     * @param v 要判断的顶点
     * @return 若图中包含该顶点，返回 true；否则返回 false
     */
    public boolean containsVertex(V v){
        // 遍历顶点集合，检查是否存在相等的顶点
        for(V vertex : vertexSet){
            if(v.equals(vertex))
                return true;
        }
        return false;
    }

    /**
     * 判断图中是否包含指定的边。
     *
     * @param e 要判断的边
     * @return 若图中包含该边，返回 true；否则返回 false
     */
    public boolean containsEdge(LabelEdge e){
        // 遍历边集合，检查是否存在相等的边
        for(LabelEdge edge : edgeSet){
            if(e.equals(edge))
                return true;
        }
        return false;
    }

    /**
     * 判断图中是否包含指定源顶点、目标顶点和标签的边。
     *
     * @param source 边的源顶点
     * @param target 边的目标顶点
     * @param label 边的标签
     * @return 若图中包含该边，返回 true；否则返回 false
     */
    public boolean containsEdge(V source, V target, Character label){
        // 遍历边集合，检查是否存在符合条件的边
        for(LabelEdge edge : edgeSet){
            if(edge.getSource().equals(source)&&edge.getTarget().equals(target)&&edge.getLabel().equals(label))
                return true;
        }
        return false;
    }

    /**
     * 向图中添加一个顶点。
     * 若顶点为 null 或图中已存在该顶点，则添加失败。
     *
     * @param v 要添加的顶点
     * @return 若添加成功，返回 true；否则返回 false
     */
    public boolean addVertex(V v){
        // 若顶点为 null，添加失败
        if(v == null)
            return false;
        // 若图中不包含该顶点，将其添加到顶点集合中
        if(!containsVertex(v)) {
            vertexSet.add(v);
            return true;
        }
        return false;
    }

    /**
     * 向图中添加一条边。
     * 若边为 null 或图中已存在该边，则添加失败。
     *
     * @param le 要添加的边
     * @return 若添加成功，返回 true；否则返回 false
     */
    public boolean addEdge(LabelEdge le){
        // 若边为 null，添加失败
        if(le == null)
            return false;
        // 若图中不包含该边，将其添加到边集合中
        if(!containsEdge(le)) {
            return edgeSet.add(le);
        }
        return false;
    }

    /**
     * 向图中添加一条指定源顶点、目标顶点和标签的边。
     * 若源顶点或目标顶点为 null，或图中已存在该边，则添加失败。
     *
     * @param source 边的源顶点
     * @param target 边的目标顶点
     * @param label 边的标签
     * @return 若添加成功，返回 true；否则返回 false
     */
    public boolean addEdge(V source, V target, Character label){
        // 若源顶点或目标顶点为 null，添加失败
        if(source == null || target == null)
            return false;
        // 若图中不包含该边，创建新边并添加到图中
        if(!containsEdge(source, target, label)){
            LabelEdge le = new LabelEdge(source, target, label);
            return addEdge(le);
        }
        return false;
    }

    /**
     * 获取指定边的目标顶点。
     *
     * @param le 指定的边
     * @return 边的目标顶点
     */
    public V getEdgeTarget(LabelEdge le){
        return (V)le.getTarget();
    }

    /**
     * 获取指定边的源顶点。
     *
     * @param le 指定的边
     * @return 边的源顶点
     */
    public V getEdgeSource(LabelEdge le){
        return (V) le.getSource();
    }

    /**
     * 获取指定边的标签。
     *
     * @param le 指定的边
     * @return 边的标签
     */
    public Character getEdgeLabel(LabelEdge le){
        return le.getLabel();
    }

    /**
     * 将图的信息转换为字符串表示。
     * 包含边的总数和每条边的详细信息。
     *
     * @return 包含图信息的字符串
     */
    @Override
    public String toString() {
        // 用于构建图信息的字符串
        StringBuilder graphInfo = new StringBuilder();
        // 获取边的总数
        int num = edgeSet().size();
        // 添加边的总数信息
        graphInfo.append("Total edges:").append(num).append("\n");
        // 遍历边集合，添加每条边的信息
        for(LabelEdge le : edgeSet()){
            graphInfo.append(le.toString()).append("\n");
        }

        return graphInfo.toString();
    }

    /**
     * 将另一个带标签的有向图合并到当前图中。
     * 若另一个图为 null，或合并顶点集合失败，则合并失败。
     *
     * @param graph 要合并的另一个带标签的有向图
     * @return 若合并成功，返回 true；否则返回 false
     */
    public boolean merge(LabeledDirectedGraph graph){
        // 若要合并的图为 null，合并失败
        if(graph == null)
            return false;
        // 合并顶点集合，若失败则返回 false
        if(!vertexSet.addAll(graph.vertexSet())){
            return false;
        }
        // 合并边集合并返回结果
        return (edgeSet.addAll(graph.edgeSet()));
    }
}