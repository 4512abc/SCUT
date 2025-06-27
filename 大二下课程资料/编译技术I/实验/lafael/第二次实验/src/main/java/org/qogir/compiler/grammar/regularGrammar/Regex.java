package org.qogir.compiler.grammar.regularGrammar;

/**
 * The definition regular expression
 * The form of regex id "id := regex" ;
 * "id" , left hand of equation ":=", is the name or identifier of the regex
 * "regex" , right hand of equation ":=", is the string of regex
 */
public class Regex {
    private final String name;
    private final String regex;
    private final int priority;

    public Regex(String name, String regex, int priority){
        this.name = name;
        this.regex = regex;
        this.priority = priority;
    }

    public String getName() {
        return this.name;
    }

    public String getRegex() {
        return this.regex;
    }

    public int getPriority() {
        return priority;
    }

    @Override
    public String toString() {
        return this.name + " := " + this.regex;
    }
}
