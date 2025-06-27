package org.qogir.compiler.util.graph;

import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.Iterator;

public class BreadthFirstIterator<V> implements Iterator<V> {

    private ArrayDeque<V> queue = new ArrayDeque<>();

    private LabeledDirectedGraph<V> graph;
    private V startVertex;

    public BreadthFirstIterator(LabeledDirectedGraph<V> g, V startVertex){
        this.graph = g;
        this.startVertex = startVertex;
        breadthFirstTraverse();
    }

    private void breadthFirstTraverse(){
        if(this.startVertex == null)
            return;

        HashMap<V,Integer> visited = new HashMap<>();

        for(V v : graph.vertexSet()){
            visited.put(v,0);
        }
        ArrayDeque<V> traverseQueue = new ArrayDeque<>();

        traverseQueue.add(this.startVertex);
        V temp;

        while(!traverseQueue.isEmpty()){
            temp = traverseQueue.poll();
            if(visited.get(temp) == 0){
                visited.put(temp,1);
                queue.add(temp);

                for(LabelEdge le : graph.edgeSet()){
                    if(le.getSource().equals(temp)){
                        if(visited.get(le.getTarget()) == 0){
                            traverseQueue.add((V)le.getTarget());
                        }
                    }
                }
            }
        }
    }

    @Override
    public boolean hasNext() {
        if(queue.isEmpty())
            return false;
        return true;
    }

    @Override
    public V next() {
        if(!hasNext())
            return null;
        return queue.poll();
    }
}
