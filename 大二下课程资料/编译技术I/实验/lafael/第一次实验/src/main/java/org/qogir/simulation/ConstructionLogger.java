package org.qogir.simulation;

import java.util.ArrayDeque;

public class ConstructionLogger{

    private ArrayDeque<String> stepQueue;

    public ConstructionLogger(){
        stepQueue = new ArrayDeque<>();
    }

    public boolean addStep(){
        return false;
    }

}
