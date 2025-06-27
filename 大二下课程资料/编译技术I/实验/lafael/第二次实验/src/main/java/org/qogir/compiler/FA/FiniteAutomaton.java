package org.qogir.compiler.FA;

import org.qogir.compiler.util.graph.BreadthFirstIterator;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author xuyang
 */

public class FiniteAutomaton implements Serializable {
    @Serial
    private static final long serialVersionUID = -8476282864782304740L;

    protected ArrayList<Character> alphabet = new ArrayList<>();

    protected LabeledDirectedGraph<State> transitTable = new LabeledDirectedGraph<>();

    protected State startState;

    public FiniteAutomaton(){
        this.startState = new State(0);
        this.transitTable.addVertex(this.startState);
    }

    public FiniteAutomaton(int flag){
        if(flag != -1){
            this.startState = new State(0);
            this.transitTable.addVertex(this.startState);
        }
    }

    public void setAlphabet(ArrayList<Character> alphabet) {
        this.alphabet = alphabet;
    }

    public ArrayList<Character> getAlphabet() {
        return alphabet;
    }

    public State getStartState() {
        return startState;
    }

    public void setStartState(State startState) {
        this.startState = startState;
    }

    public LabeledDirectedGraph<State> getTransitTable(){
        return this.transitTable;
    }

    @Override
    public String toString() {
        StringBuilder faInfo = new StringBuilder();
        int num = transitTable.edgeSet().size();
        faInfo.append("Alphabet:").append(this.alphabet.toString()).append("\n").append("Total edges:").append(num).append("\n").append("Start State:").append(this.startState.getId()).append("\n").append("the transitTable is: \n");
        for (LabelEdge edge : transitTable.edgeSet()){
            faInfo.append("(").append(edge.toString()).append(")\n") ;
        }
        return faInfo.toString();
    }

    public void renumberSID(){
        int i = 0;
        ArrayDeque<State> queue = new ArrayDeque<>();
        BreadthFirstIterator<State> bfi = new BreadthFirstIterator<>(this.transitTable, this.startState);
        while (bfi.hasNext()) {
            bfi.next().setSid(String.valueOf(i));
            i++;
        }
    }

    /**
     * format: {"start":0,"edges":[{"source":{"id":0,"type":0},"target":{"id":1,"type":1},"label":"a"},{...}]}
     * @param filename  the name of exported file.
     */
    public void exportJson(String filename){}

/*    public void showFA(){
        String stateInfo = "Start State:" + this.startState.getId() ;
        System.out.println(stateInfo);
        System.out.println("the transitTable is: \r");
        String edgeInfo;
        for (LabelEdge edge : transitTable.edgeSet()){
            edgeInfo = "(" + edge.toString() + ")\r" ;//this.transitTable.getEdgeSource(edge).getId() + ":" + this.transitTable.getEdgeSource(edge).getType() + "->" + this.transitTable.getEdgeTarget(edge).getId() + ":" + this.transitTable.getEdgeTarget(edge).getType() + " @ " + edge.getLabel() + ")\r";
            System.out.println(edgeInfo);
        }
    }*/

/*    public void exportJson(String filename){

        ArrayDeque<String> edgeInfoQueue = new ArrayDeque<>();
        for (RelationshipEdge e : transitTable.edgeSet()){
            String thisEdgeInfo = "{\"source\":{\"id\":" + this.transitTable.getEdgeSource(e).getId() + ",\"type\":" + this.transitTable.getEdgeSource(e).getType() + "},\"target\":{\"id\":" + this.transitTable.getEdgeTarget(e).getId() + ",\"type\":" + this.transitTable.getEdgeTarget(e).getType() + "},\"label\":\"" + e.getLabel() + "\"}";
            edgeInfoQueue.add(thisEdgeInfo);
        }

        String thatEdgeInfo = edgeInfoQueue.poll();
        String FAJson = "{\"start\":" + this.startState.getId() + ",\"edges\":[" + thatEdgeInfo;
        while(!edgeInfoQueue.isEmpty()){
            thatEdgeInfo = edgeInfoQueue.poll();
            FAJson += "," + thatEdgeInfo;
        }
        FAJson += "]}";

        System.out.println(FAJson);

        String file = filename +".json";
        try {
            Writer write = new OutputStreamWriter(new FileOutputStream(new File(file)), "UTF-8");
            write.write(FAJson);
            write.flush();
            write.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }*/
}
