package lexer;

import java.io.IOException;
import java.io.Reader;
import java.util.Hashtable;

import symbols.Type;

/**
 * 词法分析器（Lexer）：将字符流转换为 Token（记号）流
 */
public class Lexer {
	public static int line = 1;  // 当前行号，默认从第 1 行开始
	char peek = ' ';             // 当前读取的字符
	Hashtable words = new Hashtable();  // 保留字表，用于识别关键字
	Reader reader = null;       // 输入流读取器

	// 将保留字放入哈希表中
	void reserve(Word w) {
		words.put(w.lexeme, w);
	}

	// 构造方法，初始化关键字和类型
	public Lexer(Reader r) {
		// 保留关键字
		reserve(new Word("if", Tag.IF));
		reserve(new Word("else", Tag.ELSE));
		reserve(new Word("while", Tag.WHILE));
		reserve(new Word("do", Tag.DO));
		reserve(new Word("break", Tag.BREAK));
		reserve(new Word("for", Tag.FOR));

		// 布尔值常量
		reserve(Word.True);
		reserve(Word.False);

		// 基本数据类型
		reserve(Type.Int);
		reserve(Type.Char);
		reserve(Type.Bool);
		reserve(Type.Float);

		reader = r;  // 绑定输入流
	}

	// 读取下一个字符
	void readch() throws IOException {
		peek = (char) reader.read();
	}

	// 读取下一个字符并判断是否是目标字符 c
	boolean readch(char c) throws IOException {
		readch();
		if (peek != c) return false;
		peek = ' ';
		return true;
	}

	// 扫描输入，返回下一个 Token
	public Token scan() throws IOException {
		// 跳过空白字符、制表符和回车
		for (;; readch()) {
			if (peek == ' ' || peek == '\t' || peek == '\r') continue;
			else if (peek == '\n') line = line + 1;  // 换行计数
			else break;
		}

		// 处理复合运算符，如 &&、||、==、!=、<=、>=
		switch (peek) {
			case '&':
				if (readch('&')) return Word.and; else return new Token('&');
			case '|':
				if (readch('|')) return Word.or; else return new Token('|');
			case '=':
				if (readch('=')) return Word.eq; else return new Token('=');
			case '!':
				if (readch('=')) return Word.ne; else return new Token('!');
			case '<':
				if (readch('=')) return Word.le; else return new Token('<');
			case '>':
				if (readch('=')) return Word.ge; else return new Token('>');
		}

		// 处理数字：整数和浮点数
		if (Character.isDigit(peek)) {
			int v = 0;
			do {
				v = 10 * v + Character.digit(peek, 10);
				readch();
			} while (Character.isDigit(peek));

			// 不是浮点数
			if (peek != '.') return new Num(v);

			// 是浮点数
			float x = v, d = 10;
			for (;;) {
				readch();
				if (!Character.isDigit(peek)) break;
				x = x + Character.digit(peek, 10) / d;
				d = d * 10;
			}
			return new Real(x);
		}

		// 处理标识符（变量名）或保留字
		if (Character.isLetter(peek)) {
			StringBuffer b = new StringBuffer();
			do {
				b.append(peek);
				readch();
			} while (Character.isLetterOrDigit(peek));  // 支持字母和数字

			String s = b.toString();
			Word w = (Word) words.get(s);
			if (w != null) return w;        // 是保留字
			w = new Word(s, Tag.ID);        // 是用户定义标识符
			words.put(s, w);                // 存入保留字表
			return w;
		}

		// 其他符号（如分号、括号、加号等），直接构造 Token
		Token tok = new Token(peek);
		peek = ' ';
		return tok;
	}
}
