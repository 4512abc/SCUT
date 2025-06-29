package inter;

import symbols.Type;

public class For extends Stmt {
	//add your implementation for fields and methods of for-node

	//fields:
	//forexpr
	//forassign1  forassign2  loopstmt ...
	//methods:
	//public For() {
	//}
	//public void init(Stmt forassignstmt1, Expr expr, Stmt forassignstmt2, Stmt bodystmt) {
	//}
	//public void display(){
	//}
	Expr expr; Stmt assign1,assign2,stmt;//对应 for(assign1;expr;assign2) stmt

	public void init(Stmt assign1,Expr expr, Stmt assign2 ,Stmt stmt) {
		this.expr = expr;  this.assign1 = assign1;this.assign2 = assign2;this.stmt = stmt;
		if( expr.type != Type.Bool ) expr.error("boolean required in For");
	}

	public void display() {
		emit("stmt : for begin");
		
		// 输出初始化赋值（调用 Set/SetElem 的 display() 方法）
		emit("initial forassign:");
		assign1.display();  // 假设 assign1 是 Set/SetElem 类型，其 display() 会输出 "assignment"
		
		// 输出增量赋值（调用 Set/SetElem 的 display() 方法）
		emit("incremental forassign:");
		assign2.display();  // 假设 assign2 是 Set/SetElem 类型
		
		// 输出循环体（调用循环体的 display() 方法）
		emit("for loop body:");
		stmt.display();     // 循环体可能是普通语句（如 Set），其 display() 会输出 "assignment"
		
		emit("stmt : for end");
	}

	public void gen(int b, int a) {}

}