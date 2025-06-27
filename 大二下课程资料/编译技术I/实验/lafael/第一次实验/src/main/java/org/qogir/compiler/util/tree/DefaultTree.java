package org.qogir.compiler.util.tree;

import java.io.Serial;
import java.io.Serializable;

public class DefaultTree<N> implements Serializable {
    @Serial
    private static final long serialVersionUID = 2002054322029286840L;

    protected N root;

    public DefaultTree(){
        this.root = null;
    }

    public DefaultTree(N rt){
        this.root = rt;
    }

    public N getRoot() {
        return root;
    }

    public void setRoot(N root) {
        this.root = root;
    }

}
