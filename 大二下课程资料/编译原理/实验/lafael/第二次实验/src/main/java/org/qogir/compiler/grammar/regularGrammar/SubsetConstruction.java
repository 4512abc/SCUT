package org.qogir.compiler.grammar.regularGrammar;

import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * The subset construction Algorithm for converting an NFA to a DFA.
 * The subset construction Algorithm takes an NFA N as input and output a DFA D accepting the same language as N.
 * The main mission is to eliminate ε-transitions and multi-transitions in NFA and construct a transition table for D.
 * The algorithm can be referred to {@see }
 */
public class SubsetConstruction {

    private ArrayDeque<String> stepQueue = new ArrayDeque<>();
    /**
     * 记录每一步的状态集合
     */

    private void recordStep(String message, HashMap<Integer, State> stateMap) {
        StringBuilder sb = new StringBuilder();
        for (Integer id : stateMap.keySet()) {
            sb.append(id).append(":").append(stateMap.get(id).getType()).append(",");
        }
        if (sb.length() > 0) sb.deleteCharAt(sb.length() - 1);
        stepQueue.add("[" + message + "] {" + sb.toString() + "}");
    }
    private void recordDistinguishSteps(HashMap<Integer, HashMap<Integer, State>> groupSet, String memo) {
        StringBuilder sb = new StringBuilder();
        for (Integer g : groupSet.keySet()) {
            sb.append(g).append(":{");
            for (Integer id : groupSet.get(g).keySet()) {
                State s = groupSet.get(g).get(id);
                sb.append(s.getId()).append(":").append(s.getType()).append(",");
            }
            if (sb.charAt(sb.length() - 1) == ',') {
                sb.deleteCharAt(sb.length() - 1);
            }
            sb.append("} ");
        }
        stepQueue.add(sb.toString() + ":" + memo);
    }
    /**
     * 展示所有步骤
     */
    public void showSteps() {
        int step = 0;
        while (!stepQueue.isEmpty()) {
            System.out.println("Step " + (step++) + ": " + stepQueue.poll());
        }
    }
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

        ArrayDeque<State> queue = new ArrayDeque<>();
        queue.add(s);
        // 初始状态
        recordStep("Initial", new HashMap<>(Map.of(s.getId(), s)));
        while(!queue.isEmpty()) {
            State state = queue.poll();
            nfaStates.putIfAbsent(state.getId(), state);

            //add each new state reached by an edge from ‘state’ on 'ε' to ‘queue’
            for (LabelEdge e : tb.edgeSet()) {
            	//Add your implementation
                /*
                补充代码
                 */
                if(tb.getEdgeSource(e).equals(state) && e.getLabel() == 'ε' && !nfaStates.containsKey(tb.getEdgeTarget(e).getId())) {
                    State target = tb.getEdgeTarget(e);
                    nfaStates.put(target.getId(), target);
                    queue.push(target);
                    recordStep("ε-Closure Add", nfaStates); // 每次加入新状态都记录
                }
            }
        }
        return nfaStates;
    }

    /**
     * Eliminate all ε-transitions reachable from a  state set in NFA through the epsilon closure operation
     * @param ss a state set of NFA
     * @param tb the transition table of NFA
     * @return a set of state reachable from the state set on ε-transition
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

        //put each state reached by an edge from ‘s’ on 'ch' to ‘nfaStates’
        for(LabelEdge e : tb.edgeSet()){
        	//Add your implementation
            /*
            补充代码
             */
            if(tb.getEdgeSource(e).equals(s)&&e.getLabel()==ch)
                nfaStates.put(tb.getEdgeTarget(e).getId(),tb.getEdgeTarget(e));
        }

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

        ArrayList<Character> symbols = tnfa.getAlphabet();
        LabeledDirectedGraph<State> tb = tnfa.getTransitTable();
        State tnfaStartState = tnfa.getStartState();
        State tnfaAcceptState = tnfa.getAcceptingState();

        //RDFA start state is a epsilonClosure of tnfa.startState
        HashMap<Integer, State> dFAStartStates = new HashMap<>();
        dFAStartStates.put(tnfaStartState.getId(), tnfaStartState);
        dFAStartStates = epsilonClosure(dFAStartStates, tb);

        // if there is an accepting state in the epsilonClosure of tnfaStartState
        for(State s : dFAStartStates.values()){
            if(s.getType() == State.ACCEPT){
                tnfaStartState.setType(State.ACCEPTANDSTART); //set the tnfaStartState as acceptAndStart
                break;
            }
        }

        //build a DFA
        RDFA dfa = new RDFA(tnfaStartState);
        dfa.getStateMappingBetweenDFAAndNFA().put(tnfaStartState, dFAStartStates);

        ArrayDeque<State> queue = new ArrayDeque<>();
        queue.add(tnfaStartState);

        dfa.setAlphabet(symbols);

        //State dfaState;
        while (!queue.isEmpty()) {
            State SourceDfaState = queue.poll();
            getTargetNfaStateSetForEachCharacter(symbols, dfa, SourceDfaState, tb, queue, tnfaStartState, tnfaAcceptState);
        }
        showSteps();
        return dfa;
    }
    
    void getTargetNfaStateSetForEachCharacter(ArrayList<Character> symbols, RDFA dfa, State SourceDfaState,
            LabeledDirectedGraph<State> tb, ArrayDeque<State> queue, State tnfaStartState, State tnfaAcceptState) {
    	for (Character ch : symbols) {
    		HashMap<Integer, State> TargetNfaStateSet = new HashMap<>();
    		TargetNfaStateSet.putAll(epsilonClosureWithMove(dfa.getStateMappingBetweenDFAAndNFA().get(SourceDfaState), ch, tb));
    		
    		if (TargetNfaStateSet.isEmpty()) continue;
            recordStep("Move on '" + ch + "'", TargetNfaStateSet);
            //Check the TargetNfaStateSet whether exists in DFA state(StateMappingBetweenDFAAndNFA) or not
    		boolean bool = false; //indicates that TargetNfaStateSet not exist in the DFA.
    		for (State s : dfa.getStateMappingBetweenDFAAndNFA().keySet()) {
    			if (dfa.getStateMappingBetweenDFAAndNFA().get(s).equals(TargetNfaStateSet)) {
    				//TargetNfaStateSet already exists in DFA
    				ifExistsInDFA(s, SourceDfaState, dfa, ch, TargetNfaStateSet);
    				bool = true;
    				break;
    				}
    			}
    		
    		//if not exist in, create a new targetDfaState
    		if (!bool) {
    			ifNotExistsInDFA(queue, TargetNfaStateSet, tnfaStartState, tnfaAcceptState, SourceDfaState, dfa, ch);
    			}
    		}
    	}    
    
    void ifExistsInDFA(State s, State SourceDfaState, RDFA dfa, Character ch, HashMap<Integer, State> TargetNfaStateSet) {
        State targetDfaState = new State(s);
        dfa.getTransitTable().addEdge(new LabelEdge(SourceDfaState, targetDfaState, ch));

    }

    void ifNotExistsInDFA(ArrayDeque<State> queue, HashMap<Integer, State> TargetNfaStateSet, State tnfaStartState,
                          State tnfaAcceptState, State SourceDfaState, RDFA dfa, Character ch) {
        State targetDfaState = new State();
        queue.add(targetDfaState);

        //judge the dfaState whether is start state, middle state or accepting state
        if (TargetNfaStateSet.containsValue(tnfaAcceptState)) {
            targetDfaState.setType(State.ACCEPT);
        } else {
            targetDfaState.setType(State.MIDDLE);
        }

        //add the new DFA state ‘targetDfaState’ and its NFA state set to mapping 
        dfa.setStateMappingBetweenDFAAndNFA(targetDfaState, TargetNfaStateSet);
        
        //add the new DFA state and new edge to transit table

        /*
        补充代码
         */
        dfa.getTransitTable().addVertex(targetDfaState);
        dfa.getTransitTable().addEdge(new LabelEdge(SourceDfaState, targetDfaState, ch));
    }
}
