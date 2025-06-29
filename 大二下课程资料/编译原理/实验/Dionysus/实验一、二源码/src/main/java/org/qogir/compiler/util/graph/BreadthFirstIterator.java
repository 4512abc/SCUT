package org.qogir.compiler.util.graph;

import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.Iterator;

/**
 * BreadthFirstIterator 类实现了 Iterator 接口，用于对带标签的有向图进行广度优先遍历。
 * 该类从指定的起始顶点开始，按照广度优先搜索（BFS）的顺序迭代图中的顶点。
 *
 * @param <V> 图中顶点的类型
 */
public class BreadthFirstIterator<V> implements Iterator<V> {

    // 用于存储待迭代的顶点队列
    private ArrayDeque<V> queue = new ArrayDeque<>();

    // 要遍历的带标签的有向图
    private LabeledDirectedGraph<V> graph;
    // 广度优先遍历的起始顶点
    private V startVertex;

    /**
     * 构造函数，初始化广度优先迭代器。
     * 传入要遍历的图和起始顶点，并调用 breadthFirstTraverse 方法进行图的遍历。
     *
     * @param g 要遍历的带标签的有向图
     * @param startVertex 广度优先遍历的起始顶点
     */
    public BreadthFirstIterator(LabeledDirectedGraph<V> g, V startVertex){
        this.graph = g;
        this.startVertex = startVertex;
        // 执行广度优先遍历
        breadthFirstTraverse();
    }

    /**
     * 执行广度优先遍历，将遍历到的顶点按顺序添加到 queue 中。
     * 若起始顶点为 null，则直接返回。
     */
    private void breadthFirstTraverse(){
        // 若起始顶点为 null，不进行遍历
        if(this.startVertex == null)
            return;

        // 用于记录每个顶点是否被访问过，0 表示未访问，1 表示已访问
        HashMap<V,Integer> visited = new HashMap<>();

        // 初始化所有顶点的访问状态为未访问
        for(V v : graph.vertexSet()){
            visited.put(v,0);
        }
        // 用于辅助遍历的队列
        ArrayDeque<V> traverseQueue = new ArrayDeque<>();

        // 将起始顶点加入辅助队列
        traverseQueue.add(this.startVertex);
        V temp;

        // 当辅助队列不为空时，继续遍历
        while(!traverseQueue.isEmpty()){
            // 从辅助队列中取出一个顶点
            temp = traverseQueue.poll();
            // 若该顶点未被访问过
            if(visited.get(temp) == 0){
                // 标记该顶点为已访问
                visited.put(temp,1);
                // 将该顶点加入待迭代的队列
                queue.add(temp);

                // 遍历图中的所有边
                for(LabelEdge le : graph.edgeSet()){
                    // 若当前边的源顶点等于当前顶点
                    if(le.getSource().equals(temp)){
                        // 若当前边的目标顶点未被访问过
                        if(visited.get(le.getTarget()) == 0){
                            // 将目标顶点加入辅助队列
                            traverseQueue.add((V)le.getTarget());
                        }
                    }
                }
            }
        }
    }

    /**
     * 判断迭代器中是否还有下一个元素。
     *
     * @return 若队列不为空，返回 true；否则返回 false
     */
    @Override
    public boolean hasNext() {
        // 若队列为空，返回 false
        if(queue.isEmpty())
            return false;
        return true;
    }

    /**
     * 返回迭代器中的下一个元素，并将其从队列中移除。
     * 若没有下一个元素，则返回 null。
     *
     * @return 迭代器中的下一个元素，若没有则返回 null
     */
    @Override
    public V next() {
        // 若没有下一个元素，返回 null
        if(!hasNext())
            return null;
        // 从队列中取出并返回下一个元素
        return queue.poll();
    }
}