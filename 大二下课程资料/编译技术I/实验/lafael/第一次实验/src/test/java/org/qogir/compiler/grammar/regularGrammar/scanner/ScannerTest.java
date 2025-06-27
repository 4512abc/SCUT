package org.qogir.compiler.grammar.regularGrammar.scanner;

import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;
import org.qogir.simulation.scanner.Scanner;

public class ScannerTest {
    public static void main(String[] args) {

        String[] regexes = new String[]{"regex1 := a(a|b)*a"}; //,"regex1 := c(a|b)*"
        //{"regex1 := c(a|b)*"};//{"regex0 := a|ε","regex1 := c(a|b)*"};//"regex1 := c(a|b)*","regex2 := d(f|ea*(g|h))b","c(a|b)*","a|b", "ab*", "d(f|e)","d(f|ea*(g|h))b","c(a|b)*"

        //test defining a regular grammar
        RegularGrammar rg = new RegularGrammar(regexes);

        System.out.println(rg);
        //test building a grammar for the grammar
        Scanner scanner = new Scanner(rg);

        //test constructing the regex tree
        System.out.println(scanner.constructRegexTrees().toString());

        System.out.println("Show the NFA:");
        //test constructing the NFA
        System.out.println(scanner.constructNFA().toString());

        //System.out.println("Show the DFA:");
        //test constructing the DFA

        //System.out.println(scanner.constructDFA(scanner.constructNFA()).toString());
        //System.out.println("Show the miniDFA:");
        //test minimizing the DFA
        //State.STATE_ID = 0;
        //System.out.println(scanner.minimizeDFA(scanner.constructDFA(scanner.constructNFA())).toString());

    }
}