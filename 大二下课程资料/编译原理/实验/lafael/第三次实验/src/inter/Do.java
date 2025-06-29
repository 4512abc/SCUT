package inter;

import symbols.Type;

public class Do extends Stmt {

   Expr expr; Stmt stmt;

   public Do() { expr = null; stmt = null; }

   public void init(Stmt s, Expr x) {
      expr = x; stmt = s;
      if( expr.type != Type.Bool ) expr.error("boolean required in do");
   }

   public void gen(int b, int a) {}
   
   public void display(){
	  emit("stmt : do begin");
	  stmt.display();
	  //expr.jumping(b,0);
	  emit("stmt : do end");
   }
}