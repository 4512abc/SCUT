package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.util.tree.DefaultTree;

import java.util.ArrayDeque;

public class RegexTree extends DefaultTree<RegexTreeNode> {

    public RegexTree(){
        super();
    }

    @Override
    public String toString() {

        if(this.root == null)
            return null;

        StringBuilder treeStr = new StringBuilder();
        ArrayDeque<RegexTreeNode> queue = new ArrayDeque<>();
        queue.add(this.root);
        RegexTreeNode node = queue.poll();

        while(node != null){
            treeStr.append("(").append(node.toString()).append(")\n");
            RegexTreeNode childnode = (RegexTreeNode) node.getFirstChild();

            if(childnode != null) {
                treeStr.append("\t" + "firstChild:(").append(childnode.toString()).append(")\n");
                queue.add(childnode);
                childnode = (RegexTreeNode) childnode.getNextSibling();

                while (childnode != null) {
                    treeStr.append("\t(").append(childnode.toString()).append(")\n");
                    queue.add(childnode);
                    childnode = (RegexTreeNode) childnode.getNextSibling();
                }
            }
            node = queue.poll();
        }
        StringBuilder str = new StringBuilder();
        str.append("The regex tree:\n").append(treeStr.toString());
        return str.toString();
    }

    public String export(){
        String treeJson="";
        return treeJson;
    }
}
