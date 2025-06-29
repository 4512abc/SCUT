package org.qogir.compiler.FA;

import java.io.Serial;
import java.io.Serializable;
//import org.jetbrains.annotations.NotNull;

/**
 * State 类表示有限自动机中的一个状态，实现了 Serializable 接口，可进行序列化操作。
 */
public class State implements Serializable {

    // 序列化版本号，确保序列化和反序列化过程中类的版本一致性
    @Serial
    private static final long serialVersionUID = 3706097164927205436L;

    // 静态变量，用于为每个新创建的状态分配唯一的 ID
    public static int STATE_ID = 0;

    /**
     * 每个状态都有一个唯一的 ID，该 ID 一旦创建就不能被修改。
     */
    private final int id; // 状态的唯一 ID

    /**
     * 每个状态都有一个 sid（显示 ID），可以被重新赋值，主要用于显示目的。
     */
    private String sid;

    /**
     * 当前支持四种类型的状态：
     * 0 - 起始状态；
     * 1 - 中间状态
     * 2 - 接受状态；
     * 20 - 既是起始状态又是接受状态。
     */
    public static final int START = 0;
    public static final int MIDDLE = 1;
    public static final int ACCEPT = 2;
    public static final int ACCEPTANDSTART = 20;
    // 状态的类型，默认为中间状态
    private int type = MIDDLE;

    /**
     * 默认构造函数，创建一个新的状态。
     * 为状态分配一个唯一的 ID 和显示 ID，并将全局的 STATE_ID 加 1。
     */
    public State(){
        // 为当前状态分配全局的 STATE_ID
        this.id = State.STATE_ID;
        // 将状态的显示 ID 设置为其唯一 ID 的字符串形式
        this.sid = String.valueOf(this.id);
        // 全局的 STATE_ID 加 1，以便下一个状态获得不同的 ID
        STATE_ID += 1 ;
    }

    /**
     * 复制构造函数，根据另一个状态对象创建一个新的状态。
     * 新状态的 ID、类型和显示 ID 与传入的状态对象相同。
     *
     * @param s 用于复制属性的状态对象
     */
    public State( State s){//@NotNull
        // 复制传入状态的唯一 ID
        this.id = s.getId();
        // 复制传入状态的类型
        this.type = s.getType();
        // 复制传入状态的显示 ID
        this.sid = s.getSid();
    }

    /**
     * 构造函数，创建一个指定类型的新状态。
     * 为状态分配一个唯一的 ID 和显示 ID，并将全局的 STATE_ID 加 1。
     *
     * @param type 状态的类型，使用类中定义的静态常量
     */
    State(int type){
        // 为当前状态分配全局的 STATE_ID
        this.id = State.STATE_ID;
        // 将状态的显示 ID 设置为其唯一 ID 的字符串形式
        this.sid = String.valueOf(this.id);
        // 设置状态的类型
        this.type = type;
        // 全局的 STATE_ID 加 1，以便下一个状态获得不同的 ID
        STATE_ID += 1 ;
    }

    /**
     * 获取状态的唯一 ID。
     *
     * @return 状态的唯一 ID
     */
    public int getId() {
        return id;
    }

    /**
     * 获取状态的类型。
     *
     * @return 状态的类型，对应类中定义的静态常量
     */
    public int getType() {
        return type;
    }

    /**
     * 设置状态的显示 ID。
     *
     * @param sid 新的显示 ID
     */
    public void setSid(String sid){
        this.sid = sid;
    }

    /**
     * 获取状态的显示 ID。
     *
     * @return 状态的显示 ID
     */
    public String getSid() {
        return sid;
    }

    /**
     * 设置状态的类型。
     *
     * @param type 新的状态类型，使用类中定义的静态常量
     */
    public void setType(int type) {
        this.type = type;
    }

    /**
     * 判断当前状态是否与另一个状态相等。
     * 当两个状态的唯一 ID 和类型都相同时，认为它们相等。
     *
     * @param s 用于比较的另一个状态对象
     * @return 如果两个状态相等则返回 true，否则返回 false
     */
    public boolean equals( State s){//@NotNull
        return this.id == s.getId() && this.type == s.getType();
    }

    /**
     * 将状态对象转换为字符串表示形式。
     * 字符串格式为 "唯一 ID:类型"。
     *
     * @return 状态的字符串表示
     */
    @Override
    public String toString() {
        return this.id + ":" + this.type;
    }
}