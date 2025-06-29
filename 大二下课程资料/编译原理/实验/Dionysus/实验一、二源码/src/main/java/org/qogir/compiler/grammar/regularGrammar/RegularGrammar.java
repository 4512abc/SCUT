package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.util.StringUtil;
import java.util.ArrayList;

/**
 * Regular Grammar
 * 支持的符号: [A-Za-z] 和 ε;
 * 支持的文法: a|b, ab, a*, (a)
 *
 * 当实例化一个 RegularGrammar 对象时，仅接受 " 字符串 := 正则表达式 " 形式的输入。例如：
 * + regex1 := c(a|b)*
 * + regex2 := d(f|ea*(g|h))b
 * + regex3 := a|ε
 * ":=" 左边的字符串是正则表达式的名称，即词法分析中词法单元的标签（类型）。
 * ":=" 右边的字符串是正则表达式。
 */
public class RegularGrammar {
    // 正则文法的字母表，存储正则表达式中出现的字符
    public ArrayList<Character> symbols = new ArrayList<Character>();
    // 存储正则表达式对象的列表
    private final ArrayList<Regex> patterns = new ArrayList<>();

    /**
     * 构造函数，根据输入的正则表达式数组初始化正则文法对象
     * @param regexes 正则表达式数组，每个元素的格式为 " 字符串 := 正则表达式 "
     */
    public RegularGrammar(String[] regexes){
        // 遍历输入的正则表达式数组
        for(String r: regexes){
            // 提取 ":=" 左边的字符串作为正则表达式的名称
            String name = r.substring(0, r.lastIndexOf(":=") - 1) ;
            // 提取 ":=" 右边的字符串作为正则表达式
            String regex = r.substring(r.lastIndexOf(":=") + 2, r.length());

            // 创建 StringUtil 对象用于字符串处理
            StringUtil stringUtil = new StringUtil();
            // 去除名称字符串两端的空白字符
            name = stringUtil.trim(name);
            // 去除正则表达式字符串两端的空白字符
            regex = stringUtil.trim(regex);

            // 创建 Regex 对象
            Regex p = new Regex(name, regex, 0);
            // 将 Regex 对象添加到 patterns 列表中
            this.patterns.add(p);
            // 遍历正则表达式中的每个字符
            for(Character ch : regex.toCharArray()){
                // 如果字符是字母且不是 ε，并且 symbols 列表中不包含该字符
                if(Character.isLetter(ch) && ch != 'ε' && !symbols.contains(ch)){
                    // 将该字符添加到 symbols 列表中
                    this.symbols.add(ch);
                }
            }
        }
    }

    /**
     * 获取正则文法的字母表
     * @return 存储字母表字符的列表
     */
    public ArrayList<Character> getSymbols(){
        return this.symbols;
    }

    /**
     * 获取存储正则表达式对象的列表
     * @return 存储 Regex 对象的列表
     */
    public ArrayList<Regex> getPatterns() {
        return patterns;
    }

    /**
     * 将正则文法对象转换为字符串表示
     * @return 包含正则文法信息的字符串
     */
    @Override
    public String toString() {
        // 创建 StringBuilder 对象用于拼接字符串
        StringBuilder regularGrammarStr = new StringBuilder();
        // 拼接正则文法信息
        return regularGrammarStr.append("Regular Grammar\n").append("Alphabet:").append(symbols.toString()).append("\n").append("Regexes:\n").append(patterns.toString()).toString();
    }
}