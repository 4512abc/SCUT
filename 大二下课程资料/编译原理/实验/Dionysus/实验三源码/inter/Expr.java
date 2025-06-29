package inter;

import symbols.Type;
import lexer.Token;

public class Expr extends Node{

	public Token op;
	public Type type;
	
	Expr(Token tok, Type p) { op = tok; type = p; }
	
	public Expr gen() { return this;}
	public Expr reduce() { return this;}
	
	public void jumping(int t, int f) {}
	
	public void emitjumps(String test, int t, int f){}
	public String toString() { return op.toString(); }
	
}
