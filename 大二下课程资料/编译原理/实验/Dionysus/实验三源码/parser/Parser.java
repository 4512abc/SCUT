package parser;

import inter.Access;
import inter.And;
import inter.Arith;
import inter.Break;
import inter.Constant;
import inter.Do;
import inter.Else;
import inter.Expr;
import inter.For;
import inter.Id;
import inter.If;
import inter.Not;
import inter.Or;
import inter.Rel;
import inter.Seq;
import inter.Set;
import inter.SetElem;
import inter.Stmt;
import inter.Unary;
import inter.While;

import java.io.IOException;

import symbols.Array;
import symbols.Env;
import symbols.Type;
import lexer.Lexer;
import lexer.Tag;
import lexer.Token;
import lexer.Word;
import lexer.Num;

// 语法分析器类，负责将Token序列转换为语法树
public class Parser {

	private Lexer lex;    // 词法分析器实例
	private Token look;   // 当前lookahead token
	Env top = null;       // 当前符号表环境(作用域)
	int used = 0;         // 内存分配计数器

	// 构造函数，初始化词法分析器并读取第一个token
	public Parser(Lexer l) throws IOException { lex = l; move(); }

	// 读取下一个token
	void move() throws IOException { look = lex.scan(); }

	// 错误处理，输出错误位置和消息
	void error(String s) { throw new Error("near line "+lex.line+": "+s); }

	// 匹配当前token并前进
	void match(int t) throws IOException {
		if( look.tag == t ) move();
		else error("syntax error");
	}

	// 程序入口，解析整个程序
	public void program() throws IOException {
		Stmt s = block();  // 解析程序块
		s.display();       // 显示生成的语法树
	}

	// 解析代码块 { ... }
	Stmt block() throws IOException {
		match('{');
		Env savedEnv = top;  // 保存当前环境
		top = new Env(top);  // 创建新的作用域
		decls();             // 解析声明部分
		Stmt s = stmts();    // 解析语句部分
		match('}');
		top = savedEnv;      // 恢复之前的环境
		return s;
	}

	// 解析变量声明 (可递归)
	void decls() throws IOException {
		while( look.tag == Tag.BASIC ) {   // 基础类型声明
			Type p = type();               // 获取类型
			Token tok = look;
			match(Tag.ID);                 // 匹配标识符
			match(';');
			Id id = new Id((Word)tok, p, used);  // 创建标识符节点
			top.put(tok, id);              // 加入符号表
			used = used + p.width;         // 更新内存偏移
		}
	}

	// 解析类型 (基础类型或数组类型)
	Type type() throws IOException {
		Type p = (Type)look;      // 获取基础类型
		match(Tag.BASIC);
		if( look.tag != '[' ) return p;  // 非数组类型
		else return dims(p);             // 数组类型
	}

	// 解析数组维度
	Type dims(Type p) throws IOException {
		match('[');
		Token tok = look;
		match(Tag.NUM);  // 数组大小
		match(']');
		if( look.tag == '[' )  // 多维数组
			p = dims(p);
		return new Array(((Num)tok).value, p);  // 创建数组类型
	}

	// 解析语句序列
	Stmt stmts() throws IOException {
		if ( look.tag == '}' ) return Stmt.Null;  // 空语句序列
		else return new Seq(stmt(), stmts());     // 构建语句序列节点
	}

	// 解析单条语句
	Stmt stmt() throws IOException {
		Expr x; Stmt s, s1, s2;
		Stmt savedStmt;  // 用于保存循环上下文(break使用)

		switch( look.tag ) {
			case ';':        // 空语句
				move();
				return Stmt.Null;

			case Tag.IF:     // if语句
				match(Tag.IF);
				match('(');
				x = bool();  // 条件表达式
				match(')');
				s1 = stmt(); // then部分
				if( look.tag != Tag.ELSE ) return new If(x, s1);
				match(Tag.ELSE);
				s2 = stmt(); // else部分
				return new Else(x, s1, s2);

			case Tag.WHILE:  // while循环
				While whilenode = new While();
				savedStmt = Stmt.Enclosing;
				Stmt.Enclosing = whilenode;  // 设置当前循环上下文
				match(Tag.WHILE);
				match('(');
				x = bool();  // 循环条件
				match(')');
				s1 = stmt(); // 循环体
				whilenode.init(x, s1);
				Stmt.Enclosing = savedStmt;  // 恢复上下文
				return whilenode;

			case Tag.DO:     // do-while循环
				Do donode = new Do();
				savedStmt = Stmt.Enclosing;
				Stmt.Enclosing = donode;
				match(Tag.DO);
				s1 = stmt(); // 循环体
				match(Tag.WHILE);
				match('(');
				x = bool();  // 循环条件
				match(')');
				match(';');
				donode.init(s1, x);
				Stmt.Enclosing = savedStmt;
				return donode;

			case Tag.FOR:    // for循环
				For fornode = new For();
				savedStmt = Stmt.Enclosing;
				Stmt.Enclosing = fornode;
				match(Tag.FOR);
				match('(');
				s1 = forassign();  // 初始化语句
				match(';');
				x = bool();        // 循环条件
				match(';');
				s2 = forassign();  // 迭代语句
				match(')');
				s = stmt();        // 循环体
				fornode.init(s1, x, s2, s);
				Stmt.Enclosing = savedStmt;
				return fornode;

			case Tag.BREAK:  // break语句
				match(Tag.BREAK);
				match(';');
				return new Break();

			case '{':        // 代码块
				return block();

			default:         // 赋值语句
				return assign();
		}
	}

	// 解析for循环的赋值部分(初始化或迭代)
	Stmt forassign() throws IOException {
		Stmt stmt;
		Token t = look;
		match(Tag.ID);
		Id id = top.get(t);
		if( id == null ) error(t.toString() + " undeclared");

		if( look.tag == '=' ) {  // 简单赋值 id = E
			move();
			stmt = new Set(id, bool());
		}
		else {                   // 数组元素赋值 L = E
			Access x = offset(id);
			match('=');
			stmt = new SetElem(x, bool());
		}
		return stmt;
	}

	// 解析赋值语句
	Stmt assign() throws IOException {
		Stmt stmt = forassign();
		match(';');
		return stmt;
	}

	// 以下为表达式解析方法(递归下降) ----------------------

	// 解析布尔表达式(OR)
	Expr bool() throws IOException {
		Expr x = join();
		while( look.tag == Tag.OR ) {
			Token tok = look;
			move();
			x = new Or(tok, x, join());
		}
		return x;
	}

	// 解析布尔表达式(AND)
	Expr join() throws IOException {
		Expr x = equality();
		while( look.tag == Tag.AND ) {
			Token tok = look;
			move();
			x = new And(tok, x, equality());
		}
		return x;
	}

	// 解析相等性表达式(==, !=)
	Expr equality() throws IOException {
		Expr x = rel();
		while( look.tag == Tag.EQ || look.tag == Tag.NE ) {
			Token tok = look;
			move();
			x = new Rel(tok, x, rel());
		}
		return x;
	}

	// 解析关系表达式(<, <=, >, >=)
	Expr rel() throws IOException {
		Expr x = expr();
		switch( look.tag ) {
			case '<': case Tag.LE: case Tag.GE: case '>':
				Token tok = look;
				move();
				return new Rel(tok, x, expr());
			default:
				return x;
		}
	}

	// 解析算术表达式(+, -)
	Expr expr() throws IOException {
		Expr x = term();
		while( look.tag == '+' || look.tag == '-' ) {
			Token tok = look;
			move();
			x = new Arith(tok, x, term());
		}
		return x;
	}

	// 解析算术项(*, /)
	Expr term() throws IOException {
		Expr x = unary();
		while(look.tag == '*' || look.tag == '/' ) {
			Token tok = look;
			move();
			x = new Arith(tok, x, unary());
		}
		return x;
	}

	// 解析一元表达式(-, !)
	Expr unary() throws IOException {
		if( look.tag == '-' ) {
			move();
			return new Unary(Word.minus, unary());
		}
		else if( look.tag == '!' ) {
			Token tok = look;
			move();
			return new Not(tok, unary());
		}
		else return factor();
	}

	// 解析基本因子(常量、标识符、数组访问、括号表达式)
	Expr factor() throws IOException {
		Expr x = null;
		switch( look.tag ) {
			case '(':  // 括号表达式
				move();
				x = bool();
				match(')');
				return x;
			case Tag.NUM:    // 整型常量
				x = new Constant(look, Type.Int);
				move();
				return x;
			case Tag.REAL:   // 浮点常量
				x = new Constant(look, Type.Float);
				move();
				return x;
			case Tag.TRUE:   // 布尔常量true
				x = Constant.True;
				move();
				return x;
			case Tag.FALSE:  // 布尔常量false
				x = Constant.False;
				move();
				return x;
			case Tag.ID:     // 标识符或数组访问
				String s = look.toString();
				Id id = top.get(look);
				if( id == null ) error(look.toString() + " undeclared");
				move();
				if( look.tag != '[' ) return id;  // 简单变量
				else return offset(id);           // 数组访问
			default:
				error("syntax error");
				return x;
		}
	}

	// 解析数组访问(多维)
	Access offset(Id a) throws IOException {
		Expr i, w, t1, t2, loc;
		Type type = a.type;
		match('[');
		i = bool();  // 数组索引
		match(']');
		type = ((Array)type).of;  // 元素类型
		w = new Constant(type.width);  // 元素大小
		t1 = new Arith(new Token('*'), i, w);  // 计算偏移量
		loc = t1;
		while( look.tag == '[' ) {  // 处理多维数组
			match('[');
			i = bool();
			match(']');
			type = ((Array)type).of;
			w = new Constant(type.width);
			t1 = new Arith(new Token('*'), i, w);
			t2 = new Arith(new Token('+'), loc, t1);
			loc = t2;
		}
		return new Access(a, loc, type);  // 返回数组访问节点
	}
}