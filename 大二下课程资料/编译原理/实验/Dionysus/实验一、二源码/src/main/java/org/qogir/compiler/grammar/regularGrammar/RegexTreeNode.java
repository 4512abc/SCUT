package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.util.tree.DefaultTreeNode;

import java.io.Serial;

/**
 * RegexTreeNode 类继承自 DefaultTreeNode，用于表示正则表达式语法树的节点。
 * 每个节点包含一个值和一个类型，类型用于标识节点所代表的正则表达式元素。
 */
public class RegexTreeNode extends DefaultTreeNode {
    // 序列化版本号，确保序列化和反序列化过程中类的版本一致性
    @Serial
    private static final long serialVersionUID = 8199272493386097880L;
    // 节点的值，通常为正则表达式中的字符
    private Character value;
    // 节点的类型，含义如下：
    // 0 - 基本字符（如字母、ε）
    // 1 - 连接操作
    // 2 - 并集操作
    // 3 - Kleene 闭包操作
    // 4 - 左括号
    // 5 - 右括号
    private int type;

    /**
     * 构造函数，创建一个正则表达式树节点。
     * @param ch 节点的值，为一个字符。
     * @param t 节点的类型，使用预定义的整数常量表示。
     */
    public RegexTreeNode(Character ch, int t){
        super();
        this.value = ch;
        this.type = t;
    }

    /**
     * 构造函数，创建一个带有子节点和兄弟节点的正则表达式树节点。
     * @param v 节点的值，为一个字符。
     * @param type 节点的类型，使用预定义的整数常量表示。
     * @param firstChild 该节点的第一个子节点。
     * @param nextSibling 该节点的下一个兄弟节点。
     */
    public RegexTreeNode(char v, int type, RegexTreeNode firstChild, RegexTreeNode nextSibling){
        super(firstChild, nextSibling);
        this.value = v;
        this.type = type;
    }

    /**
     * 设置节点的类型。
     * @param type 节点的新类型，使用预定义的整数常量表示。
     */
    public void setType(int type) {
        this.type = type;
    }

    /**
     * 设置节点的值。
     * @param value 节点的新值，为一个字符。
     */
    public void setValue(Character value) {
        this.value = value;
    }

    /**
     * 获取节点的值。
     * @return 节点的值，为一个字符。
     */
    public Character getValue() {
        return value;
    }

    /**
     * 获取节点的类型。
     * @return 节点的类型，使用预定义的整数常量表示。
     */
    public int getType() {
        return type;
    }

    /**
     * 获取该节点的最后一个子节点。
     * 从第一个子节点开始，通过遍历兄弟节点找到最后一个子节点。
     * @return 最后一个子节点，如果没有子节点则返回 null。
     */
    public RegexTreeNode getLastChild(){
        // 获取第一个子节点并转换为 RegexTreeNode 类型
        RegexTreeNode theNode = (RegexTreeNode) this.getFirstChild();
        // 如果第一个子节点不为空
        if(theNode != null) {
            // 当当前节点存在下一个兄弟节点时，继续遍历
            while (theNode.getNextSibling() != null) {
                // 将当前节点更新为下一个兄弟节点
                theNode = (RegexTreeNode) theNode.getNextSibling();
            }
        }
        return theNode;
    }

    /**
     * 将节点信息转换为字符串表示。
     * 格式为 "节点值:节点类型"。
     * @return 包含节点值和类型的字符串。
     */
    @Override
    public String toString() {
        return this.value + ":" + this.type;
    }
}