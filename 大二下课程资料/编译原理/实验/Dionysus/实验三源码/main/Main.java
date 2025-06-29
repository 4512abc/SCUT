package main;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

import parser.Parser;
import lexer.Lexer;

public class Main {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		File file = new File("F:/A1学校相关文件/大二/编译原理/实验/实验三源码/6-Decaf语言语法分析测试例1-decaftest3-1 (1).txt");
//		File file = new File("F:/A1学校相关文件/大二/编译原理/实验/实验三源码/7-Decaf语言语法分析测试例2(for语句)-decaftest3-2.txt");
//		"E:/文件/编译技术/实验/第三次实验/6-Decaf语言语法分析测试例1-decaftest3-1.txt"
//		"E:/文件/编译技术/实验/第三次实验/7-Decaf语言语法分析测试例2(for语句)-decaftest3-2.txt"
		Reader reader = null;
		reader = new InputStreamReader(new FileInputStream(file));
		
		Lexer lex = new Lexer(reader);

		Parser parser = new Parser(lex);
		
		parser.program();
		System.out.print("\n");
	}

}
