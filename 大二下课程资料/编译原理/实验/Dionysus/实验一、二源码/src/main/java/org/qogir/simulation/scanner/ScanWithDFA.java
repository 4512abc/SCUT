package org.qogir.simulation.scanner;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.grammar.regularGrammar.RDFA;
import org.qogir.compiler.grammar.regularGrammar.Regex;
import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;
import org.qogir.compiler.grammar.regularGrammar.TNFA;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.HashMap;

/**
 * ScanWithDFA 类继承自 Scan 类，用于使用确定有限自动机（DFA）对输入字符串进行扫描。
 * 该类会依据给定的正则文法构建 DFA，然后利用这个 DFA 对输入字符串进行匹配和扫描操作，
 * 根据匹配结果返回相应的扫描消息。
 */
public class ScanWithDFA extends Scan{

    /**
     * 构造函数，初始化 ScanWithDFA 实例。
     * 调用父类 Scan 的构造函数，将正则文法和输入字符串传递给父类进行初始化。
     *
     * @param rg 用于扫描的正则文法对象。
     * @param input 待扫描的输入字符串。
     */
    public ScanWithDFA(RegularGrammar rg, String input) {
        super(rg, input);
    }

    /**
     * 重写父类的 scan 方法，使用 DFA 对输入字符串进行扫描。
     * 该方法会构建 DFA，遍历输入字符串，根据 DFA 的状态转移规则进行匹配，
     * 并将匹配得到的词法单元（lexeme）封装成 Token 对象添加到 tokenQueue 中。
     *
     * @param tokenQueue 用于存储扫描过程中生成的 Token 对象的双端队列。
     * @return 表示扫描结果的整数，其值定义在 ScanMessage 类中，
     *         如 ScanMessage.SUCCESS_MATCH 表示匹配成功，
     *         ScanMessage.NOT_MATCH 表示匹配失败，
     *         ScanMessage.AMBIGUITY_GRAMMAR 表示文法存在二义性。
     */
    @Override
    public int scan(ArrayDeque tokenQueue) {
        // 创建 Scanner 实例，用于构建 DFA
        Scanner scanner = new Scanner(rg);
        // 调用 Scanner 的 constructDFA 方法，根据正则文法构建 DFA
        RDFA dfa = scanner.constructDFA();
        // 获取 DFA 的转移表，用于状态转移操作
        LabeledDirectedGraph<State> tb = dfa.getTransitTable();
        // 获取 DFA 的起始状态
        State startState = dfa.getStartState();

        // 在输入字符串末尾添加结束符 '$'，方便扫描结束判断
        String inputList = this.input + "$";
        // 将添加结束符后的字符串转换为字符数组，便于逐字符处理
        char[] input = inputList.toCharArray();

        // 记录本次匹配开始字符的索引
        int lastStartCharAt = 0;
        // 记录最后一个被接受字符的索引
        int lastAcceptedCharAt = 0;

        // 创建一个新的状态对象，初始状态为 DFA 的起始状态
        State currentState = new State(startState);

        // 遍历输入字符数组
        for(int i = 0; i < input.length; i++){
            // 如果当前字符不是结束符 '$' 且不在正则文法的符号集合中，说明匹配失败
            if(input[i] != '$' && !rg.symbols.contains(input[i]))
                return ScanMessage.NOT_MATCH;

            // 初始化下一个状态为 null
            State nextState = null;
            // 如果当前状态不为 null，尝试进行状态转移
            if(currentState != null){
                // 遍历 DFA 转移表中的所有边
                for(LabelEdge e : tb.edgeSet()){
                    // 如果边的源状态等于当前状态，且边的标签等于当前输入字符
                    if(tb.getEdgeSource(e) == currentState && e.getLabel().equals(input[i])){
                        // 获取边的目标状态作为下一个状态
                        nextState = tb.getEdgeTarget(e);
                    }
                }
            }
            // 初始化最后一个接受状态为 null
            State lastAcceptingState = null;
            // 如果下一个状态存在
            if(nextState != null) {
                // 如果下一个状态是接受状态（类型为 2 或 20）
                if (nextState.getType() == 2 || nextState.getType() == 20) {
                    // 更新最后一个被接受字符的索引
                    lastAcceptedCharAt = i;
                    // 更新最后一个接受状态
                    lastAcceptingState = nextState;
                }
                // 将当前状态更新为下一个状态
                currentState = nextState;
            }
            else { // 状态转移失败，无法继续匹配，此时可以输出结果
                // 如果没有找到接受状态，说明匹配失败
                if(lastAcceptingState == null){
                    return ScanMessage.NOT_MATCH;
                }
                else {
                    // 从输入字符串中截取本次匹配得到的词法单元
                    String lexeme = this.input.substring(lastStartCharAt, lastAcceptedCharAt + 1);
                    // 获取 DFA 状态到 NFA 状态集合的映射
                    HashMap<State, HashMap<Integer,State>> dfatonfas = scanner.getDFAToNFAs();
                    // 初始化一个存储 NFA 状态的 HashMap
                    HashMap<Integer,State> nfas = new HashMap<>();
                    // 遍历 DFA 状态到 NFA 状态集合的映射的键集
                    for(State s : dfatonfas.keySet()){
                        // 如果当前状态等于最后一个接受状态，此处代码块为空，可根据需求补充逻辑
                        if(s.equals(lastAcceptingState)){

                        }
                    }
                    // 获取正则表达式到 NFA 的映射
                    HashMap<Regex, TNFA> rtonfa = scanner.getRegexToNFA();

                    // 初始化优先级为 -1
                    int priority = -1;
                    // 遍历正则表达式到 NFA 的映射的键集
                    for(Regex r : rtonfa.keySet()){
                        /* 此处代码被注释掉，原逻辑为：
                           如果最后一个接受状态包含 NFA 的接受状态，
                           比较正则表达式的优先级，根据优先级决定是否添加 Token 或判断文法二义性
                        if(lastAcceptingState.containsValue(rtonfa.get(r).getAcceptingState())) {
                            if(r.getPriority() > priority){
                                priority = r.getPriority();
                                String regexName = r.getName();
                                tokenQueue.add(new Token(regexName,lexeme));
                            }
                            else if(r.getPriority() == priority){
                                return ScanMessage.AMBIGUITY_GRAMMAR;
                                //throw new AssertionError("The regular grammar" + rg.toString() + " is ambiguity!");
                            }
                        }*/
                    }
                    // 如果当前字符不是结束符 '$'，需要重新开始匹配
                    if(input[i] != '$') {
                        // 将索引回退到最后一个被接受字符的位置
                        i = lastAcceptedCharAt;
                        // 更新本次匹配开始字符的索引
                        lastStartCharAt = lastAcceptedCharAt + 1;
                        // 将当前状态重置为 DFA 的起始状态，重新开始匹配
                        currentState = startState;
                    }
                }
            }
        }
        // 遍历完输入字符串，匹配成功
        return ScanMessage.SUCCESS_MATCH;
    }
}