package inter;

import symbols.Type;
import lexer.Word;

public class Id extends Expr {
	
	public int offset;
	public Id(Word id, Type p, int b) { super(id,p); offset=b; }
}
