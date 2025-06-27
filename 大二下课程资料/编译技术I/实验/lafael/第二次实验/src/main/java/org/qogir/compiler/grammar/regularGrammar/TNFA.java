package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.FiniteAutomaton;
import org.qogir.compiler.FA.State;

/**
 * A nondeterministic finite automaton (NFA) is a 5-tuple (S,∑,F,s0,sf). Here,
 *   S - a finite set of state. i.e The vertex set of transition graph of NFA
 *   ∑ - an Alphabet, not including ε
 *   F - S X ∑ U {ε} -> subset of S
 *   s0 - a start state
 *   sf - an accepting state.
 * Here, following McNaughton-Yamada-Thompson algorithm, NFA has the following properties:
 *   each NFA has only one accepting state;
 *   The accepting state has no outgoing transitions, and the start state has no incoming
 *   transitions.
 *   Each state other than the accepting state has either one outgoing transition on a symbol
 *   in alphabet or two outgoing transitions, both on ε(epsilon).
 */

public class TNFA extends FiniteAutomaton {

    private State acceptingState = new State();

    public TNFA(){
        super();
        acceptingState.setType(State.ACCEPT);
        this.transitTable.addVertex(acceptingState);
    }

    public TNFA(State acceptingState){
        super();
        this.acceptingState = acceptingState;
        this.acceptingState.setType(State.ACCEPT);
        this.transitTable.addVertex(this.acceptingState);
    }

    public State getAcceptingState() {
        return acceptingState;
    }

    public void setAcceptingState(State acceptingState) {
        this.acceptingState = acceptingState;
    }
}
