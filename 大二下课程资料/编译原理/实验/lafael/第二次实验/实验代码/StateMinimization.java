package org.qogir.compiler.grammar.regularGrammar;


import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class StateMinimization {

    /**
     * Distinguish non-equivalent states in the given DFA.
     * @param dfa the original dfa.
     * @return distinguished equivalent state groups
     */
    private HashMap<Integer,HashMap<Integer, State>> distinguishEquivalentState(RDFA dfa){


        LabeledDirectedGraph<State> tb = dfa.getTransitTable();
        ArrayList<Character> symbols = dfa.getAlphabet();

        HashMap<Integer, State> acceptGroup = new HashMap<>();
        HashMap<Integer, State> nonAcceptGroup = new HashMap<>();
        for(State s : tb.vertexSet()){
            if(s.getType() == State.ACCEPT || s.getType() == State.ACCEPTANDSTART)
                acceptGroup.put(s.getId(),s);
            else
                nonAcceptGroup.put(s.getId(),s);
        }
        HashMap<Integer,HashMap<Integer, State>> groupSet = new HashMap<>(); // group set
        groupSet.put(0,acceptGroup);
        if(!nonAcceptGroup.isEmpty()){
            groupSet.put(1,nonAcceptGroup);
        }

        HashMap<Integer,HashMap<Integer, State>> newGroupSet = new HashMap<>();
        int lastNum = 0; //used for recording #groups

        for(Character ch : symbols){//each symbol

            newGroupSet.clear();

            while(newGroupSet.size() != groupSet.size()){ //until no equivalent state can be distinguished

                if(newGroupSet.size() != 0 ) newGroupSet.clear();
                newGroupSet.putAll(groupSet);
                groupSet.clear(); //clear for holding new groups
                lastNum = 0;

                for (HashMap<Integer, State> group : newGroupSet.values()) { // each group
                    //distinguish non-equivalent states
                    HashMap<State, Integer> split = new HashMap<>();
                    for(State s : group.values()){
                        split.put(s,-1); //initialize that all states reach no group
                    }

                    //Check and record which group in groupSet each state 's' can reach on "ch".
                    //Record in split
                    //Check and record which group in groupSet each state 's' can reach on "ch".
                    //Record in split
                    for (State s : group.values()) {
                        //get the edge with "ch" as label and  's' as source vertex
                        //Add your implementation
                        boolean found = false;
                        for(LabelEdge e : tb.edgeSet()){
                            if(tb.getEdgeSource(e).equals(s) && e.getLabel().equals(ch)){
                                State target = tb.getEdgeTarget(e);
                                // Find which group the target state belongs to
                                for(Map.Entry<Integer, HashMap<Integer, State>> entry : newGroupSet.entrySet()){
                                    if(entry.getValue().containsKey(target.getId())){
                                        split.put(s, entry.getKey());
                                        found = true;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        if(!found){
                            split.put(s, -1); // no transition on this symbol
                        }
                    }

                    //regroup equivalent states, and add the group into the group set

                    // set group id for new groups
                    HashMap<Integer,HashMap<Integer, State>> tempGroupSet = new HashMap<>();
                    for(Integer g : split.values()){//create groups
                        tempGroupSet.put(g, new HashMap<>());
                    }
                    for(State s : split.keySet()){
                        tempGroupSet.get(split.get(s)).put(s.getId(), s);
                    }

                    for(int i = 0; i < tempGroupSet.size(); i++){
                        groupSet.put(i+lastNum,new HashMap<Integer,State>());
                    }

                    int j =0;
                    for(HashMap<Integer,State> h : tempGroupSet.values()){
                        groupSet.put(j+lastNum, h);
                        j++;
                    }
                    lastNum = groupSet.size();

                }
            }
        }

        return groupSet;
    }

    public RDFA minimize(RDFA dfa){

        if(dfa == null)
            return null;

        HashMap<Integer,HashMap<Integer, State>> newGroupSet = distinguishEquivalentState(dfa);

        if(newGroupSet == null)
            return null;

        LabeledDirectedGraph<State> tb = dfa.getTransitTable();

        //construct the minimized DFA with newGroupSet
        //System.out.println("Construct the minimized DFA.");
        RDFA minDFA = new RDFA(dfa.getStartState()); //the minimized DFA

        HashMap<State,Integer> dfaStateToGroup = new HashMap<>();//search group id by representative state;used for holding the representative for each state group.
        HashMap<Integer,State> GroupToDfaState = new HashMap<>();//search representative state by group id
        ArrayDeque<State> queue = new ArrayDeque<>(); // used for building the minimized DFA

        //get the representative states
        for(Integer k : newGroupSet.keySet()){
            State s;
            if(newGroupSet.get(k).containsValue(dfa.getStartState())){ //set the start state of  original DFA as start state of the minimized DFA
                s = dfa.getStartState();
            }
            else {//select the first state in each newGroupSet as the representative of the newGroupSet
                s = (State) newGroupSet.get(k).values().toArray()[0];
            }
            dfaStateToGroup.put(s,k);
            GroupToDfaState.put(k,s);
            queue.add(s);
        }

        //build the transitTable of the minimized DFA
        while(!queue.isEmpty()){
            State s =  queue.poll();

            minDFA.getTransitTable().addVertex(s);

            for(State ss : newGroupSet.get(dfaStateToGroup.get(s)).values()){ //all states in one group
                for(LabelEdge e : tb.edgeSet()) { // add edge
                    if(tb.getEdgeSource(e) == ss){
                        State ts = tb.getEdgeTarget(e);
                        for(Integer k : newGroupSet.keySet()){
                            if(newGroupSet.get(k).containsValue(ts) != false){
                                minDFA.getTransitTable().addVertex(GroupToDfaState.get(k));
                                minDFA.getTransitTable().addEdge(new LabelEdge(s,GroupToDfaState.get(k),e.getLabel()));
                                break;
                            }
                        }
                    }
                }
            }
        }

        return minDFA;
    }

//    /**
//     * Used for showing the distinguishing process of state miminization algorithm
//     * @param stepQueue holds all distinguishing steps
//     * @param GroupSet is the set of equivalent state groups
//     * @param memo  remarks
//     */
//    private void recordDistinguishSteps(ArrayDeque<String> stepQueue, HashMap<Integer,HashMap<Integer, State>> GroupSet, String memo){
//        String str = "";
//        str = GroupSetToString(GroupSet);
//        str += ":" + memo;
//        stepQueue.add(str);
//    }
//
//    /**
//     * Display the equivalent state groups
//     * @param stepQueue
//     */
//    private void showDistinguishSteps(ArrayDeque<String> stepQueue){
//        int step = 0;
//        String str = "";
//        while(!stepQueue.isEmpty()){
//            str = stepQueue.poll();
//            System.out.println("Step" + step++ + ":\t" + str +"\r");
//        }
//    }

    private String GroupSetToString(HashMap<Integer,HashMap<Integer, State>> GroupSet){
        String str = "";
        for( Integer g: GroupSet.keySet()){
            String tmp = GroupToString(GroupSet.get(g));
            str += g +  ":" + tmp + "\t" ;
        }
        return str;
    }

    private String GroupToString(HashMap<Integer, State> group){
        String str = "";
        for(Integer k : group.keySet()){
            str += group.get(k).getId() + ":" + group.get(k).getType() + ",";
        }
        if(str.length()!=0) str = str.substring(0,str.length()-1);
        str = "{" + str + "}";
        return str;
    }
}
