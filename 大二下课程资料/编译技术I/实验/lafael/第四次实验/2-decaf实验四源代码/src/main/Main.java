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
		File file = new File("E:/文件/编译技术/实验/第四次实验/3-Decaf语言中间代码生成测试例3-decaftest4-3.txt");
		// "E:/文件/编译技术/实验/第四次实验/3-Decaf语言中间代码生成测试例1-decaftest4-1.txt"
		// "E:/文件/编译技术/实验/第四次实验/3-Decaf语言中间代码生成测试例2-decaftest4-2.txt"
		// "E:/文件/编译技术/实验/第四次实验/3-Decaf语言中间代码生成测试例3-decaftest4-3.txt"
		Reader reader = null;
		reader = new InputStreamReader(new FileInputStream(file));
		// �½�һ���ʷ������������ļ�����lexer��������ȡ�ļ�����
		Lexer lex = new Lexer(reader);
		Parser parser = new Parser(lex);
		parser.program();
		System.out.print("\n");
	}

}
