package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.State;

import java.util.ArrayDeque;

/**
 * ThompsonConstruction 类实现了 Thompson 构造算法，用于将正则表达式的语法树转换为等价的 NFA（非确定有限自动机）。
 * Thompson 构造算法是一种将正则表达式转换为 NFA 的经典方法，通过递归地处理正则表达式的各个部分来构建 NFA。
 */
public class ThompsonConstruction {

    /**
     * 将正则表达式语法树节点转换为对应的 NFA。
     *
     * @param node 正则表达式语法树的节点，由 RegexTreeNode 表示。
     * @return 与输入节点对应的 TNFA 对象，如果输入节点为 null 则返回 null。
     */
    public TNFA translate(RegexTreeNode node) {
        // 如果输入节点为 null，直接返回 null
        if (node == null)
            return null;

        // 获取当前节点的类型
        int type = node.getType();

        // 创建一个新的 TNFA 对象，用于存储转换后的 NFA
        TNFA tnfa = new TNFA();

        // 处理基本情况，即节点类型为基本字符
        if (type == 0) { //base case
            // 为 NFA 添加一条从起始状态到接受状态的边，边的标签为节点的值
            tnfa.getTransitTable().addEdge(tnfa.getStartState(), tnfa.getAcceptingState(), node.getValue());
            return tnfa;
        }
        // 处理 Kleene 闭包情况，正则表达式树中只有一个子节点
        else if (type == 3) { //kleene, only one child in its regex tree
            // 获取子节点的NFA
            RegexTreeNode child = (RegexTreeNode) node.getFirstChild();
            TNFA childNFA = translate(child);

            // 将子NFA的状态设置为中间状态
            childNFA.getStartState().setType(State.MIDDLE);
            childNFA.getAcceptingState().setType(State.MIDDLE);

            // 合并转移表
            tnfa.getTransitTable().merge(childNFA.getTransitTable());

            // 添加ε转移: start -> child's start
            tnfa.getTransitTable().addEdge(tnfa.getStartState(), childNFA.getStartState(), 'ε');
            // 添加ε转移: child's accept -> accept
            tnfa.getTransitTable().addEdge(childNFA.getAcceptingState(), tnfa.getAcceptingState(), 'ε');
            // 添加ε转移: start -> accept (直接跳过)
            tnfa.getTransitTable().addEdge(tnfa.getStartState(), tnfa.getAcceptingState(), 'ε');
            // 添加ε转移: child's accept -> child's start (循环)
            tnfa.getTransitTable().addEdge(childNFA.getAcceptingState(), childNFA.getStartState(), 'ε');

            return tnfa;
        }
        // 处理连接或并集情况
        else {
            // 创建一个队列，用于存储正则表达式树中所有子节点对应的 NFA
            ArrayDeque<TNFA> queue = new ArrayDeque<>();
            // 获取当前节点的第一个子节点
            RegexTreeNode enode = (RegexTreeNode) node.getFirstChild();
            // 遍历正则表达式树的所有子节点，构建对应的 NFA 并加入队列
            while (enode != null) {
                queue.add(translate(enode));
                enode = (RegexTreeNode) enode.getNextSibling();
            }

            // 处理连接情况
            if (type == 1) { //concatenation
                TNFA prevNFA = queue.poll();

                // 将第一个NFA的起始状态设置为主NFA的起始状态
                tnfa.setStartState(prevNFA.getStartState());

                // 处理队列中剩余的NFA
                while (!queue.isEmpty()) {
                    TNFA currentNFA = queue.poll();

                    // 将前一个NFA的接受状态与当前NFA的起始状态合并
                    prevNFA.getAcceptingState().setType(State.MIDDLE);
                    currentNFA.getStartState().setType(State.MIDDLE);

                    // 合并转移表
                    tnfa.getTransitTable().merge(prevNFA.getTransitTable());
                    tnfa.getTransitTable().merge(currentNFA.getTransitTable());

                    // 添加ε转移: prev accept -> current start
                    tnfa.getTransitTable().addEdge(prevNFA.getAcceptingState(), currentNFA.getStartState(), 'ε');

                    prevNFA = currentNFA;
                }

                // 设置最后一个NFA的接受状态为主NFA的接受状态
                tnfa.setAcceptingState(prevNFA.getAcceptingState());
                // 合并最后一个NFA的转移表
                tnfa.getTransitTable().merge(prevNFA.getTransitTable());
            }

            // 处理并集情况
            if (type == 2) {
                TNFA tempNFA;
                // 从队列中取出所有 NFA 进行并集操作
                while (!queue.isEmpty()) {
                    tempNFA = queue.poll();
                    // 将临时 NFA 的起始状态和接受状态类型设置为中间状态
                    tempNFA.getStartState().setType(State.MIDDLE);
                    tempNFA.getAcceptingState().setType(State.MIDDLE);
                    // 将临时 NFA 的转移表合并到主 NFA 的转移表中
                    tnfa.getTransitTable().merge(tempNFA.getTransitTable());
                    // 添加从主 NFA 起始状态到临时 NFA 起始状态的 ε 转移
                    tnfa.getTransitTable().addEdge(tnfa.getStartState(), tempNFA.getStartState(), 'ε');
                    // 添加从临时 NFA 接受状态到主 NFA 接受状态的 ε 转移
                    tnfa.getTransitTable().addEdge(tempNFA.getAcceptingState(), tnfa.getAcceptingState(), 'ε');
                }
            }
        }
        // 返回最终构建好的 NFA
        return tnfa;
    }
}