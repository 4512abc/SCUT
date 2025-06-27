package symbols;

import lexer.Tag;

public class Array extends Type{
	public Type of;
	public int size = 1;
	public Array(int sz, Type p){
		super("[]", Tag.INDEX, sz*p.width); size = sz; of = p;
	}
	public String toString() { return "["+size+"]"+of.toString(); }
}
