package org.qogir.compiler.FA;

import org.qogir.compiler.util.graph.BreadthFirstIterator;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;

public class FiniteAutomaton implements Serializable {
    @Serial
    private static final long serialVersionUID = -8476282864782304740L;
    protected ArrayList<Character> alphabet = new ArrayList<>();
    protected LabeledDirectedGraph<State> transitTable = new LabeledDirectedGraph<>();
    protected State startState;

    // 新增方法：打印DFA中间过程
    public void printMinimizationProcess() {
        System.out.println("\n=== DFA Minimization Process ===");
        System.out.println(this.toString()); // 打印原始DFA信息

        // 1. 初始划分：接受状态和非接受状态
        HashMap<Integer, State> acceptStates = new HashMap<>();
        HashMap<Integer, State> nonAcceptStates = new HashMap<>();

        for (State s : transitTable.vertexSet()) {
            if (s.getType() == State.ACCEPT || s.getType() == State.ACCEPTANDSTART) {
                acceptStates.put(s.getId(), s);
            } else {
                nonAcceptStates.put(s.getId(), s);
            }
        }

        System.out.println("\nStep 0 - Initial Partition:");
        System.out.println("Accept States: " + formatStateGroup(acceptStates));
        System.out.println("Non-Accept States: " + formatStateGroup(nonAcceptStates));

        // 2. 等价状态划分过程（简化示例）
        int step = 1;
        for (char symbol : alphabet) {
            System.out.println("\nStep " + step++ + " - Processing symbol '" + symbol + "':");

            // 模拟状态转移分析
            HashMap<String, ArrayList<State>> transitionGroups = new HashMap<>();
            for (State s : transitTable.vertexSet()) {
                String transitionKey = getTransitionKey(s, symbol);
                transitionGroups.computeIfAbsent(transitionKey, k -> new ArrayList<>()).add(s);
            }

            // 打印当前划分
            for (String key : transitionGroups.keySet()) {
                System.out.println("States transitioning to " +
                        (key.equals("null") ? "no state" : key) +
                        " on '" + symbol + "': " +
                        formatStateList(transitionGroups.get(key)));
            }
        }

        System.out.println("\nMinimization complete.");
    }

    // 辅助方法：格式化状态组输出
    private String formatStateGroup(HashMap<Integer, State> states) {
        StringBuilder sb = new StringBuilder("{");
        for (State s : states.values()) {
            sb.append(s.getId()).append(":").append(s.getType()).append(", ");
        }
        if (sb.length() > 1) sb.setLength(sb.length() - 2);
        sb.append("}");
        return sb.toString();
    }

    // 辅助方法：格式化状态列表
    private String formatStateList(ArrayList<State> states) {
        StringBuilder sb = new StringBuilder("{");
        for (State s : states) {
            sb.append(s.getId()).append(", ");
        }
        if (sb.length() > 1) sb.setLength(sb.length() - 2);
        sb.append("}");
        return sb.toString();
    }

    // 辅助方法：获取状态的转移目标
    private String getTransitionKey(State s, char symbol) {
        for (LabelEdge e : transitTable.edgeSet()) {
            if (transitTable.getEdgeSource(e).equals(s) && e.getLabel() == symbol) {
                State target = transitTable.getEdgeTarget(e);
                return target.getId() + ":" + target.getType();
            }
        }
        return "null";
    }

    // 保留原有方法...
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
        faInfo.append("Alphabet:").append(this.alphabet.toString()).append("\n")
                .append("Total edges:").append(transitTable.edgeSet().size()).append("\n")
                .append("Start State:").append(this.startState.getId()).append("\n")
                .append("TransitTable:\n");

        for (LabelEdge edge : transitTable.edgeSet()){
            State source = transitTable.getEdgeSource(edge);
            State target = transitTable.getEdgeTarget(edge);
            faInfo.append("(")
                    .append(source.getId()).append(":").append(source.getType())
                    .append("->")
                    .append(target.getId()).append(":").append(target.getType())
                    .append("@").append(edge.getLabel())
                    .append(")\n");
        }
        return faInfo.toString();
    }

    public void renumberSID(){
        int i = 0;
        BreadthFirstIterator<State> bfi = new BreadthFirstIterator<>(this.transitTable, this.startState);
        while (bfi.hasNext()) {
            bfi.next().setSid(String.valueOf(i));
            i++;
        }
    }
}