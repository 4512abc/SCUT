package org.qogir.compiler.grammar.regularGrammar.scanner;

import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;
import org.qogir.simulation.scanner.ScanWithNFA;
import org.qogir.simulation.scanner.Token;

import java.util.ArrayDeque;

/**
 * ScanWithNFATest 类用于测试 ScanWithNFA 类的扫描功能，
 * 通过定义正则文法和输入字符串，使用 ScanWithNFA 进行扫描操作，并输出扫描结果。
 */
public class ScanWithNFATest {
    /**
     * 程序入口方法，执行 ScanWithNFA 类的扫描功能测试。
     * @param args 命令行参数，在本程序中未使用。
     */
    public static void main(String[] args) {
        // 定义正则表达式数组，用于创建正则文法
        String[] regexes = new String[]{"regex0 := a|b","regex1 := c(a|b)*"};
        // 注释中列出了其他可测试的正则表达式组合
        //"regex1 := c(a|b)*","regex2 := d(f|ea*(g|h))b","c(a|b)*","a|b", "ab*", "d(f|e)","d(f|ea*(g|h))b","c(a|b)*"

        // 定义待扫描的输入字符串
        String input = "abbcab";//aabb
        // 测试正则文法的定义，创建一个正则文法对象
        RegularGrammar rg = new RegularGrammar(regexes);
        // 创建 ScanWithNFA 对象，传入正则文法和输入字符串
        ScanWithNFA scanWithNFA = new ScanWithNFA(rg, input);
        // 创建一个双端队列，用于存储扫描过程中生成的 Token 对象
        ArrayDeque<Token> tokens = new ArrayDeque<>();
        // 调用 ScanWithNFA 的 scan 方法进行扫描，返回扫描结果
        int result = scanWithNFA.scan(tokens);

        // 创建 StringBuilder 对象，用于拼接扫描结果信息
        StringBuilder str = new StringBuilder();
        // 将扫描结果添加到 StringBuilder 中
        str.append(result).append("\n");
        // 遍历双端队列，将每个 Token 对象的信息添加到 StringBuilder 中
        while(!tokens.isEmpty()) {
            Token token = tokens.poll();
            str.append(token.toString()).append("\n");
        }

        // 打印最终的扫描结果信息
        System.out.println(str);

    }
}