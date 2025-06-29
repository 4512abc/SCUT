package inter;

public class Break extends Stmt {
   Stmt stmt;

   public Break() {
      if( Stmt.Enclosing == Stmt.Null ) error("unenclosed break");
      stmt = Stmt.Enclosing;
   }

   public void gen(int b, int a) {}
   
   public void display(){
	   emit(" break ");
   }
}
