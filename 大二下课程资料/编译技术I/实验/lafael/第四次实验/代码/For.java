package inter;

import symbols.Type;

public class For extends Stmt {
	Expr expr; Stmt stmt1; Stmt stmt2; Stmt stmt3; 
	
	public For() { expr = null; stmt1 = null; stmt2 = null; stmt3 = null; }
	
	public void init(Stmt s1, Expr x, Stmt s2, Stmt s3) {
		expr = x; stmt1 = s1; stmt2 = s2; stmt3 = s3;
		if( expr.type != Type.Bool ) expr.error("boolean required in do");
	}
	
	public void gen(int b, int a) {
		//add your implementation
		int label1=newlabel();
        int label2=newlabel();
        int label3=newlabel();
        stmt1.gen(b,label1);
        after=a;
        emitlabel(label1);
        expr.jumping(0,a);
        emitlabel(label2);stmt3.gen(label2,label3);
        emitlabel(label3);stmt2.gen(label3,label1);
        emit("goto L"+label1);
	}

}
