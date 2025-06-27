package org.qogir.simulation.scanner;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.grammar.regularGrammar.RDFA;
import org.qogir.compiler.grammar.regularGrammar.Regex;
import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;
import org.qogir.compiler.grammar.regularGrammar.TNFA;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.HashMap;

public class ScanWithDFA extends Scan{

    public ScanWithDFA(RegularGrammar rg, String input) {
        super(rg, input);
    }

    @Override
    public int scan(ArrayDeque tokenQueue) {
        Scanner scanner = new Scanner(rg);
        RDFA dfa = scanner.constructDFA();
        LabeledDirectedGraph<State> tb = dfa.getTransitTable();
        State startState = dfa.getStartState();

        String inputList = this.input + "$";
        char[] input = inputList.toCharArray();

        //State lastAcceptingStates;
        int lastStartCharAt = 0;
        int lastAcceptedCharAt = 0;

        State currentState = new State(startState);

        for(int i = 0; i< input.length; i++){

            if(input[i]!='$' && !rg.symbols.contains(input[i]))
                return ScanMessage.NOT_MATCH;

            State nextState = null;
            if(currentState != null){
                for(LabelEdge e : tb.edgeSet()){
                    if(tb.getEdgeSource(e) == currentState && e.getLabel().equals(input[i])){
                        nextState = tb.getEdgeTarget(e);
                    }
                }
            }
            State lastAcceptingState = null;
            if(nextState != null) {
                if (nextState.getType() == 2 || nextState.getType() == 20) {
                    lastAcceptedCharAt = i;
                    lastAcceptingState = nextState;
                }
                currentState = nextState;
            }
            else { //stuck, can output
                if(lastAcceptingState == null){
                    return ScanMessage.NOT_MATCH;
                }
                else {
                    String lexeme = this.input.substring(lastStartCharAt, lastAcceptedCharAt + 1);
                    HashMap<State, HashMap<Integer,State>> dfatonfas = scanner.getDFAToNFAs();
                    HashMap<Integer,State> nfas = new HashMap<>();
                    for(State s : dfatonfas.keySet()){
                        if(s.equals(lastAcceptingState)){

                        }

                    }
                    HashMap<Regex, TNFA> rtonfa = scanner.getRegexToNFA();

                    int priority = -1;
                    for(Regex r : rtonfa.keySet()){
                        /*if(lastAcceptingState.containsValue(rtonfa.get(r).getAcceptingState())) {
                            if(r.getPriority() > priority){
                                priority = r.getPriority();
                                String regexName = r.getName();
                                tokenQueue.add(new Token(regexName,lexeme));
                            }
                            else if(r.getPriority() == priority){
                                return ScanMessage.AMBIGUITY_GRAMMAR;
                                //throw new AssertionError("The regular grammar" + rg.toString() + " is ambiguity!");
                            }
                        }*/
                    }
                    if(input[i] != '$') {
                        i = lastAcceptedCharAt;
                        lastStartCharAt = lastAcceptedCharAt + 1;
                        currentState = startState;//restart NFA
                    }
                }
            }

        }

        return ScanMessage.SUCCESS_MATCH;
    }
}
