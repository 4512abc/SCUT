package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class StateMinimization {

    /**
     * 区分DFA中等价状态的核心算法
     * 使用表格填充法(table-filling algorithm)或等价类划分法(partition refinement)
     *
     * @param dfa 需要最小化的原始DFA
     * @return 包含等价状态分组的HashMap结构:
     *         外层HashMap的key是分组编号，value是该分组的状态集合
     *         内层HashMap的key是状态ID，value是状态对象
     */
    private HashMap<Integer, HashMap<Integer, State>> distinguishEquivalentState(RDFA dfa) {
        LabeledDirectedGraph<State> tb = dfa.getTransitTable();
        ArrayList<Character> symbols = dfa.getAlphabet();

        // 1. 初始划分: 将接受状态和非接受状态分开
        HashMap<Integer, State> acceptGroup = new HashMap<>();
        HashMap<Integer, State> nonAcceptGroup = new HashMap<>();
        for (State s : tb.vertexSet()) {
            if (s.getType() == State.ACCEPT || s.getType() == State.ACCEPTANDSTART)
                acceptGroup.put(s.getId(), s);
            else
                nonAcceptGroup.put(s.getId(), s);
        }

        HashMap<Integer, HashMap<Integer, State>> groupSet = new HashMap<>();
        groupSet.put(0, acceptGroup);
        if (!nonAcceptGroup.isEmpty()) {
            groupSet.put(1, nonAcceptGroup);
        }

        // 添加初始步骤输出
        System.out.println("GroupSet.size:" + groupSet.size());
        System.out.println("Step0: " + GroupSetToString(groupSet) + " :initial split");

        HashMap<Integer, HashMap<Integer, State>> newGroupSet = new HashMap<>();
        int lastNum = 0;
        int stepCount = 1;

        // 2. 迭代细分: 对每个分组，检查它们在相同输入下的转移是否仍在同一分组
        for (Character ch : symbols) {
            newGroupSet.clear();

            while (newGroupSet.size() != groupSet.size()) {
                if (newGroupSet.size() != 0) newGroupSet.clear();
                newGroupSet.putAll(groupSet);
                groupSet.clear();
                lastNum = 0;

                for (HashMap<Integer, State> group : newGroupSet.values()) {
                    // 记录每个状态在输入ch下的转移目标所在的分组
                    HashMap<State, Integer> split = new HashMap<>();
                    for (State s : group.values()) {
                        split.put(s, -1);
                    }

                    // 检查每个状态在输入ch下的转移目标所在的分组
                    for (State s : group.values()) {
                        boolean found = false;
                        for (LabelEdge e : tb.edgeSet()) {
                            if (tb.getEdgeSource(e).equals(s) && e.getLabel().equals(ch)) {
                                State target = tb.getEdgeTarget(e);
                                for (Map.Entry<Integer, HashMap<Integer, State>> entry : newGroupSet.entrySet()) {
                                    if (entry.getValue().containsKey(target.getId())) {
                                        split.put(s, entry.getKey());
                                        found = true;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        if (!found) {
                            split.put(s, -1);
                        }
                    }

                    // 根据转移目标分组重新划分状态
                    HashMap<Integer, HashMap<Integer, State>> tempGroupSet = new HashMap<>();
                    for (Integer g : split.values()) {
                        tempGroupSet.put(g, new HashMap<>());
                    }
                    for (State s : split.keySet()) {
                        tempGroupSet.get(split.get(s)).put(s.getId(), s);
                    }

                    // 将新的分组添加到groupSet中
                    for (int i = 0; i < tempGroupSet.size(); i++) {
                        groupSet.put(i + lastNum, new HashMap<Integer, State>());
                    }

                    int j = 0;
                    for (HashMap<Integer, State> h : tempGroupSet.values()) {
                        groupSet.put(j + lastNum, h);
                        j++;
                    }
                    lastNum = groupSet.size();
                }

                // 添加步骤输出
                System.out.println("Step" + stepCount + ": " + GroupSetToString(groupSet) + " :end of_" + ch);
                stepCount++;
            }
        }

        return groupSet;
    }

    /**
     * DFA最小化主方法
     * 通过合并等价状态来减少DFA的状态数量
     *
     * @param dfa 需要最小化的原始DFA
     * @return 最小化后的DFA
     */
    public RDFA minimize(RDFA dfa) {
        if (dfa == null)
            return null;

        // 1. 调用distinguishEquivalentState区分等价状态
        HashMap<Integer, HashMap<Integer, State>> newGroupSet = distinguishEquivalentState(dfa);

        if (newGroupSet == null)
            return null;

        LabeledDirectedGraph<State> tb = dfa.getTransitTable();

        // 2. 为每个等价类创建新状态
        RDFA minDFA = new RDFA(dfa.getStartState());
        HashMap<State, Integer> dfaStateToGroup = new HashMap<>();
        HashMap<Integer, State> GroupToDfaState = new HashMap<>();
        ArrayDeque<State> queue = new ArrayDeque<>();

        // 选择每个分组的代表状态
        for (Integer k : newGroupSet.keySet()) {
            State s;
            if (newGroupSet.get(k).containsValue(dfa.getStartState())) {
                s = dfa.getStartState();
            } else {
                s = (State) newGroupSet.get(k).values().toArray()[0];
            }
            dfaStateToGroup.put(s, k);
            GroupToDfaState.put(k, s);
            queue.add(s);
        }

        // 3. 重新构建转移关系
        while (!queue.isEmpty()) {
            State s = queue.poll();

            minDFA.getTransitTable().addVertex(s);

            for (State ss : newGroupSet.get(dfaStateToGroup.get(s)).values()) {
                for (LabelEdge e : tb.edgeSet()) {
                    if (tb.getEdgeSource(e) == ss) {
                        State ts = tb.getEdgeTarget(e);
                        for (Integer k : newGroupSet.keySet()) {
                            if (newGroupSet.get(k).containsValue(ts) != false) {
                                minDFA.getTransitTable().addVertex(GroupToDfaState.get(k));
                                minDFA.getTransitTable().addEdge(new LabelEdge(s, GroupToDfaState.get(k), e.getLabel()));
                                break;
                            }
                        }
                    }
                }
            }
        }

        // 4. 设置新的起始状态和接受状态
        // (已在RDFA构造函数中处理起始状态，接受状态在分组时已保留)

        return minDFA;
    }

    /**
     * 将等价状态分组转换为字符串表示(用于调试和显示)
     *
     * @param GroupSet 等价状态分组集合
     * @return 格式化的字符串表示，如"1:{1:ORDINARY,2:ORDINARY} 2:{3:ACCEPT}"
     */
    private String GroupSetToString(HashMap<Integer, HashMap<Integer, State>> GroupSet) {
        StringBuilder str = new StringBuilder();
        for (Integer g : GroupSet.keySet()) {
            String tmp = GroupToString(GroupSet.get(g));
            str.append(g).append(":").append(tmp).append(" ");
        }
        return str.toString().trim();
    }

    /**
     * 将单个等价状态组转换为字符串表示
     *
     * @param group 单个状态分组
     * @return 格式化的字符串表示，如"{1:ORDINARY,2:ORDINARY}"
     */
    private String GroupToString(HashMap<Integer, State> group) {
        StringBuilder str = new StringBuilder();
        for (Integer k : group.keySet()) {
            str.append(group.get(k).getId()).append(":").append(group.get(k).getType()).append(",");
        }
        if (str.length() != 0)
            str = new StringBuilder(str.substring(0, str.length() - 1));
        str.insert(0, "{");
        str.append("}");
        return str.toString();
    }
}