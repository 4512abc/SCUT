package org.qogir.simulation.scanner;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.grammar.regularGrammar.Regex;
import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;
import org.qogir.compiler.grammar.regularGrammar.SubsetConstruction;
import org.qogir.compiler.grammar.regularGrammar.TNFA;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.HashMap;

/**
 *  scan uses Maximal Munch principle and priority system.
 *  使用最大匹配原则和优先级系统进行扫描。
 *  Run all NFAs in parallel, keeping track of the last match.
 *  并行运行所有非确定有限自动机（NFA），记录最后一次匹配信息。
 *  When all automata get stuck, report the last match and restart the search at that point.
 *  当所有自动机都无法继续转移时，输出最后一次匹配结果，并从该位置重新开始搜索。
 *  When more than one regular expressions apply, choose the one with the greater “priority.”
 *  当有多个正则表达式都能匹配时，选择优先级更高的那个。
 *  If exist two regular expressions with same priority can accept the same input string(substring), error.
 *  如果存在两个优先级相同的正则表达式都能接受相同的输入字符串（子串），则报错。
 *  @author xuyang
 */
public class ScanWithNFA extends Scan{

    /**
     * 构造函数，初始化 ScanWithNFA 实例。
     *
     * @param rg 正则文法对象，定义了扫描规则。
     * @param input 待扫描的输入字符串。
     */
    public ScanWithNFA(RegularGrammar rg, String input){
        super(rg, input);
    }


    /**
     * 重写父类的扫描方法，使用 NFA 对输入字符串进行扫描。
     *
     * @param tokenQueue 用于存储扫描生成的词法单元（Token）的双端队列。
     * @return 扫描结果，取值定义在 ScanMessage 类中，如匹配成功、匹配失败或文法存在二义性等。
     */
    @Override
    public int scan(ArrayDeque tokenQueue){ //ArrayDeque scan() {
        // Get the NFA.
        // 创建 Scanner 实例，用于构建 NFA
        Scanner scanner = new Scanner(rg);
        // 调用 Scanner 的 constructNFA 方法，根据正则文法构建 NFA
        TNFA nfa =  scanner.constructNFA();
        // 获取 NFA 的状态转移表
        LabeledDirectedGraph<State> tb = nfa.getTransitTable();
        // 获取 NFA 的起始状态
        State startState = nfa.getStartState();

        // add "$" for representing the input string.
        // 在输入字符串末尾添加结束符 '$'，用于标记输入结束
        String inputList = this.input + "$";
        // 将添加结束符后的字符串转换为字符数组，便于逐字符处理
        char[] input = inputList.toCharArray();

        // All NFAs start in parallel to scan.
        // 创建子集构造实例，用于计算 ε 闭包和状态转移
        SubsetConstruction sc = new SubsetConstruction();
        // 初始化起始状态集合，将起始状态加入集合
        HashMap<Integer, State> startStates = new HashMap<>();
        startStates.put(startState.getId(),startState);
        // 计算起始状态的 ε 闭包
        startStates = sc.epsilonClosure(startStates,tb);

        //record last accepting state during NFA running.
        // 记录 NFA 运行过程中的最后一个接受状态集合
        HashMap<Integer, State> lastAcceptingStates = new HashMap<>();
        // 记录当前接受状态集合
        HashMap<Integer, State> currentAcceptingStates = new HashMap<>();

        //used for record the start and end position of substring to be output
        // 记录待输出子串的起始字符索引
        int lastStartCharAt = 0;
        // 记录待输出子串的最后一个接受字符索引
        int lastAcceptedCharAt = 0;

        //initialize current states with start states
        // 初始化当前状态集合，将起始状态集合复制到当前状态集合
        HashMap<Integer, State> currentStates = new HashMap<>();
        currentStates.putAll(startStates);
        // 用于存储下一个状态集合
        HashMap<Integer, State> nextStates = new HashMap<>();

        // 遍历输入字符数组
        for(int i = 0; i< input.length; i++){

            // 检查当前字符是否合法，若不是结束符 '$' 且不在正则文法的符号集合中，匹配失败
            if(input[i]!='$' && !rg.symbols.contains(input[i]))
                return ScanMessage.NOT_MATCH;
            //throw new AssertionError("The input " +  this.input + " can not be matched with the regular grammar!");

            // 清空下一个状态集合
            nextStates.clear();

            // 计算当前状态集合在输入字符作用下的 ε 闭包，得到下一个状态集合
            nextStates.putAll(sc.epsilonClosureWithMove(currentStates, input[i], tb));

            //put the accepting states in next states into current accepting states
            // 清空当前接受状态集合
            currentAcceptingStates.clear();
            // 遍历下一个状态集合
            for(State s : nextStates.values()) {
                // 若状态为接受状态或既是接受状态又是起始状态
                if(s.getType() == State.ACCEPT || s.getType() == State.ACCEPTANDSTART)
                    // 将该状态加入当前接受状态集合
                    currentAcceptingStates.put(s.getId(),s);
            }

            // 若当前接受状态集合不为空
            if(!currentAcceptingStates.isEmpty()){
                // 更新最后一个接受字符的索引
                lastAcceptedCharAt = i;
                // 清空最后一个接受状态集合
                lastAcceptingStates.clear();
                // 将当前接受状态集合复制到最后一个接受状态集合
                lastAcceptingStates.putAll(currentAcceptingStates);
            }

            // 若下一个状态集合为空，说明自动机无法继续转移
            if(nextStates.isEmpty()){ //stuck, can output
                // 若最后一个接受状态集合为空，匹配失败
                if(lastAcceptingStates.isEmpty()){
                    return ScanMessage.NOT_MATCH;
                    //throw new AssertionError("The input " +  this.input + " can not be matched with the regular grammar!");
                }
                else {//if(!lastAcceptingStates.isEmpty(), output token
                    // 截取本次匹配得到的词法单元
                    String lexeme = this.input.substring(lastStartCharAt, lastAcceptedCharAt + 1);
                    // 获取正则表达式到 NFA 的映射
                    HashMap<Regex, TNFA> rtonfa = scanner.getRegexToNFA();
                    // 初始化优先级为 -1
                    int priority = -1;
                    // 遍历正则表达式到 NFA 的映射
                    for(Regex r : rtonfa.keySet()){
                        // 若最后一个接受状态集合包含当前正则表达式对应 NFA 的接受状态
                        if(lastAcceptingStates.containsValue(rtonfa.get(r).getAcceptingState())) {
                            // 若当前正则表达式的优先级大于记录的优先级
                            if(r.getPriority() > priority){
                                // 更新优先级
                                priority = r.getPriority();
                                // 获取正则表达式的名称
                                String regexName = r.getName();
                                // 将词法单元封装成 Token 对象添加到 tokenQueue 中
                                tokenQueue.add(new Token(regexName,lexeme));
                            }
                            // 若当前正则表达式的优先级等于记录的优先级，文法存在二义性
                            else if(r.getPriority() == priority){
                                return ScanMessage.AMBIGUITY_GRAMMAR;
                                //throw new AssertionError("The regular grammar" + rg.toString() + " is ambiguity!");
                            }
                        }
                    }
                    // 若当前字符不是结束符 '$'，重新开始匹配
                    if(input[i] != '$') {
                        // 将索引回退到最后一个被接受字符的位置
                        i = lastAcceptedCharAt;
                        // 更新下次匹配的起始位置
                        lastStartCharAt = lastAcceptedCharAt + 1;
                        // 清空当前状态集合
                        currentStates.clear();
                        // 将起始状态集合复制到当前状态集合，重新开始 NFA 运行
                        currentStates.putAll(startStates);//restart NFA
                    }
                }
            }
            else{ // hold current situation and going on
                // 清空当前状态集合
                currentStates.clear();
                // 将下一个状态集合复制到当前状态集合，继续运行
                currentStates.putAll(nextStates);
            }
        }

        // 若最后一个接受字符的索引不等于输入字符串长度减 2（除去结束符 '$'），匹配失败
        if(lastAcceptedCharAt != input.length - 2)
            return ScanMessage.NOT_MATCH;
        //throw new AssertionError("The input " + this.input + " can not be matched with the regular grammar!");
        // 扫描完成，匹配成功
        return ScanMessage.SUCCESS_MATCH;
    }
}