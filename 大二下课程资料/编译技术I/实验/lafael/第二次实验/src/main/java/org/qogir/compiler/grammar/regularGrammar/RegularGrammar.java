package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.util.StringUtil;
import java.util.ArrayList;

/**
 * Regular Grammar
 * The supported symbols: [A-Za-z] and ε;
 * The supported grammars: a|b, ab, a*, (a)
 *
 * When instantiate a RegularGrammar object, only the inputs with " string := regular expression " form
 * are accepted. For example:
 * + regex1 := c(a|b)*
 * + regex2 := d(f|ea*(g|h))b
 * + regex3 := a|ε
 * The string on the left hand of ":="  is the name of regex, i.e. tag(type) of token in lexical analysis.
 * The string on the right hand of ":=" is regular expression.
 */
public class RegularGrammar {
    public ArrayList<Character> symbols = new ArrayList<Character>();//the alphabet for regular grammar
    private final ArrayList<Regex> patterns = new ArrayList<>();
    public RegularGrammar(String[] regexes){
        for(String r: regexes){
            String name = r.substring(0, r.lastIndexOf(":=") - 1) ;
            String regex = r.substring(r.lastIndexOf(":=") + 2, r.length());

            StringUtil stringUtil = new StringUtil();
            name = stringUtil.trim(name);
            regex = stringUtil.trim(regex);

            Regex p = new Regex(name, regex, 0);
            this.patterns.add(p);
            for(Character ch : regex.toCharArray()){
                if(Character.isLetter(ch) && ch != 'ε' && !symbols.contains(ch)){
                    this.symbols.add(ch);
                }
            }
        }
    }

    public ArrayList<Character> getSymbols(){
        return this.symbols;
    }
    public ArrayList<Regex> getPatterns() {
        return patterns;
    }

    @Override
    public String toString() {
        StringBuilder regularGrammarStr = new StringBuilder();
        return regularGrammarStr.append("Regular Grammar\n").append("Alphabet:").append(symbols.toString()).append("\n").append("Regexes:\n").append(patterns.toString()).toString();
    }
}
