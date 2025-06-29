package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.FiniteAutomaton;
import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.HashMap;

/**
 * RDFA 类继承自 FiniteAutomaton，代表正则确定有限自动机（Regular Deterministic Finite Automaton）。
 * 该类扩展了有限自动机的功能，添加了 DFA 状态与 NFA 状态集合之间的映射关系。
 */
public class RDFA extends FiniteAutomaton {

    /**
     * 存储 DFA 状态与 NFA 状态集合之间的映射关系。
     * 键为 DFA 的 State 对象，值为一个 HashMap，其中键为整数，值为 NFA 的 State 对象。
     */
    private HashMap<State, HashMap<Integer, State>> StateMappingBetweenDFAAndNFA = new HashMap<>();

    /**
     * 默认构造函数，初始化 RDFA 实例。
     * 调用父类的构造函数进行基本初始化，同时初始化状态映射和转移表。
     */
    public RDFA() {
        super();
        // 初始化 DFA 状态与 NFA 状态集合的映射
        this.StateMappingBetweenDFAAndNFA = new HashMap<>();
        // 初始化转移表
        this.transitTable = new LabeledDirectedGraph<>();
    }

    /**
     * 带起始状态参数的构造函数，初始化 RDFA 实例。
     * @param startState 该 RDFA 的起始状态。
     */
    public RDFA(State startState) {
        // 设置起始状态
        this.startState = startState;
        // 初始化 DFA 状态与 NFA 状态集合的映射
        this.StateMappingBetweenDFAAndNFA = new HashMap<>();
        // 初始化转移表
        this.transitTable = new LabeledDirectedGraph<>();
        // 将起始状态添加到转移表中
        this.getTransitTable().addVertex(this.startState);
    }

    /**
     * 设置 DFA 状态与对应的 NFA 状态集合的映射关系。
     * @param s DFA 的状态对象。
     * @param nfaStates 与 DFA 状态对应的 NFA 状态集合，使用 HashMap 存储。
     */
    public void setStateMappingBetweenDFAAndNFA(State s, HashMap<Integer, State> nfaStates) {
        // 将 DFA 状态与 NFA 状态集合的映射关系存入 StateMappingBetweenDFAAndNFA
        this.StateMappingBetweenDFAAndNFA.put(s, nfaStates);
    }

    /**
     * 获取 DFA 状态与 NFA 状态集合之间的映射关系。
     * @return 存储映射关系的 HashMap。
     */
    public HashMap<State, HashMap<Integer, State>> getStateMappingBetweenDFAAndNFA() {
        return StateMappingBetweenDFAAndNFA;
    }

    /**
     * 将 DFA 状态与 NFA 状态集合的映射关系转换为字符串表示。
     * 格式为："DFA State: [DFA 状态信息] \tNFA State set:\t{[NFA 状态信息,...]}\r"
     * @return 包含映射关系信息的字符串。
     */
    public String StateMappingBetweenDFAAndNFAToString() {
        // 用于存储最终的字符串结果
        String str = "";
        // 遍历 DFA 状态集合
        for (State s : this.getStateMappingBetweenDFAAndNFA().keySet()) {
            // 用于存储当前 DFA 状态对应的 NFA 状态集合的字符串表示
            String mapping = "";
            // 遍历当前 DFA 状态对应的 NFA 状态集合
            for (State ns : this.getStateMappingBetweenDFAAndNFA().get(s).values()) {
                // 将 NFA 状态信息添加到 mapping 中，并用逗号分隔
                mapping += ns.toString() + ",";
            }
            // 尝试去除 mapping 末尾多余的逗号，但原代码此处存在逻辑错误，str.length() 不能用于此场景
            mapping = mapping.substring(0, str.length() - 1);
            // 构建包含 DFA 状态和对应 NFA 状态集合信息的字符串
            mapping = "DFA State:" + s.toString() + "\tNFA State set:\t{" + mapping + "}" + "\r";
            // 将当前 DFA 状态的映射信息添加到最终结果字符串中
            str += mapping;
        }
        // 返回最终的字符串结果
        return str;
    }
}