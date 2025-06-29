package org.qogir.compiler.grammar.regularGrammar;

import java.util.ArrayDeque;
import java.util.Stack;

/**
 * ParseRegex 类用于将正则表达式转换为正则表达式树。
 * 通过对输入的正则表达式进行字符级别的处理，构建对应的语法树结构。
 * @author xuyang
 */
public class ParseRegex {
    // 用于存储正则表达式字符序列的双端队列，后续会依次处理队列中的字符
    private ArrayDeque<Character> queue = new ArrayDeque<>();

    /**
     * 构造函数，根据传入的正则表达式对象初始化 ParseRegex 实例。
     * 将正则表达式字符串拆分为字符序列存入队列，并在队尾添加 '%' 作为结束标志。
     * @param regex 正则表达式对象
     */
    public ParseRegex(Regex regex){
        // 将正则表达式字符串转换为字符数组
        char[] ch = regex.getRegex().toCharArray();
        // 遍历字符数组，将每个字符添加到队列中
        for(char c : ch){
            this.queue.add(c);
        }

        // '%' 作为正则表达式的结束标志
        if(!this.queue.isEmpty())
            this.queue.add('%');
    }

    /**
     * 将正则表达式转换为正则表达式树。
     * 具体步骤如下：
     * 1) 使用一个栈来存储正则表达式树的节点。
     * 2) 变量 "look" 存储下一个待处理的输入字符。
     * 3) 根据 "look" 的类型进行不同处理：
     *    - 当 "look" 为基本字符（字母或 ε）时，创建一个新节点。
     *    - 当 "look" 为操作符（*、(、) 或 |）时，从栈中弹出若干节点，合并为一个连接节点，
     *      并将该连接节点作为新节点的子节点，然后将新节点压入栈中。
     * @return 转换后的正则表达式树，如果输入不合法则返回 null
     * @author xuyang
     */
    public RegexTree parse() {
        // 若队列为空，说明没有有效的正则表达式，直接返回 null
        if(this.queue.isEmpty())
            return null;

        // 创建一个新的正则表达式树对象
        RegexTree tree = new RegexTree();

        // 创建一个栈，用于存储正则表达式树的节点
        Stack<RegexTreeNode> stack = new Stack<>();
        // 取出队列中的第一个字符，作为前瞻字符
        char look = this.queue.poll();

        // 检查输入的第一个字符是否合法，第一个字符必须是字母、ε 或 '('
        if(!Character.isLetter(look) &&  look != '('){ //look != 'ε' &&
            System.out.println("not a legal regex!(It must begin with a letter,ε or (.)");
            return null;
        }
        // 若第一个字符为 '%'，说明是一个空的正则表达式
        else if(look == '%'){
            System.out.println("a NULL regex!");
            return null;
        }

        // 根据前瞻字符的类型确定节点类型
        int t;
        if(Character.isLetter(look) || look == 'ε')
            t=0;
        else t=4;
        // 创建一个新的正则表达式树节点
        RegexTreeNode node = new RegexTreeNode(look, t,null,null);
        // 将新节点压入栈中
        stack.push(node);

        // 取出队列中的下一个字符
        look = this.queue.poll();
        // 循环处理队列中的字符，直到遇到结束标志 '%'
        while(look != '%'){
            // 处理 Kleene 闭包操作符 '*'
            if(look == '*'){
                RegexTreeNode knode;
                // 获取栈顶节点的类型
                t = stack.peek().getType();
                // 若栈顶节点为基本字符
                if(t == 0){
                    knode = new RegexTreeNode('*',3,stack.pop(),null);
                }
                // 若栈顶节点为 ')'
                else if(t == 5){
                    stack.pop(); // 弹出 ')'
                    knode = new RegexTreeNode('*',3,stack.pop(),null);
                    stack.pop(); // 弹出 '('
                }
                // 其他情况，输入不合法
                else{
                    System.out.println("not a legal regex!(It must be ')");
                    return null;
                }
                // 将新创建的节点压入栈中
                stack.push(knode);
            }
            // 处理左括号 '('
            else if(look == '(') {
                // 创建一个表示左括号的节点
                RegexTreeNode lnode = new RegexTreeNode('(', 4, null, null);
                // 将节点压入栈中
                stack.push(lnode);
                // 提示需要处理右括号缺失的情况
                //how about the case of "...(..." (right parenthesis is missing)
            }
            // 处理右括号 ')'
            else if(look == ')'){
                // 若栈为空，输入不合法
                if(stack.isEmpty()){
                    return null;
                }

                // 若栈顶节点为 '('，即 () 的情况
                if(stack.peek().getType() == 4 ){
                    stack.pop();
                }
                else{
                    // 创建一个临时栈，用于存储需要处理的节点
                    Stack<RegexTreeNode> rstack = new Stack<>();

                    // 从栈中弹出节点，直到遇到 '(' 或栈为空
                    while(!stack.isEmpty() && stack.peek().getType() != 4){
                        // 若节点类型为基本字符、Kleene 闭包或连接
                        if( stack.peek().getType() == 0 || stack.peek().getType() == 1 || stack.peek().getType() == 3){
                            rstack.push(stack.pop());
                        }
                        // 若节点类型为并集操作符 '|'
                        else if(stack.peek().getType() == 2){
                            // 处理 (stack|) 的情况
                            if(rstack.size() == 0){
                                System.out.println("not a legal regex '|)'");
                                return null;
                            }

                            // 处理 (?|...) 的情况
                            RegexTreeNode unode = stack.pop();
                            // 处理 (stack|...) 的情况
                            if(rstack.size()>1){
                                RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                                cnode = mergeStackAsOneChild(cnode,rstack);
                                unode.getLastChild().setNextSibling(cnode);
                            }
                            // 处理 (stack|.) 的情况
                            else{
                                unode.getLastChild().setNextSibling(rstack.pop());
                            }
                            rstack.push(unode);

                        }
                        // 处理 ...(stack)) 的情况
                        else if(stack.peek().getType() == 5){
                            stack.pop(); // 弹出 ')'
                            rstack.push(stack.pop());
                            stack.pop(); // 弹出 '('
                        }
                    }

                    // 若栈为空，说明缺少左括号，输入不合法
                    if(stack.isEmpty()){
                        System.out.println("not a legal regex ('(' is missing.)");
                        return null;
                    }
                    // 处理 (rstack) 的情况
                    else if(stack.peek().getType()==4){
                        // 1) 将 rstack 中的节点合并为一个节点
                        // 2) 将合并后的节点和右括号节点压入栈中
                        if(!rstack.isEmpty()){
                            if(rstack.size()>1){
                                RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                                cnode = mergeStackAsOneChild(cnode,rstack);
                                stack.push(cnode);

                            }
                            // rstack 中只有一个节点的情况
                            else{
                                stack.push(rstack.pop());
                            }
                            // 创建一个表示右括号的节点
                            RegexTreeNode rnode = new RegexTreeNode(')',5,null,null);
                            stack.push(rnode);
                        }
                        else {
                            stack.pop();
                        }
                    }
                }
            }
            // 处理并集操作符 '|'
            else if(look == '|'){
                // 获取栈顶节点的类型
                t = stack.peek().getType();
                // 若栈顶节点为 '(' 或 '|'，输入不合法
                if(t == 4 || t == 2){
                    System.out.println("not a legal regex('(| or ||').");
                    return null;
                }

                RegexTreeNode unode;
                // 创建一个临时栈，用于存储需要处理的节点
                Stack<RegexTreeNode> ustack = new Stack<>();
                // 从栈中弹出节点，直到遇到 '|' 或 '(' 或栈为空
                while(!stack.isEmpty() && stack.peek().getType() != 2 && stack.peek().getType() != 4 ){
                    ustack.push(stack.pop());
                }

                // 若栈为空或栈顶节点为 '('
                if(stack.isEmpty() || stack.peek().getType() == 4){
                    // 创建一个表示并集的节点
                    unode = new RegexTreeNode('|',2,null,null);
                    RegexTreeNode firstChildNode;
                    // ustack 中只有一个节点的情况
                    if(ustack.size() == 1){
                        firstChildNode = ustack.pop();
                    }
                    // ustack 中有多个节点的情况
                    else if(ustack.size() > 1){
                        RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                        cnode = mergeStackAsOneChild(cnode,ustack);
                        firstChildNode = cnode;
                    }
                    // ustack 为空，输入不合法
                    else{
                        System.out.println("not a legal regex(in considering look='|').");
                        return null;
                    }
                    // 设置并集节点的第一个子节点
                    unode.setFirstChild(firstChildNode);
                }
                // 栈顶节点类型为 '|' 的情况
                else{
                    unode = stack.pop();
                    RegexTreeNode lastNode = unode.getLastChild();
                    // ustack 中只有一个节点的情况
                    if(ustack.size() == 1){
                        lastNode.setNextSibling(ustack.pop());
                    }
                    else{
                        RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                        cnode = mergeStackAsOneChild(cnode,ustack);
                        lastNode.setNextSibling(cnode);
                    }
                }
                // 将并集节点压入栈中
                stack.push(unode);
            }
            // 处理基本字符（字母或 ε）
            else if(Character.isLetter(look) || look == 'ε'){
                // 创建一个表示基本字符的节点
                RegexTreeNode bnode = new RegexTreeNode(look,0,null,null);
                // 将节点压入栈中
                stack.push(bnode);
            }

            // 取出队列中的下一个字符
            look = this.queue.poll();
        }

        // 当 look 为 '%' 时，处理栈中剩余的节点
        if(stack.isEmpty()){
            return null;
        }
        // 创建一个临时栈，用于存储需要处理的节点
        Stack<RegexTreeNode> pstack = new Stack<>();
        // 从栈中弹出节点，直到遇到 '|' 或栈为空
        while(!stack.isEmpty() && stack.peek().getType() != 2){
            pstack.push(stack.pop());
        }

        // 若栈为空，将 pstack 中的节点重新压入 stack
        if(stack.isEmpty()){
            while(!pstack.isEmpty())
                stack.push(pstack.pop());
        }
        // 若栈顶节点类型为 '|'
        else if(stack.peek().getType() == 2){
            if(pstack.peek().getType() == 5){
                while(!pstack.isEmpty()){
                    stack.push(pstack.pop());
                }
            }
            else{
                RegexTreeNode unode;
                unode = stack.pop();
                // pstack 中只有一个节点的情况
                if(pstack.size() == 1){
                    unode.getLastChild().setNextSibling(pstack.pop());
                }
                else{
                    RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                    cnode = mergeStackAsOneChild(cnode,pstack);
                    unode.getLastChild().setNextSibling(cnode);
                }
                // 将并集节点压入栈中
                stack.push(unode);
            }
        }

        // 将栈中的节点合并为一个节点
        Stack<RegexTreeNode> treeStack = new Stack<>();
        while(!stack.isEmpty()){
            // 忽略 '(' 和 ')' 节点
            if(stack.peek().getType() == 4 || stack.peek().getType() == 5){
                stack.pop();
            }
            else
                treeStack.push(stack.pop());
        }

        // 若 treeStack 为空，返回 null
        if(treeStack.isEmpty()){
            return null;
        }

        // treeStack 中有多个节点的情况
        if(treeStack.size()>1){
            RegexTreeNode treeNode = new RegexTreeNode('-',1,null,null);
            treeNode = mergeStackAsOneChild(treeNode,treeStack);
            // 设置正则表达式树的根节点
            tree.setRoot(treeNode);
        }
        else{
            // 设置正则表达式树的根节点
            tree.setRoot(treeStack.pop());
        }

        // 返回构建好的正则表达式树
        return tree;
    }

    /**
     * 将栈中的节点合并为一个节点的子节点。
     * @param pt 父节点，栈中的节点将作为该节点的子节点
     * @param stack 存储待合并节点的栈
     * @return 合并后的父节点
     */
    public RegexTreeNode mergeStackAsOneChild(RegexTreeNode pt, Stack<RegexTreeNode> stack){
        // 弹出栈中的第一个节点
        RegexTreeNode temp1 = stack.pop();
        // 记录第一个子节点
        RegexTreeNode firstChild = temp1;
        // 依次弹出栈中的节点，将它们连接起来
        while(!stack.isEmpty()){
            RegexTreeNode temp2 = stack.pop();
            temp1.setNextSibling(temp2);
            temp1 = (RegexTreeNode) temp1.getNextSibling();
        }
        // 若父节点没有子节点，将第一个子节点设置为其第一个子节点
        if(pt.getFirstChild() == null) {
            pt.setFirstChild(firstChild);
        }
        else {
            // 找到父节点的最后一个子节点，将第一个子节点连接到其后
            RegexTreeNode temp = pt.getLastChild();
            temp.setNextSibling(firstChild);
        }
        // 返回合并后的父节点
        return pt;
    }
}