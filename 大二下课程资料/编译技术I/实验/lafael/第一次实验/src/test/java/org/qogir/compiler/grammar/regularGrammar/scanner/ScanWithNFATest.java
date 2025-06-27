package org.qogir.compiler.grammar.regularGrammar.scanner;

import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;
import org.qogir.simulation.scanner.ScanWithNFA;
import org.qogir.simulation.scanner.Token;

import java.util.ArrayDeque;

public class ScanWithNFATest {

    public static void main(String[] args) {
        String[] regexes = new String[]{"regex0 := a|b","regex1 := c(a|b)*"};//"regex1 := c(a|b)*","regex2 := d(f|ea*(g|h))b","c(a|b)*","a|b", "ab*", "d(f|e)","d(f|ea*(g|h))b","c(a|b)*"

        String input = "abbcab";//aabb
        //test defining a regular grammar
        RegularGrammar rg = new RegularGrammar(regexes);
        ScanWithNFA scanWithNFA = new ScanWithNFA(rg, input);
        ArrayDeque<Token> tokens = new ArrayDeque<>();
        int result = scanWithNFA.scan(tokens);

        StringBuilder str = new StringBuilder();
        str.append(result).append("\n");
        while(!tokens.isEmpty()) {
            Token token = tokens.poll();
            str.append(token.toString()).append("\n");
        }

        System.out.println(str);

    }
}
