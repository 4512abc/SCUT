package org.qogir.compiler.grammar.regularGrammar;

/**
 * 该类用于定义正则表达式。
 * 正则表达式的形式为 "id := regex" ；
 * "id" 位于等式 ":=" 的左侧，是正则表达式的名称或标识符；
 * "regex" 位于等式 ":=" 的右侧，是正则表达式的字符串内容。
 * 每个正则表达式还包含一个优先级参数，用于在多个正则表达式同时匹配时决定优先级顺序。
 */
public class Regex {
    /**
     * 正则表达式的名称或标识符，位于等式 ":=" 的左侧。
     */
    private final String name;
    /**
     * 正则表达式的字符串内容，位于等式 ":=" 的右侧。
     */
    private final String regex;
    /**
     * 正则表达式的优先级，用于在多个正则表达式同时匹配输入字符串时，
     * 决定优先采用哪个正则表达式的匹配结果，数值越大优先级越高。
     */
    private final int priority;

    /**
     * 构造函数，用于创建一个正则表达式对象。
     *
     * @param name 正则表达式的名称或标识符。
     * @param regex 正则表达式的字符串内容。
     * @param priority 正则表达式的优先级，数值越大优先级越高。
     */
    public Regex(String name, String regex, int priority){
        this.name = name;
        this.regex = regex;
        this.priority = priority;
    }

    /**
     * 获取正则表达式的名称或标识符。
     *
     * @return 正则表达式的名称或标识符。
     */
    public String getName() {
        return this.name;
    }

    /**
     * 获取正则表达式的字符串内容。
     *
     * @return 正则表达式的字符串内容。
     */
    public String getRegex() {
        return this.regex;
    }

    /**
     * 获取正则表达式的优先级。
     *
     * @return 正则表达式的优先级，数值越大优先级越高。
     */
    public int getPriority() {
        return priority;
    }

    /**
     * 将正则表达式对象转换为字符串表示形式。
     * 格式为 "名称 := 正则表达式字符串"。
     *
     * @return 正则表达式的字符串表示形式。
     */
    @Override
    public String toString() {
        return this.name + " := " + this.regex;
    }
}