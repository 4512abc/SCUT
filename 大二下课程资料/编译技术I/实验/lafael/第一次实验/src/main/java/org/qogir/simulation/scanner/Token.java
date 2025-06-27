package org.qogir.simulation.scanner;

public class Token {
    private final String tag;
    private final String lexeme;

    public Token(String tag,String lexeme){
        this.tag = tag;
        this.lexeme = lexeme;
    }

    @Override
    public String toString() {
        return this.tag + ":" + this.lexeme;
    }
}
