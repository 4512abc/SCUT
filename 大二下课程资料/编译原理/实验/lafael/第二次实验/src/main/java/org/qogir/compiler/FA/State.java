package org.qogir.compiler.FA;

import java.io.Serial;
import java.io.Serializable;
//import org.jetbrains.annotations.NotNull;

/**
 * State for finite automaton
 */
public class State implements Serializable {

    @Serial
    private static final long serialVersionUID = 3706097164927205436L;

    public static int STATE_ID = 0; //assign STATE_ID to a state

    /**
     * Every state has a unique id which can not be modified.
     */
    private final int id;//state id

    /**
     * Every state has a sid which can be assigned with new value and is used for display purpose.
     */
    private String sid;

    /**
     * currently, four types of state are supported
     * 0-start; 1-middle; 2-accept; 20-accept and start
     */
    public static final int START = 0;
    public static final int MIDDLE = 1;
    public static final int ACCEPT = 2;
    public static final int ACCEPTANDSTART = 20;
    private int type = MIDDLE;

    public State(){
        this.id = State.STATE_ID;
        this.sid = String.valueOf(this.id);
        STATE_ID += 1 ;
    }

    public State( State s){//@NotNull
        this.id = s.getId();
        this.type = s.getType();
        this.sid = s.getSid();
    }

    State(int type){
        this.id = State.STATE_ID;
        this.sid = String.valueOf(this.id);
        this.type = type;
        STATE_ID += 1 ;
    }

    public int getId() {
        return id;
    }

    public int getType() {
        return type;
    }

    public void setSid(String sid){
        this.sid = sid;
    }

    public String getSid() {
        return sid;
    }

    public void setType(int type) {
        this.type = type;
    }

    public boolean equals( State s){//@NotNull
        return this.id == s.getId() && this.type == s.getType();
    }

    @Override
    public String toString() {
        return this.id + ":" + this.type;
    }
}
