package inter;

import lexer.Token;

public class Or extends Logical {

   public Or(Token tok, Expr x1, Expr x2) { super(tok, x1, x2); }

   public void jumping(int t, int f) {}
}
