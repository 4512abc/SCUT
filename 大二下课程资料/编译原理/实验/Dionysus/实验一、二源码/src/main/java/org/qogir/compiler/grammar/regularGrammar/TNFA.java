package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.FiniteAutomaton;
import org.qogir.compiler.FA.State;

/**
 * TNFA 类表示一个非确定有限自动机（NFA），遵循 McNaughton - Yamada - Thompson 算法。
 * 非确定有限自动机是一个五元组 (S,∑,F,s0,sf)，各元素含义如下：
 *   S - 有限状态集合，即 NFA 转移图的顶点集合。
 *   ∑ - 字母表，不包含 ε（空串）。
 *   F - 状态转移函数，S X ∑ U {ε} -> S 的子集。
 *   s0 - 起始状态。
 *   sf - 接受状态。
 * 该类实现的 NFA 具有以下特性：
 *   - 每个 NFA 仅有一个接受状态。
 *   - 接受状态没有出边，起始状态没有入边。
 *   - 除接受状态外，每个状态要么有一条基于字母表中符号的出边，要么有两条基于 ε 的出边。
 */
public class TNFA extends FiniteAutomaton {

    /**
     * 表示 NFA 的接受状态。
     */
    private State acceptingState = new State();

    /**
     * 默认构造函数，初始化一个 TNFA 实例。
     * 会创建一个新的接受状态，并将其类型设置为接受状态，同时将该状态添加到转移表中。
     */
    public TNFA(){
        super();
        // 将接受状态的类型设置为接受状态
        acceptingState.setType(State.ACCEPT);
        // 将接受状态添加到转移表的顶点集合中
        this.transitTable.addVertex(acceptingState);
    }

    /**
     * 带参数的构造函数，使用传入的状态作为接受状态初始化一个 TNFA 实例。
     * @param acceptingState 用于作为 NFA 接受状态的 State 对象。
     */
    public TNFA(State acceptingState){
        super();
        // 将传入的状态赋值给类的接受状态属性
        this.acceptingState = acceptingState;
        // 将接受状态的类型设置为接受状态
        this.acceptingState.setType(State.ACCEPT);
        // 将接受状态添加到转移表的顶点集合中
        this.transitTable.addVertex(this.acceptingState);
    }

    /**
     * 获取 NFA 的接受状态。
     * @return 表示接受状态的 State 对象。
     */
    public State getAcceptingState() {
        return acceptingState;
    }

    /**
     * 设置 NFA 的接受状态。
     * @param acceptingState 用于作为新接受状态的 State 对象。
     */
    public void setAcceptingState(State acceptingState) {
        this.acceptingState = acceptingState;
    }
}