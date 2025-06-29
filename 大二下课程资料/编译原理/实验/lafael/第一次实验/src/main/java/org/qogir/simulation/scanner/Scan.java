package org.qogir.simulation.scanner;

import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;

import java.util.ArrayDeque;

/**
 * lexical analysis
 */
public abstract class Scan {
    protected final RegularGrammar rg;
    protected final String input;

    public Scan(RegularGrammar rg, String input){
        this.rg = rg;
        this.input = input;
    }

    /**
     *
     * @param tokenQueue an empty token sequence used for holding output tokens.
     * @return
     */
    public abstract int scan(ArrayDeque tokenQueue);
}
