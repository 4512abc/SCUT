package lexer;

import java.io.IOException;
import java.io.Reader;
import java.util.Hashtable;

import symbols.Type;

// 词法分析器类，负责将输入流转换为Token序列
public class Lexer {
	public static int line = 1;  // 当前行号，用于错误定位
	char peek = ' ';  // 当前读取的字符
	Hashtable words = new Hashtable();  // 存储保留字和标识符的哈希表
	Reader reader = null;  // 输入流读取器

	// 将保留字存入哈希表
	void reserve(Word w) { words.put(w.lexeme, w); }

	// 构造函数，初始化保留字表
	public Lexer(Reader r) {
		// 添加控制流关键字
		reserve(new Word("if", Tag.IF));
		reserve(new Word("else", Tag.ELSE));
		reserve(new Word("while", Tag.WHILE));
		reserve(new Word("do", Tag.DO));
		reserve(new Word("break", Tag.BREAK));
		reserve(new Word("for", Tag.FOR));

		// 添加布尔常量
		reserve(Word.True); reserve(Word.False);

		// 添加类型关键字
		reserve(Type.Int); reserve(Type.Char);
		reserve(Type.Bool); reserve(Type.Float);

		reader = r;  // 设置输入流
	}

	// 读取下一个字符
	void readch() throws IOException {
		peek = (char)reader.read();
	}

	// 读取并检查特定字符
	boolean readch(char c) throws IOException {
		readch();
		if(peek != c) return false;
		peek = ' ';  // 匹配成功则清空peek
		return true;
	}

	// 核心扫描方法，返回下一个Token
	public Token scan() throws IOException {
		// 跳过空白字符
		for(;; readch()) {
			if(peek == ' ' || peek == '\t' || peek == '\r') continue;
			else if(peek == '\n') line = line + 1;  // 换行时增加行号
			else break;
		}

		// 处理双字符操作符
		switch(peek) {
			case '&':
				if(readch('&')) return Word.and; else return new Token('&');
			case '|':
				if(readch('|')) return Word.or; else return new Token('|');
			case '=':
				if(readch('=')) return Word.eq; else return new Token('=');
			case '!':
				if(readch('=')) return Word.ne; else return new Token('!');
			case '<':
				if(readch('=')) return Word.le; else return new Token('<');
			case '>':
				if(readch('=')) return Word.ge; else return new Token('>');
		}

		// 处理数字常量(整数和浮点数)
		if(Character.isDigit(peek)) {
			int v = 0;
			do {
				v = 10*v + Character.digit(peek, 10);
				readch();
			} while(Character.isDigit(peek));

			if(peek != '.') return new Num(v);  // 整数

			// 处理浮点数部分
			float x = v; float d = 10;
			for(;;) {
				readch();
				if(!Character.isDigit(peek)) break;
				x = x + Character.digit(peek, 10)/d;
				d = d*10;
			}
			return new Real(x);
		}

		// 处理标识符和保留字
		if(Character.isLetter(peek)) {
			StringBuffer b = new StringBuffer();
			do {
				b.append(peek);
				readch();
			} while(Character.isLetterOrDigit(peek));

			String s = b.toString();
			Word w = (Word)words.get(s);
			if(w != null) return w;  // 返回保留字

			w = new Word(s, Tag.ID);  // 新建标识符
			words.put(s, w);
			return w;
		}

		// 其他单字符Token
		Token tok = new Token(peek);
		peek = ' ';  // 重置peek
		return tok;
	}
}