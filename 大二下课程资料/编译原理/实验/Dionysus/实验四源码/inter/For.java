package inter;

import symbols.Type;

/**
 * 表示一个 for 语句节点（中间代码生成器部分）
 * 格式类似：for (stmt1; expr; stmt2) stmt3;
 */
public class For extends Stmt {
    Expr expr;         // for 循环的条件表达式
    Stmt stmt1;        // 初始化语句
    Stmt stmt2;        // 每次循环结束后的递增语句
    Stmt stmt3;        // 循环体

    // 构造函数：初始化为 null
    public For() {
        expr = null;
        stmt1 = null;
        stmt2 = null;
        stmt3 = null;
    }

    /**
     * 初始化 for 循环的四个部分：
     * @param s1 初始化语句（stmt1）
     * @param x  条件表达式（expr）
     * @param s2 增量语句（stmt2）
     * @param s3 循环体（stmt3）
     */
    public void init(Stmt s1, Expr x, Stmt s2, Stmt s3) {
        expr = x;
        stmt1 = s1;
        stmt2 = s2;
        stmt3 = s3;

        // 检查条件表达式是否为布尔类型
        if (expr.type != Type.Bool)
            expr.error("boolean required in do");
    }

    /**
     * 生成中间代码（四元式）：
     * b - 循环开始前的位置
     * a - 循环结束后的位置（出口）
     */
    public void gen(int b, int a) {
        int label1 = newlabel(); // 条件判断的标签
        int label2 = newlabel(); // 循环体标签
        int label3 = newlabel(); // 增量语句标签

        // 先生成初始化语句
        stmt1.gen(b, label1); // 初始语句执行后跳转到 label1（条件判断）

        after = a;  // 设置退出标签（用于 break）

        emitlabel(label1);         // 条件判断开始
        expr.jumping(0, a);        // 如果条件为 false 跳转到循环后

        emitlabel(label2);         // 循环体开始
        stmt3.gen(label2, label3); // 生成循环体代码

        emitlabel(label3);         // 增量语句
        stmt2.gen(label3, label1); // 增量语句后跳回条件判断

        emit("goto L" + label1);   // 显式回到条件判断
    }
}
