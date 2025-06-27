package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.FiniteAutomaton;
import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.HashMap;

public class RDFA extends FiniteAutomaton {

    /**
     * holds the maps between DFA states and NFA state sets
     */
    private HashMap<State, HashMap<Integer,State>> StateMappingBetweenDFAAndNFA = new HashMap<>();
    public RDFA(){
        super();
        this.StateMappingBetweenDFAAndNFA = new HashMap<>();
        this.transitTable = new LabeledDirectedGraph<>();
    }

    public RDFA(State startState){
        this.startState = startState;
        this.StateMappingBetweenDFAAndNFA = new HashMap<>();
        this.transitTable = new LabeledDirectedGraph<>();
        this.getTransitTable().addVertex(this.startState);
    }

    public void setStateMappingBetweenDFAAndNFA(State s, HashMap<Integer,State> nfaStates){
        this.StateMappingBetweenDFAAndNFA.put(s,nfaStates);
    }

    public HashMap<State, HashMap<Integer, State>> getStateMappingBetweenDFAAndNFA() {
        return StateMappingBetweenDFAAndNFA;
    }

    public String StateMappingBetweenDFAAndNFAToString() {
        String str = "";
        for(State s : this.getStateMappingBetweenDFAAndNFA().keySet()){
            String mapping = "";
            for(State ns : this.getStateMappingBetweenDFAAndNFA().get(s).values()){
                mapping += ns.toString() + ",";
            }
            mapping = mapping.substring(0,str.length()-1);
            mapping = "DFA State:" + s.toString() + "\tNFA State set:\t{"+ mapping + "}" + "\r";
            str += mapping;
        }
        return str;
    }
}
