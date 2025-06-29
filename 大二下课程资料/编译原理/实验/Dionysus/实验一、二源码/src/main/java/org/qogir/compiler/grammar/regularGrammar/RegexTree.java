package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.util.tree.DefaultTree;

import java.util.ArrayDeque;

/**
 * RegexTree 类继承自 DefaultTree，用于表示正则表达式的语法树。
 * 该类提供了将正则表达式语法树转换为字符串表示的功能，以及导出语法树为 JSON 字符串的方法。
 */
public class RegexTree extends DefaultTree<RegexTreeNode> {

    /**
     * 构造函数，调用父类的构造函数初始化正则表达式语法树。
     */
    public RegexTree(){
        super();
    }

    /**
     * 将正则表达式语法树转换为字符串表示，采用层序遍历的方式。
     *
     * @return 包含正则表达式语法树结构的字符串，如果根节点为空则返回 null。
     */
    @Override
    public String toString() {
        // 如果根节点为空，直接返回 null
        if(this.root == null)
            return null;

        // 用于构建表示语法树的字符串
        StringBuilder treeStr = new StringBuilder();
        // 使用队列来进行层序遍历
        ArrayDeque<RegexTreeNode> queue = new ArrayDeque<>();
        // 将根节点加入队列
        queue.add(this.root);
        // 从队列中取出一个节点
        RegexTreeNode node = queue.poll();

        // 当队列中还有节点时，继续遍历
        while(node != null){
            // 拼接当前节点的信息，格式为 "(节点信息)\n"
            treeStr.append("(").append(node).append(")\n");
            // 获取当前节点的第一个子节点
            RegexTreeNode childnode = (RegexTreeNode) node.getFirstChild();

            // 如果存在子节点
            if(childnode != null) {
                // 拼接第一个子节点的信息，格式为 "\tfirstChild:(子节点信息)\n"
                treeStr.append("\t" + "firstChild:(").append(childnode).append(")\n");
                // 将第一个子节点加入队列
                queue.add(childnode);
                // 获取第一个子节点的下一个兄弟节点
                childnode = (RegexTreeNode) childnode.getNextSibling();

                // 遍历当前节点的所有兄弟节点
                while (childnode != null) {
                    // 拼接兄弟节点的信息，格式为 "\t(子节点信息)\n"
                    treeStr.append("\t(").append(childnode).append(")\n");
                    // 将兄弟节点加入队列
                    queue.add(childnode);
                    // 获取下一个兄弟节点
                    childnode = (RegexTreeNode) childnode.getNextSibling();
                }
            }
            // 从队列中取出下一个节点
            node = queue.poll();
        }
        // 用于构建最终的输出字符串
        StringBuilder str = new StringBuilder();
        // 拼接前缀信息和语法树信息
        str.append("The regex tree:\n").append(treeStr);
        // 返回最终的字符串表示
        return str.toString();
    }

    /**
     * 导出正则表达式语法树为 JSON 字符串。
     * 目前该方法仅返回空字符串，需要后续实现具体的 JSON 转换逻辑。
     *
     * @return 表示正则表达式语法树的 JSON 字符串，当前实现返回空字符串。
     */
    public String export(){
        // 存储导出的 JSON 字符串，目前为空
        String treeJson="";
        return treeJson;
    }
}