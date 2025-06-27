package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.State;

import java.util.ArrayDeque;

//正则转NFA
public class ThompsonConstruction {

    public TNFA translate(RegexTreeNode node){

        if (node == null)
            return null;

        int type = node.getType();

        if (type < 0 || type > 3) {
            throw new IllegalArgumentException("未知的正则表达式节点类型: " + type);
        }

        TNFA tnfa = new TNFA();
        if(type == 0){ //base case
            //add edge with label node.getValue() to nfa
            Character value = node.getValue();
            if (value == null || value.toString().isEmpty()) {
                throw new IllegalArgumentException("基本字符节点值不能为空");
            }
            tnfa.getTransitTable().addEdge(tnfa.getStartState(),tnfa.getAcceptingState(), node.getValue());
            return tnfa;
        }
        /*
        以下
         */
        else if (type == 3) { // Kleene Star (*), only one child
            RegexTreeNode child = (RegexTreeNode) node.getFirstChild();
            if (child == null) {
                throw new IllegalArgumentException("Kleene Star (*) 操作符必须有一个子节点");
            }
            TNFA childNFA = translate(child);
            if (childNFA == null) {
                throw new IllegalStateException("子节点转换为 NFA 时返回了 null");
            }

            tnfa.getTransitTable().addEdge(tnfa.getStartState(), childNFA.getStartState(), 'ε');
            tnfa.getTransitTable().addEdge(childNFA.getAcceptingState(), tnfa.getAcceptingState(), 'ε');
            childNFA.getTransitTable().addEdge(childNFA.getAcceptingState(), childNFA.getStartState(), 'ε');
            tnfa.getTransitTable().addEdge(tnfa.getStartState(), tnfa.getAcceptingState(), 'ε');

            tnfa.getTransitTable().merge(childNFA.getTransitTable());

            // 设置子 NFA 的开始和结束状态为中间状态
            childNFA.getStartState().setType(State.MIDDLE);
            childNFA.getAcceptingState().setType(State.MIDDLE);
        }



        else{ //conca or union
            ArrayDeque<TNFA> queue = new ArrayDeque<>(); //hold all NFAs of children in the regex tree
            RegexTreeNode enode = (RegexTreeNode) node.getFirstChild();
            while(enode != null){ //traverse all children in the regex tree, and build corresponding NFAs
                queue.add(translate(enode));
                enode = (RegexTreeNode) enode.getNextSibling();
            }

            /*
             */
            if (type == 1) { // Concatenation (-)
                if (queue.isEmpty()) return null;

                TNFA first = queue.poll(); // 第一个子 NFA
                tnfa.setStartState(first.getStartState());
                tnfa.getTransitTable().merge(first.getTransitTable());

                first.getStartState().setType(State.START);
                first.getAcceptingState().setType(State.MIDDLE);

                TNFA prev = first;
                while (!queue.isEmpty()) {
                    TNFA curr = queue.poll();
                    tnfa.getTransitTable().addEdge(prev.getAcceptingState(), curr.getStartState(), 'ε');
                    tnfa.getTransitTable().merge(curr.getTransitTable());
                    curr.getStartState().setType(State.MIDDLE);
                    curr.getAcceptingState().setType(State.ACCEPT);
                    prev = curr;
                }
                tnfa.setAcceptingState(prev.getAcceptingState());

                // 设置起始状态为 START，接受状态为 ACCEPT
                tnfa.getStartState().setType(State.START);
                tnfa.getAcceptingState().setType(State.ACCEPT);
            }

            if(type == 2){ //union
                TNFA tempNFA;
                if (queue.size() < 2) {
                    throw new IllegalArgumentException("Union (|) 至少需要两个子表达式");
                }
                while(!queue.isEmpty()){
                    tempNFA = queue.poll();
                    tempNFA.getStartState().setType(State.MIDDLE);
                    tempNFA.getAcceptingState().setType(State.MIDDLE);
                    tnfa.getTransitTable().merge(tempNFA.getTransitTable());
                    tnfa.getTransitTable().addEdge(tnfa.getStartState(),tempNFA.getStartState(),'ε');
                    tnfa.getTransitTable().addEdge(tempNFA.getAcceptingState(),tnfa.getAcceptingState(),'ε');
                }
            }
        }
        return tnfa;
    }
}
