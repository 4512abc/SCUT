package org.qogir.simulation.scanner;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.grammar.regularGrammar.*;
import org.qogir.compiler.util.graph.LabelEdge;

import java.util.HashMap;

/**
 * An implementation of a regular grammar for:
 * 1) 从正则表达式构建正则表达式树
 * 2) 从正则表达式树构建 NFA
 * 3) 从 NFA 构建 DFA
 * 4) 最小化 DFA
 */
public class Scanner {

    /**
     * A regular grammar {@see }
     * 存储正则文法对象，用于后续的正则表达式处理
     */
    private final RegularGrammar rg;

    /**
     * Hold regex trees for each regex
     * 存储每个正则表达式对应的正则表达式树，键为正则表达式对象，值为对应的正则表达式树
     */
    private HashMap<Regex, RegexTree> regexToRegexTree = new HashMap<>();

    /**
     * Hold NFAs for each regex
     * 存储每个正则表达式对应的 NFA，键为正则表达式对象，值为对应的 NFA
     */
    private HashMap<Regex,TNFA> RegexToNFA = new HashMap<>();

    /**
     * Hold NFA sets for each DFA State
     * 存储每个 DFA 状态对应的 NFA 状态集合，键为 DFA 的状态对象，值为一个 HashMap，其键为整数，值为 NFA 的状态对象
     */
    private HashMap<State, HashMap<Integer,State>> DFAToNFAs = new HashMap<>();

    /**
     * Hold equivalent state sets for minimized DFA
     * 存储最小化 DFA 中每个状态对应的等价状态集合，键为最小化 DFA 的状态对象，值为一个 HashMap，其键为整数，值为等价的 DFA 状态对象
     */
    private HashMap<State,HashMap<Integer,State>> MinDFAToDFAs = new HashMap<>();

    /**
     * 构造函数，使用传入的正则文法对象初始化 Scanner
     * @param rg 正则文法对象
     */
    public Scanner(RegularGrammar rg){
        this.rg = rg;
    }

    /**
     * 构造函数，使用传入的正则表达式数组创建正则文法对象并初始化 Scanner
     * @param regexes 正则表达式数组
     */
    public Scanner(String[] regexes){
        rg = new RegularGrammar(regexes);
    }

    /**
     * 获取每个正则表达式对应的正则表达式树的映射
     * @return 存储正则表达式与正则表达式树映射的 HashMap
     */
    public HashMap<Regex, RegexTree> getRegexToRegexTree() {
        return regexToRegexTree;
    }

    /**
     * 获取每个正则表达式对应的 NFA 的映射
     * @return 存储正则表达式与 NFA 映射的 HashMap
     */
    public HashMap<Regex, TNFA> getRegexToNFA() {
        return RegexToNFA;
    }

    /**
     * 获取每个 DFA 状态对应的 NFA 状态集合的映射
     * @return 存储 DFA 状态与 NFA 状态集合映射的 HashMap
     */
    public HashMap<State, HashMap<Integer, State>> getDFAToNFAs() {
        return DFAToNFAs;
    }

    /**
     * 获取最小化 DFA 中每个状态对应的等价状态集合的映射
     * @return 存储最小化 DFA 状态与等价状态集合映射的 HashMap
     */
    public HashMap<State, HashMap<Integer, State>> getMinDFAToDFAs() {
        return MinDFAToDFAs;
    }

    /**
     * Build a regex tree by ParseRegex{@link ParseRegex#parse}
     * 通过 ParseRegex 类的 parse 方法为指定的正则表达式构建正则表达式树
     * @param r 正则表达式对象
     * @return 对应的正则表达式树 {@link RegexTree}
     */
    public RegexTree constructRegexTree(Regex r){
        // 创建 ParseRegex 对象，用于解析正则表达式
        ParseRegex parser = new ParseRegex(r);
        // 调用 parse 方法解析正则表达式，得到正则表达式树
        RegexTree tree = parser.parse();
        // 将正则表达式与对应的正则表达式树存入映射中
        regexToRegexTree.put(r,tree);
        return tree;
    }

    /**
     * Build regex trees for a Regular grammar with more regexes.
     * The method calls {@see constructRegexTree} and can be used for a Regular grammar with only one regex.
     * 为正则文法中的所有正则表达式构建正则表达式树
     * 该方法调用 constructRegexTree 方法，可用于处理只有一个正则表达式的正则文法
     * @return 一个集合，包含正则文法中每个正则表达式对应的正则表达式树
     */

    public HashMap<Regex,RegexTree> constructRegexTrees(){
        // 若正则文法对象为 null，直接返回 null
        if(rg == null)
            return null;
        // 遍历正则文法中的所有正则表达式
        for(Regex r: rg.getPatterns()){
            // 为每个正则表达式构建正则表达式树并存入映射中
            regexToRegexTree.put(r,constructRegexTree(r));
        }
        return regexToRegexTree;
    }

    /**
     * This private method is used to construct an NFA for a regex.
     * The construction is based on McNaughton-Yamada-Thompson algorithm {@link ThompsonConstruction#translate}.
     * 为指定的正则表达式构建 NFA
     * 构建过程基于 McNaughton - Yamada - Thompson 算法，调用 ThompsonConstruction 类的 translate 方法
     * @param r 正则表达式对象
     * @return An NFA
     */
    public TNFA constructRegexNFA(Regex r){
        // 为指定的正则表达式构建正则表达式树
        RegexTree tree = constructRegexTree(r);
        // 创建 ThompsonConstruction 对象，用于将正则表达式树转换为 NFA
        ThompsonConstruction thompsonConstruction = new ThompsonConstruction();
        // 调用 translate 方法将正则表达式树的根节点转换为 NFA
        TNFA nfa = thompsonConstruction.translate(tree.getRoot());
        // 遍历正则表达式的字符
        for(Character ch : r.getRegex().toCharArray()){
            // 若字符为字母且不为 ε，并且 NFA 的字母表中不包含该字符
            if(Character.isLetter(ch) && ch != 'ε' && !nfa.getAlphabet().contains(ch)){
                // 将该字符添加到 NFA 的字母表中
                nfa.getAlphabet().add(ch);
            }
        }
        return nfa;
    }

    /**
     * This private method is used to construct an DFA for a regex.
     * The construction is based on subset construction algorithm {@link SubsetConstruction#subSetConstruct}.
     * 为指定的正则表达式构建 DFA
     * 构建过程基于子集构造算法，调用 SubsetConstruction 类的 subSetConstruct 方法
     * @param r 正则表达式对象
     * @return An DFA
     */
    public RDFA constructRegexDFA(Regex r){
        // 为指定的正则表达式构建 NFA
        TNFA nfa = constructRegexNFA(r);
        // 创建 SubsetConstruction 对象，用于将 NFA 转换为 DFA
        SubsetConstruction subsetConstruction = new SubsetConstruction();
        // 调用 subSetConstruct 方法将 NFA 转换为 DFA
        RDFA dfa = subsetConstruction.subSetConstruct(nfa);
        // 设置 DFA 的字母表与 NFA 的字母表相同
        dfa.setAlphabet(nfa.getAlphabet());
        return dfa;
    }

    /**
     * Construct NFAs for all regexes in a regular grammar.
     * 为正则文法中的所有正则表达式构建 NFA
     * @return An NFA set
     */
    public HashMap<Regex,TNFA> constructAllNFA(){
        // 用于存储每个正则表达式对应的 NFA
        HashMap<Regex,TNFA> rtonfa = new HashMap<>();
        // 遍历正则文法中的所有正则表达式
        for(Regex r : rg.getPatterns()){
            // 为每个正则表达式构建 NFA 并存入映射中
            rtonfa.put(r,constructRegexNFA(r));
        }
        return rtonfa;
    }

    /**
     *  Construct DFAs for all regexes in a regular grammar.
     * 为正则文法中的所有正则表达式构建 DFA
     * @return a DFA set
     */
    public HashMap<Regex,RDFA> constructAllDFA(){
        // 用于存储每个正则表达式对应的 DFA
        HashMap<Regex,RDFA> rtodfa = new HashMap<>();
        // 遍历正则文法中的所有正则表达式
        for(Regex r : rg.getPatterns()){
            // 为每个正则表达式构建 DFA 并存入映射中
            rtodfa.put(r,constructRegexDFA(r));
        }
        return rtodfa;
    }

    /**
     * construct an DFA with an NFA
     * 使用给定的 NFA 构建 DFA
     * @param nfa an NFA
     * @return an DFA
     */
    public RDFA constructDFA(TNFA nfa){
        // 创建 SubsetConstruction 对象，用于将 NFA 转换为 DFA
        SubsetConstruction subsetConstruction = new SubsetConstruction();
        // 调用 subSetConstruct 方法将 NFA 转换为 DFA
        RDFA dfa = subsetConstruction.subSetConstruct(nfa);
        // 设置 DFA 的字母表与 NFA 的字母表相同
        dfa.setAlphabet(nfa.getAlphabet());
        return dfa;
    }

    /**
     * Minimize an DFA by State Minimization algorithm {@link StateMinimization#minimize}
     * 使用状态最小化算法对给定的 DFA 进行最小化
     * 调用 StateMinimization 类的 minimize 方法
     * @param dfa an DFA
     * @return an DFA
     */
    public RDFA minimizeDFA(RDFA dfa){
        // 创建 StateMinimization 对象，用于对 DFA 进行最小化
        StateMinimization stateMinimization = new StateMinimization();
        // 调用 minimize 方法对 DFA 进行最小化
        RDFA miniDFA = stateMinimization.minimize(dfa);
        // 设置最小化 DFA 的字母表与原 DFA 的字母表相同
        miniDFA.setAlphabet(dfa.getAlphabet());
        return miniDFA;
    }

    /**
     * Construct an NFA for a regular grammar.
     * 为正则文法构建 NFA
     * @return An NFA
     */
    public TNFA constructNFA(){
        // 若正则文法中只有一个正则表达式
        if(rg.getPatterns().size() == 1){
            // 获取该正则表达式
            Regex r = rg.getPatterns().get(0);
            // 为该正则表达式构建 NFA
            TNFA nfa = constructRegexNFA(r);
            // 若 NFA 不为 null
            if(nfa != null)
                // 将正则表达式与对应的 NFA 存入映射中
                this.RegexToNFA.put(r, nfa);
            // 设置 NFA 的字母表为正则文法的符号集合
            nfa.setAlphabet(rg.getSymbols());
            nfa.printMinimizationProcess();
            return nfa;
        }
        // 若正则文法中有多个正则表达式
        else if(rg.getPatterns().size() > 1) {
            // 遍历正则文法中的所有正则表达式
            for (Regex r : rg.getPatterns()) {
                // 为每个正则表达式构建 NFA
                TNFA nfa = constructRegexNFA(r);
                // 若 NFA 不为 null
                if (nfa != null)
                    // 将正则表达式与对应的 NFA 存入映射中
                    this.RegexToNFA.put(r, nfa);
            }
            // 创建一个新的 NFA
            TNFA nfa = new TNFA();
            // 遍历存储每个正则表达式对应 NFA 的映射的值
            for (TNFA tn : this.RegexToNFA.values()) {
                // 若该 NFA 的起始状态不是既是接受状态又是起始状态
                if(tn.getStartState().getType() != State.ACCEPTANDSTART){
                    // 将该 NFA 的起始状态类型设置为中间状态
                    tn.getStartState().setType(State.MIDDLE);
                }
                else{
                    // 将该 NFA 的起始状态类型设置为接受状态
                    tn.getStartState().setType(State.ACCEPT);
                }
                // 将该 NFA 的转移表合并到新 NFA 的转移表中
                nfa.getTransitTable().merge(tn.getTransitTable());
                // 添加一条从新 NFA 的起始状态到该 NFA 起始状态的 ε 转移边
                nfa.getTransitTable().addEdge(new LabelEdge(nfa.getStartState(), tn.getStartState(), 'ε'));
            }
            // 设置新 NFA 的字母表为正则文法的符号集合
            nfa.setAlphabet(rg.getSymbols());
            nfa.printMinimizationProcess();
            return nfa;
        }

        return null;
    }

    /**
     * construct DFA for a regular grammar
     * 为正则文法构建 DFA
     * @return a DFA
     */
    public RDFA constructDFA(){
        // 为正则文法构建 NFA
        TNFA nfa = constructNFA();
        // 创建 SubsetConstruction 对象，用于将 NFA 转换为 DFA
        SubsetConstruction subsetConstruction = new SubsetConstruction();
        // 调用 subSetConstruct 方法将 NFA 转换为 DFA
        RDFA dfa = subsetConstruction.subSetConstruct(nfa);
        // 设置 DFA 的字母表为正则文法的符号集合（此处原代码可能存在问题，rg.symbols 可能应为 rg.getSymbols()）
        dfa.setAlphabet(rg.getSymbols());
        dfa.printMinimizationProcess();
        return dfa;
    }
}