package parser;

// 引入语法树中间表示相关类
import inter.*;
// 引入符号表相关类
import symbols.*;
// 引入词法分析相关类
import lexer.*;

import java.io.IOException;

public class Parser {

	private Lexer lex;    // 词法分析器
	private Token look;   // 当前词法单元（向前看一个 token）
	Env top = null;       // 当前作用域的符号表（链表结构）
	int used = 0;         // 当前使用的存储空间，用于变量地址分配

	// 构造函数：传入词法分析器并读取第一个 token
	public Parser(Lexer l) throws IOException {
		lex = l;
		move();
	}

	// 读取下一个词法单元
	void move() throws IOException {
		look = lex.scan();
	}

	// 报错函数，抛出语法错误信息
	void error(String s) {
		throw new Error("near line " + lex.line + ": " + s);
	}

	// 匹配当前 token 的 tag，如果匹配则读取下一个，否则报错
	void match(int t) throws IOException {
		if (look.tag == t) move();
		else error("syntax error");
	}

	// program -> block
	public void program() throws IOException {
		Stmt s = block();             // 分析程序主体块
		int begin = s.newlabel();     // 创建开始标签
		int after = s.newlabel();     // 创建结束标签
		s.emitlabel(begin);           // 输出开始标签
		s.gen(begin, after);          // 生成中间代码
		s.emitlabel(after);           // 输出结束标签
	}

	// block -> { decls stmts }
	Stmt block() throws IOException {
		match('{');
		Env savedEnv = top;          // 保存当前作用域
		top = new Env(top);          // 创建新作用域
		decls();                     // 分析声明
		Stmt s = stmts();            // 分析语句
		match('}');
		top = savedEnv;              // 恢复旧作用域
		return s;
	}

	// decls -> (type ID ;)*
	void decls() throws IOException {
		while (look.tag == Tag.BASIC) {
			Type p = type();                     // 获取类型
			Token tok = look;
			match(Tag.ID); match(';');
			Id id = new Id((Word) tok, p, used); // 创建变量符号
			top.put(tok, id);                    // 加入符号表
			used = used + p.width;               // 更新存储空间使用
		}
	}

	// type -> basic | basic dims
	Type type() throws IOException {
		Type p = (Type) look;
		match(Tag.BASIC);
		if (look.tag != '[') return p;  // 非数组
		else return dims(p);            // 是数组类型
	}

	// dims -> [num] (dims)?
	Type dims(Type p) throws IOException {
		match('[');
		Token tok = look;
		match(Tag.NUM);
		match(']');
		if (look.tag == '[') p = dims(p);
		return new Array(((Num) tok).value, p);  // 构造数组类型
	}

	// stmts -> stmt stmts | ε
	Stmt stmts() throws IOException {
		if (look.tag == '}') return Stmt.Null;
		else return new Seq(stmt(), stmts());
	}

	// stmt -> 多种语句类型
	Stmt stmt() throws IOException {
		Expr x;
		Stmt s, s1, s2;
		Stmt savedStmt;

		switch (look.tag) {
			case ';':
				move();
				return Stmt.Null;

			case Tag.IF:
				match(Tag.IF); match('('); x = bool(); match(')');
				s1 = stmt();
				if (look.tag != Tag.ELSE) return new If(x, s1);
				match(Tag.ELSE);
				s2 = stmt();
				return new Else(x, s1, s2);

			case Tag.WHILE:
				While whilenode = new While();
				savedStmt = Stmt.Enclosing;
				Stmt.Enclosing = whilenode;
				match(Tag.WHILE); match('('); x = bool(); match(')');
				s1 = stmt();
				whilenode.init(x, s1);
				Stmt.Enclosing = savedStmt;
				return whilenode;

			case Tag.DO:
				Do donode = new Do();
				savedStmt = Stmt.Enclosing;
				Stmt.Enclosing = donode;
				match(Tag.DO);
				s1 = stmt();
				match(Tag.WHILE); match('('); x = bool(); match(')'); match(';');
				donode.init(s1, x);
				Stmt.Enclosing = savedStmt;
				return donode;

			case Tag.BREAK:
				match(Tag.BREAK); match(';');
				return new Break();

			case Tag.FOR:
				For fornode = new For();
				savedStmt = Stmt.Enclosing;
				Stmt.Enclosing = fornode;
				match(Tag.FOR); match('(');
				Stmt fors1 = forassign(); match(';');
				Expr forx = bool(); match(';');
				Stmt fors2 = forassign(); match(')');
				Stmt fors3 = stmt();
				fornode.init(fors1, forx, fors2, fors3);
				Stmt.Enclosing = savedStmt;
				return fornode;

			case '{':
				return block();

			default:
				return assign();  // 赋值语句
		}
	}

	// 用于 for 循环中的赋值部分，不带分号
	Stmt forassign() throws IOException {
		Stmt stmt;
		Token t = look;
		match(Tag.ID);
		Id id = top.get(t);
		if (id == null) error(t.toString() + " undeclared");

		if (look.tag == '=') {
			move();
			stmt = new Set(id, bool());
		} else {
			Access x = offset(id);
			match('=');
			stmt = new SetElem(x, bool());
		}
		return stmt;
	}

	// 普通赋值语句，带分号
	Stmt assign() throws IOException {
		Stmt stmt;
		Token t = look;
		match(Tag.ID);
		Id id = top.get(t);
		if (id == null) error(t.toString() + " undeclared");

		if (look.tag == '=') {
			move();
			stmt = new Set(id, bool());
		} else {
			Access x = offset(id);
			match('=');
			stmt = new SetElem(x, bool());
		}
		match(';');
		return stmt;
	}

	// bool -> join (|| join)*
	Expr bool() throws IOException {
		Expr x = join();
		while (look.tag == Tag.OR) {
			Token tok = look;
			move();
			x = new Or(tok, x, join());
		}
		return x;
	}

	// join -> equality (&& equality)*
	Expr join() throws IOException {
		Expr x = equality();
		while (look.tag == Tag.AND) {
			Token tok = look;
			move();
			x = new And(tok, x, equality());
		}
		return x;
	}

	// equality -> rel (==|!= rel)*
	Expr equality() throws IOException {
		Expr x = rel();
		while (look.tag == Tag.EQ || look.tag == Tag.NE) {
			Token tok = look;
			move();
			x = new Rel(tok, x, rel());
		}
		return x;
	}

	// rel -> expr ([<|<=|>=|>] expr)?
	Expr rel() throws IOException {
		Expr x = expr();
		switch (look.tag) {
			case '<':
			case Tag.LE:
			case Tag.GE:
			case '>':
				Token tok = look;
				move();
				return new Rel(tok, x, expr());
			default:
				return x;
		}
	}

	// expr -> term ((+|-) term)*
	Expr expr() throws IOException {
		Expr x = term();
		while (look.tag == '+' || look.tag == '-') {
			Token tok = look;
			move();
			x = new Arith(tok, x, term());
		}
		return x;
	}

	// term -> unary ((*|/) unary)*
	Expr term() throws IOException {
		Expr x = unary();
		while (look.tag == '*' || look.tag == '/') {
			Token tok = look;
			move();
			x = new Arith(tok, x, unary());
		}
		return x;
	}

	// unary -> -unary | !unary | factor
	Expr unary() throws IOException {
		if (look.tag == '-') {
			move();
			return new Unary(Word.minus, unary());
		} else if (look.tag == '!') {
			Token tok = look;
			move();
			return new Not(tok, unary());
		} else return factor();
	}

	// factor -> (bool) | num | real | true | false | id | id[expr]...
	Expr factor() throws IOException {
		Expr x = null;
		switch (look.tag) {
			case '(':
				move();
				x = bool();
				match(')');
				return x;
			case Tag.NUM:
				x = new Constant(look, Type.Int);
				move();
				return x;
			case Tag.REAL:
				x = new Constant(look, Type.Float);
				move();
				return x;
			case Tag.TRUE:
				x = Constant.True;
				move();
				return x;
			case Tag.FALSE:
				x = Constant.False;
				move();
				return x;
			case Tag.ID:
				String s = look.toString();
				Id id = top.get(look);
				if (id == null) error(look.toString() + " undeclared");
				move();
				if (look.tag != '[') return id;
				else return offset(id);
			default:
				error("syntax error");
				return x;
		}
	}

	// offset -> [expr] 多维数组访问
	Access offset(Id a) throws IOException {
		Expr i, w, t1, t2, loc;
		Type type = a.type;

		match('['); i = bool(); match(']');
		type = ((Array) type).of;
		w = new Constant(type.width);
		t1 = new Arith(new Token('*'), i, w);
		loc = t1;

		while (look.tag == '[') {
			match('['); i = bool(); match(']');
			type = ((Array) type).of;
			w = new Constant(type.width);
			t1 = new Arith(new Token('*'), i, w);
			t2 = new Arith(new Token('+'), loc, t1);
			loc = t2;
		}

		return new Access(a, loc, type);
	}
}
