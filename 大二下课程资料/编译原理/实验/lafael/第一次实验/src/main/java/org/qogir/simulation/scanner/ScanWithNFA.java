package org.qogir.simulation.scanner;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.grammar.regularGrammar.Regex;
import org.qogir.compiler.grammar.regularGrammar.RegularGrammar;
import org.qogir.compiler.grammar.regularGrammar.SubsetConstruction;
import org.qogir.compiler.grammar.regularGrammar.TNFA;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.HashMap;

/**
 *  scan uses Maximal Munch principle and priority system.
 *  Run all NFAs in parallel, keeping track of the last match.
 *  When all automata get stuck, report the last match and restart the search at that point.
 *  When more than one regular expressions apply, choose the one with the greater “priority.”
 *  If exist two regular expressions with same priority can accept the same input string(substring), error.
 *  @author xuyang
 */
public class ScanWithNFA extends Scan{

    public ScanWithNFA(RegularGrammar rg, String input){
        super(rg,input);
    }


    @Override
    public int scan(ArrayDeque tokenQueue){ //ArrayDeque scan() {
         // Get the NFA.
        Scanner scanner = new Scanner(rg);
        TNFA nfa =  scanner.constructNFA();
        LabeledDirectedGraph<State> tb = nfa.getTransitTable();
        State startState = nfa.getStartState();

        // add "$" for representing the input string.
        String inputList = this.input + "$";
        char[] input = inputList.toCharArray();

        // All NFAs start in parallel to scan.
        SubsetConstruction sc = new SubsetConstruction();
        HashMap<Integer, State> startStates = new HashMap<>();
        startStates.put(startState.getId(),startState);
        startStates = sc.epsilonClosure(startStates,tb);

        //record last accepting state during NFA running.
        HashMap<Integer, State> lastAcceptingStates = new HashMap<>();
        HashMap<Integer, State> currentAcceptingStates = new HashMap<>();

        //used for record the start and end position of substring to be output
        int lastStartCharAt = 0;
        int lastAcceptedCharAt = 0;

        //initialize current states with start states
        HashMap<Integer, State> currentStates = new HashMap<>();
        currentStates.putAll(startStates);
        HashMap<Integer, State> nextStates = new HashMap<>();

        for(int i = 0; i< input.length; i++){

            if(input[i]!='$' && !rg.symbols.contains(input[i]))
                return ScanMessage.NOT_MATCH;
                //throw new AssertionError("The input " +  this.input + " can not be matched with the regular grammar!");

            if(!nextStates.isEmpty())
                nextStates.clear();

            nextStates.putAll(sc.epsilonClosureWithMove(currentStates, input[i], tb));

            //put the accepting states in next states into current accepting states
            currentAcceptingStates.clear();
            for(State s : nextStates.values()) {
                if(s.getType() == State.ACCEPT || s.getType() == State.ACCEPTANDSTART)
                    currentAcceptingStates.put(s.getId(),s);
            }

            if(!currentAcceptingStates.isEmpty()){
                lastAcceptedCharAt = i;
                lastAcceptingStates.clear();
                lastAcceptingStates.putAll(currentAcceptingStates);
            }

            if(nextStates.isEmpty()){ //stuck, can output
                if(lastAcceptingStates.isEmpty()){
                    return ScanMessage.NOT_MATCH;
                    //throw new AssertionError("The input " +  this.input + " can not be matched with the regular grammar!");
                }
                else {//if(!lastAcceptingStates.isEmpty(), output token
                    String lexeme = this.input.substring(lastStartCharAt, lastAcceptedCharAt + 1);
                    HashMap<Regex, TNFA> rtonfa = scanner.getRegexToNFA();
                    int priority = -1;
                    for(Regex r : rtonfa.keySet()){
                       if(lastAcceptingStates.containsValue(rtonfa.get(r).getAcceptingState())) {
                           if(r.getPriority() > priority){
                               priority = r.getPriority();
                               String regexName = r.getName();
                               tokenQueue.add(new Token(regexName,lexeme));
                           }
                           else if(r.getPriority() == priority){
                               return ScanMessage.AMBIGUITY_GRAMMAR;
                               //throw new AssertionError("The regular grammar" + rg.toString() + " is ambiguity!");
                           }
                       }
                    }
                    if(input[i] != '$') {
                        i = lastAcceptedCharAt;
                        lastStartCharAt = lastAcceptedCharAt + 1;
                        currentStates.clear();
                        currentStates.putAll(startStates);//restart NFA
                    }
                }
            }
            else{ // hold current situation and going on
                currentStates.clear();
                currentStates.putAll(nextStates);
            }
        }

        if(lastAcceptedCharAt != input.length - 2)
            return ScanMessage.NOT_MATCH;
            //throw new AssertionError("The input " + this.input + " can not be matched with the regular grammar!");
        return ScanMessage.SUCCESS_MATCH;
    }
}
