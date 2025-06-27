package org.qogir.compiler.grammar.regularGrammar;

import java.util.ArrayDeque;
import java.util.Stack;

/**
 * An implementation of converting a regex to a regex tree.
 * @author xuyang
 */

public class ParseRegex {
    private ArrayDeque<Character> queue = new ArrayDeque<>();

    /**
     * Construct a ParseRegex object with a regex.
     * The input string of regex is divided into a sequence of char
     * For convenience, the char '%' indicating the end of the input is appended to the sequence
     * @param regex a regular expression
     */
    public ParseRegex(Regex regex){
        char[] ch = regex.getRegex().toCharArray();
        for(char c : ch){
            this.queue.add(c);
        }

        //%-end of the regex
        if(!this.queue.isEmpty())
            this.queue.add('%');
    }

    /**
     * Converting the regex into a regex tree
     * 1) Set a stack to hold the nodes of regex tree
     * 2) The variable "look" hold the next input char
     * 3) According to the type of look, a new node is
     *    created when the type of the "look" is basic case (type = letter or ε),
     *    or a new node is created by popping several nodes in the stack, merging
     *    them as a concatenation node, taking the conca node as its child when
     *    the type of the "look" is operator (type = * ,(, ) or |)，
     *    Then the new node is pushed into the stack.
     * @return a regex tree
     * @author xuyang
     */
    public RegexTree parse() {
        //System.out.println("\t2.1) Convert the regex into a tree.");
        if(this.queue.isEmpty())
            return null;

        RegexTree tree = new RegexTree();

        Stack<RegexTreeNode> stack = new Stack<>();
        //lookahead char
        char look = this.queue.poll();

        if(!Character.isLetter(look) &&  look != '('){ //look != 'ε' &&
            //The first char must be a letter, ε or '('
            System.out.println("not a legal regex!(It must begin with a letter,ε or (.)");
            return null;
        }
        else if(look == '%'){
            System.out.println("a NULL regex!");
            return null;
        }

        int t;
        if(Character.isLetter(look) || look == 'ε')
            t=0;
        else t=4;
        RegexTreeNode node = new RegexTreeNode(look,t,null,null);
        stack.push(node);

        look = this.queue.poll();
        while(look != '%'){
            if(look == '*'){
                RegexTreeNode knode;
                t = stack.peek().getType();
                if(t == 0){// is basic before *
                    knode = new RegexTreeNode('*',3,stack.pop(),null);
                }
                else if(t == 5){ //is a ')' before *
                    stack.pop(); //pop ')'
                    knode = new RegexTreeNode('*',3,stack.pop(),null);
                    stack.pop(); //pop '('
                }else{ //is other char before *, not legal
                    System.out.println("not a legal regex!(It must be ')");
                    return null;
                }
                stack.push(knode);
            }
            else if(look == '(') {
                RegexTreeNode lnode = new RegexTreeNode('(', 4, null, null);
                stack.push(lnode);
                //how about the case of "...(..." (right parenthesis is missing)
            }
            else if(look == ')'){
                if(stack.isEmpty()){
                    return null;
                }

                //t = stack.peek().getType();
                if(stack.peek().getType() == 4 ){ // case: ()
                    stack.pop();
                }
                else{
                    Stack<RegexTreeNode> rstack = new Stack<>();

                    while(!stack.isEmpty() && stack.peek().getType() != 4){
                        if( stack.peek().getType() == 0 || stack.peek().getType() == 1 || stack.peek().getType() == 3){//basic,kleene or concatenation(the case of conca exist?)
                            rstack.push(stack.pop());
                        }
                        else if(stack.peek().getType() == 2){//union, case (stack|?)
                            if(rstack.size() == 0){ //case (stack|)
                                System.out.println("not a legal regex '|)'");
                                return null;
                            }

                            // case (?|...)
                            RegexTreeNode unode = stack.pop();
                            if(rstack.size()>1){ //case (stack|...)
                                RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                                cnode = mergeStackAsOneChild(cnode,rstack);//
                                unode.getLastChild().setNextSibling(cnode);
                            }else{ //size = 1, case (stack|.)
                                unode.getLastChild().setNextSibling(rstack.pop());
                            }
                            rstack.push(unode);

                        }
                        else if(stack.peek().getType() == 5){ //case ...(stack))
                            stack.pop(); //pop ')'
                            rstack.push(stack.pop());
                            stack.pop(); // pop '('
                        }
                    }

                    if(stack.isEmpty()){
                        System.out.println("not a legal regex ('(' is missing.)");
                        return null;
                    }
                    else if(stack.peek().getType()==4){ //case (rstack)
                        // 1) convert the nodes in rstack into one node
                        // 2) push the converted node and the right-parenthesis node
                        if(!rstack.isEmpty()){
                            if(rstack.size()>1){
                                RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                                cnode = mergeStackAsOneChild(cnode,rstack);
                                stack.push(cnode);

                            }else{ //rstack.size = 1
                                stack.push(rstack.pop());
                            }
                            RegexTreeNode rnode = new RegexTreeNode(')',5,null,null);
                            stack.push(rnode);
                        }
                        else {
                            stack.pop();
                        }
                    }
                }
            }
            else if(look == '|'){
                t = stack.peek().getType();
                if(t == 4 || t == 2){
                    System.out.println("not a legal regex('(| or ||').");
                    return null;
                }

                RegexTreeNode unode;
                Stack<RegexTreeNode> ustack = new Stack<>();
                while(!stack.isEmpty() && stack.peek().getType() != 2 && stack.peek().getType() != 4 ){
                    ustack.push(stack.pop());
                }

                if(stack.isEmpty() || stack.peek().getType() == 4){
                    unode = new RegexTreeNode('|',2,null,null);
                    RegexTreeNode firstChildNode;
                    if(ustack.size() == 1){
                        firstChildNode = ustack.pop();
                    }
                    else if(ustack.size() > 1){
                        RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                        cnode = mergeStackAsOneChild(cnode,ustack);
                        firstChildNode = cnode;
                    }
                    else{
                        System.out.println("not a legal regex(in considering look='|').");
                        return null;
                    }
                    unode.setFirstChild(firstChildNode);
                }
                else{ //type=2
                    unode = stack.pop();
                    RegexTreeNode lastNode = unode.getLastChild();
                    if(ustack.size() == 1){
                        lastNode.setNextSibling(ustack.pop());
                    }
                    else{
                        RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                        cnode = mergeStackAsOneChild(cnode,ustack);
                        lastNode.setNextSibling(cnode);
                    }
                }
                stack.push(unode);
            }
            else if(Character.isLetter(look) || look == 'ε'){
                RegexTreeNode bnode = new RegexTreeNode(look,0,null,null);
                stack.push(bnode);
            }

            look = this.queue.poll();
        }

        //if look == '%'
        if(stack.isEmpty()){
            return null;
        }
        Stack<RegexTreeNode> pstack = new Stack<>();
        while(!stack.isEmpty() && stack.peek().getType() != 2){
            pstack.push(stack.pop());
        }

        if(stack.isEmpty()){
            while(!pstack.isEmpty())
                stack.push(pstack.pop());
        }
        else if(stack.peek().getType() == 2){
            if(pstack.peek().getType() == 5){
                while(!pstack.isEmpty()){
                    stack.push(pstack.pop());
                }
            }
            else{
                RegexTreeNode unode;
                unode = stack.pop();
                if(pstack.size() == 1){
                    unode.getLastChild().setNextSibling(pstack.pop());
                }
                else{
                    RegexTreeNode cnode = new RegexTreeNode('-',1,null,null);
                    cnode = mergeStackAsOneChild(cnode,pstack);
                    unode.getLastChild().setNextSibling(cnode);
                }
                stack.push(unode);
            }
        }

        // merge the nodes in stack as one node
        Stack<RegexTreeNode> treeStack = new Stack<>();
        while(!stack.isEmpty()){
            if(stack.peek().getType() == 4 || stack.peek().getType() == 5){
                stack.pop();
            }
            else
                treeStack.push(stack.pop());
        }

        if(treeStack.isEmpty()){
            return null;
        }

        if(treeStack.size()>1){
            RegexTreeNode treeNode = new RegexTreeNode('-',1,null,null);
            treeNode = mergeStackAsOneChild(treeNode,treeStack);
            tree.setRoot(treeNode);
        }
        else{
            tree.setRoot(treeStack.pop());
        }

        return tree;
    }

    /**
     * Make nodes in a stack as children of one node.
     * @param stack holds the nodes that will be merged.
     */
    public RegexTreeNode mergeStackAsOneChild(RegexTreeNode pt, Stack<RegexTreeNode> stack){
        RegexTreeNode temp1 = stack.pop();
        RegexTreeNode firstChild = temp1;
        while(!stack.isEmpty()){
            RegexTreeNode temp2 = stack.pop();
            temp1.setNextSibling(temp2);
            temp1 = (RegexTreeNode) temp1.getNextSibling();
        }
        if(pt.getFirstChild() == null) {
            pt.setFirstChild(firstChild);
        }
        else {
            RegexTreeNode temp = pt.getLastChild();
            temp.setNextSibling(firstChild);
        }
        return pt;
    }
}
