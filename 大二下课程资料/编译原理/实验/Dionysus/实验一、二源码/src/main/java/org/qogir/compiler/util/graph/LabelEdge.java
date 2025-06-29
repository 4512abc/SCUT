package org.qogir.compiler.util.graph;

import java.io.Serial;
import java.io.Serializable;

/**
 * LabelEdge 类表示带标签的有向边，实现了 Serializable 接口，可进行序列化操作。
 * 每条边包含一个源节点、一个目标节点和一个标签，并且提供了获取和设置这些属性的方法。
 */
public class LabelEdge implements Serializable {
    // 序列化版本号，确保序列化和反序列化过程中类的版本一致性
    @Serial
    private static final long serialVersionUID = 7048748617452671098L;

    // 边的源节点
    private Object source;
    // 边的目标节点
    private Object target;
    // 边的标签
    private Character label;

    /**
     * 构造函数，创建一条带标签的有向边。
     *
     * @param source 边的源节点
     * @param target 边的目标节点
     * @param label 边的标签
     */
    public LabelEdge(Object source, Object target, Character label) {
        this.source = source;
        this.target = target;
        this.label = label;
    }

    /**
     * 获取边的源节点。
     *
     * @return 边的源节点
     */
    public Object getSource(){
        return this.source;
    }

    /**
     * 设置边的源节点。
     * 若传入的节点为 null 或与原源节点类型不同，则设置失败。
     *
     * @param obj 新的源节点
     * @return 若设置成功，返回 true；否则返回 false
     */
    public boolean setSource(Object obj){
        // 若传入节点为 null，设置失败
        if(obj == null)
            return false;
        // 若传入节点与原源节点类型不同，设置失败
        if(obj.getClass() != source.getClass())
            return false;
        // 设置新的源节点
        this.source = obj;
        return true;
    }

    /**
     * 获取边的目标节点。
     *
     * @return 边的目标节点
     */
    public Object getTarget(){
        return this.target;
    }

    /**
     * 设置边的目标节点。
     * 若传入的节点为 null 或与原目标节点类型不同，则设置失败。
     *
     * @param obj 新的目标节点
     * @return 若设置成功，返回 true；否则返回 false
     */
    public boolean setTarget(Object obj){
        // 若传入节点为 null，设置失败
        if(obj == null)
            return false;
        // 若传入节点与原目标节点类型不同，设置失败
        if(obj.getClass() != target.getClass())
            return false;
        // 设置新的目标节点
        this.target = obj;
        return true;
    }

    /**
     * 获取边的标签。
     *
     * @return 边的标签
     */
    public Character getLabel(){
        return this.label;
    }

    /**
     * 设置边的标签。
     *
     * @param l 新的标签
     * @return 总是返回 true，表示设置成功
     */
    public boolean setLabel(Character l){
        this.label = l;
        return true;
    }

    /**
     * 计算边对象的哈希码。
     * 哈希码的计算基于边的源节点、目标节点和标签。
     *
     * @return 边对象的哈希码
     */
    @Override
    public int hashCode(){
        int result = 1;
        final int prime = 31;
        // 结合源节点的哈希码计算
        result = prime + result + ((this.source == null) ? 0 : this.source.hashCode());
        // 结合目标节点的哈希码计算
        result = prime + result + ((this.target == null) ? 0 : this.target.hashCode());
        // 结合标签的哈希码计算
        result = prime + result + ((this.label == null) ? 0 : this.label.hashCode());
        return result;
    }

    /**
     * 判断当前边对象是否与另一个对象相等。
     * 当另一个对象为 null、类型不同或源节点、目标节点、标签不匹配时，返回 false；否则返回 true。
     *
     * @param obj 要比较的对象
     * @return 若相等，返回 true；否则返回 false
     */
    public boolean equals(Object obj){
        // 若比较对象为 null，返回 false
        if(obj == null)
            return false;
        // 若两个对象引用相同，返回 true
        if(this == obj)
            return true;
        // 若比较对象类型不同，返回 false
        if(obj.getClass() != this.getClass())
            return false;
        // 若源节点不相等，返回 false
        if(!((LabelEdge)obj).getSource().equals(this.source))
            return false;
        // 若目标节点不相等，返回 false
        if(!((LabelEdge)obj).getTarget().equals(this.target))
            return false;
        // 比较标签是否相等
        return ((LabelEdge)obj).getLabel().equals(this.label);
    }

    /**
     * 将边对象转换为字符串表示。
     * 格式为 "源节点->目标节点@标签"。
     *
     * @return 边对象的字符串表示
     */
    @Override
    public String toString() {
        return this.source.toString() + "->" + this.target.toString() + "@" + this.label;
    }
}