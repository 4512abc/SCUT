package org.qogir.compiler.util.tree;

import java.io.Serial;
import java.io.Serializable;

/**
 * DefaultTree 类表示一个通用的树结构，实现了 Serializable 接口，可进行序列化操作。
 * 该类提供了树的基本结构，包含一个根节点，并且提供了获取和设置根节点的方法。
 *
 * @param <N> 树节点的类型
 */
public class DefaultTree<N> implements Serializable {
    // 序列化版本号，确保序列化和反序列化过程中类的版本一致性
    @Serial
    private static final long serialVersionUID = 2002054322029286840L;

    // 树的根节点
    protected N root;

    /**
     * 默认构造函数，初始化一个空树，根节点为 null。
     */
    public DefaultTree(){
        this.root = null;
    }

    /**
     * 带参数的构造函数，使用传入的节点作为树的根节点。
     *
     * @param rt 树的根节点
     */
    public DefaultTree(N rt){
        this.root = rt;
    }

    /**
     * 获取树的根节点。
     *
     * @return 树的根节点
     */
    public N getRoot() {
        return root;
    }

    /**
     * 设置树的根节点。
     *
     * @param root 新的根节点
     */
    public void setRoot(N root) {
        this.root = root;
    }
}