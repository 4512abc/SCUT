package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * The subset construction Algorithm for converting an NFA to a DFA.
 * The subset construction Algorithm takes an NFA N as input and output a DFA D accepting the same language as N.
 * The main mission is to eliminate ε-transitions and multi-transitions in NFA and construct a transition table for D.
 * The algorithm can be referred to {@see }
 */
//子集构造法
public class SubsetConstruction {

    /**
     * Eliminate all ε-transitions reachable from a single state in NFA through the epsilon closure operation.
     * @param s a single state of NFA
     * @param tb the transition table of NFA
     * @return a set of state reachable from the state s on ε-transition
     */
    private HashMap<Integer, State> epsilonClosures(State s, LabeledDirectedGraph<State> tb){
        if (!tb.vertexSet().contains(s)) { //if vertex s not in the transition table
                return null;
        }

        HashMap<Integer,State> nfaStates = new HashMap<>();

        //Add your implementation


        return nfaStates;
    }

    /**
     * Eliminate all ε-transitions reachable from a  state set in NFA through the epsilon closure operation
     * @param ss a state set of NFA
     * @param tb the transition table of NFA
     * @return a set of state reachable from the state set on ε-transition
     * @author xuyang
     */

    public HashMap<Integer, State> epsilonClosure(HashMap<Integer, State> ss, LabeledDirectedGraph<State> tb){
        HashMap<Integer,State> nfaStates = new HashMap<>();
        for(State s : ss.values()){
            nfaStates.putAll(epsilonClosures(s,tb));
        }
        return nfaStates;
    }

    /**
     *
     * @param s
     * @param ch
     * @param tb
     * @return
     */
    private HashMap<Integer,State> moves(State s, Character ch, LabeledDirectedGraph<State> tb){
        HashMap<Integer,State> nfaStates = new HashMap<>();

        //Add your implementation

        return nfaStates;
    }

    public HashMap<Integer,State> move(HashMap<Integer, State> ss, Character ch, LabeledDirectedGraph<State> tb){
        HashMap<Integer,State> nfaStates = new HashMap<>();
        for(State s : ss.values()){
            nfaStates.putAll(moves(s,ch,tb));
        }
        return nfaStates;
    }

    public HashMap<Integer,State> epsilonClosureWithMove(HashMap<Integer, State> sSet, Character ch, LabeledDirectedGraph<State> tb){
        HashMap<Integer,State> states = new HashMap<>();
        states.putAll(epsilonClosure(move(sSet, ch, tb),tb));
        return states;
    }
    public RDFA subSetConstruct(TNFA tnfa){

        // Add your implementation
        return null;
    }
}
