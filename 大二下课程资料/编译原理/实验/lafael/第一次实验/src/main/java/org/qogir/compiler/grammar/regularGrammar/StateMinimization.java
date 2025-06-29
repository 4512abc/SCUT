package org.qogir.compiler.grammar.regularGrammar;


import org.qogir.compiler.FA.State;
import org.qogir.compiler.util.graph.LabelEdge;
import org.qogir.compiler.util.graph.LabeledDirectedGraph;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.HashMap;

//最小化DFA
public class StateMinimization {

    /**
     * Distinguish non-equivalent states in the given DFA.
     * @param dfa the original dfa.
     * @return distinguished equivalent state groups
     */
    private HashMap<Integer,HashMap<Integer, State>> distinguishEquivalentState(RDFA dfa){
        //Add your implementation

        HashMap<Integer,HashMap<Integer, State>> groupSet = new HashMap<>(); // group set
        return groupSet;
    }

    public RDFA minimize(RDFA dfa){

        //Add your implementation

        return null;
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
