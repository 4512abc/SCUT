package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;

public class SubsetConstruction {

    /**
     * 通过 ε 闭包操作，找出 NFA 中从单个状态出发，通过 ε 转移可达的所有状态。
     */
    private HashMap<Integer, State> epsilonClosures(State s, LabeledDirectedGraph<State> tb) {
        if (!tb.vertexSet().contains(s)) {
            return null;
        }

        HashMap<Integer, State> nfaStates = new HashMap<>();
        ArrayDeque<State> queue = new ArrayDeque<>();
        queue.add(s);

        while (!queue.isEmpty()) {
            State state = queue.poll();
            nfaStates.putIfAbsent(state.getId(), state);

            // 遍历所有从当前状态出发的ε转移
            for (LabelEdge e : tb.edgeSet()) {
                if (tb.getEdgeSource(e).equals(state) && e.getLabel() == 'ε'
                        && !nfaStates.containsKey(tb.getEdgeTarget(e).getId())) {
                    queue.push(tb.getEdgeTarget(e));
                }
            }
        }
        return nfaStates;
    }

    /**
     * 通过 ε 闭包操作，找出 NFA 中从一个状态集合出发，通过 ε 转移可达的所有状态。
     */
    public HashMap<Integer, State> epsilonClosure(HashMap<Integer, State> ss, LabeledDirectedGraph<State> tb) {
        HashMap<Integer, State> nfaStates = new HashMap<>();
        for (State s : ss.values()) {
            nfaStates.putAll(epsilonClosures(s, tb));
        }
        return nfaStates;
    }

    /**
     * 找出 NFA 中从单个状态出发，在输入字符 ch 的作用下可达的所有状态。
     */
    private HashMap<Integer, State> moves(State s, Character ch, LabeledDirectedGraph<State> tb) {
        HashMap<Integer, State> nfaStates = new HashMap<>();

        // 遍历所有从当前状态出发的转移
        for (LabelEdge e : tb.edgeSet()) {
            if (tb.getEdgeSource(e).equals(s) && e.getLabel().equals(ch)) {
                nfaStates.put(tb.getEdgeTarget(e).getId(), tb.getEdgeTarget(e));
            }
        }
        return nfaStates;
    }

    /**
     * 找出 NFA 中从一个状态集合出发，在输入字符 ch 的作用下可达的所有状态。
     */
    public HashMap<Integer, State> move(HashMap<Integer, State> ss, Character ch, LabeledDirectedGraph<State> tb) {
        HashMap<Integer, State> nfaStates = new HashMap<>();
        for (State s : ss.values()) {
            nfaStates.putAll(moves(s, ch, tb));
        }
        return nfaStates;
    }

    /**
     * 先转移再ε闭包操作
     */
    public HashMap<Integer, State> epsilonClosureWithMove(HashMap<Integer, State> sSet, Character ch,
                                                          LabeledDirectedGraph<State> tb) {
        HashMap<Integer, State> states = new HashMap<>();
        states.putAll(epsilonClosure(move(sSet, ch, tb), tb));
        return states;
    }

    /**
     * 使用子集构造算法将NFA转换为DFA
     */
    public RDFA subSetConstruct(TNFA tnfa) {
        ArrayList<Character> symbols = tnfa.getAlphabet();
        LabeledDirectedGraph<State> tb = tnfa.getTransitTable();
        State tnfaStartState = tnfa.getStartState();
        State tnfaAcceptState = tnfa.getAcceptingState();

        // DFA的起始状态是NFA起始状态的ε闭包
        HashMap<Integer, State> dFAStartStates = new HashMap<>();
        dFAStartStates.put(tnfaStartState.getId(), tnfaStartState);
        dFAStartStates = epsilonClosure(dFAStartStates, tb);

        // 检查起始状态的ε闭包中是否包含接受状态
        for (State s : dFAStartStates.values()) {
            if (s.getType() == State.ACCEPT) {
                tnfaStartState.setType(State.ACCEPTANDSTART);
                break;
            }
        }

        // 创建DFA
        RDFA dfa = new RDFA(tnfaStartState);
        dfa.getStateMappingBetweenDFAAndNFA().put(tnfaStartState, dFAStartStates);

        ArrayDeque<State> queue = new ArrayDeque<>();
        queue.add(tnfaStartState);
        dfa.setAlphabet(symbols);

        while (!queue.isEmpty()) {
            State sourceDfaState = queue.poll();

            // 对每个输入符号进行处理
            for (Character ch : symbols) {
                HashMap<Integer, State> targetNfaStateSet =
                        epsilonClosureWithMove(dfa.getStateMappingBetweenDFAAndNFA().get(sourceDfaState), ch, tb);

                if (targetNfaStateSet.isEmpty()) continue;

                // 检查该NFA状态集合是否已存在于DFA中
                boolean exists = false;
                for (State s : dfa.getStateMappingBetweenDFAAndNFA().keySet()) {
                    if (dfa.getStateMappingBetweenDFAAndNFA().get(s).equals(targetNfaStateSet)) {
                        // 已存在，直接添加转移
                        dfa.getTransitTable().addEdge(
                                new LabelEdge(sourceDfaState, s, ch));
                        exists = true;
                        break;
                    }
                }

                // 不存在则创建新状态
                if (!exists) {
                    State targetDfaState = new State();
                    queue.add(targetDfaState);

                    // 设置状态类型
                    if (targetNfaStateSet.containsValue(tnfaAcceptState)) {
                        targetDfaState.setType(State.ACCEPT);
                    } else {
                        targetDfaState.setType(State.MIDDLE);
                    }

                    // 添加状态映射
                    dfa.setStateMappingBetweenDFAAndNFA(targetDfaState, targetNfaStateSet);

                    // 添加状态和转移
                    dfa.getTransitTable().addVertex(targetDfaState);
                    dfa.getTransitTable().addEdge(
                            new LabelEdge(sourceDfaState, targetDfaState, ch));
                }
            }
        }

        return dfa;
    }
}