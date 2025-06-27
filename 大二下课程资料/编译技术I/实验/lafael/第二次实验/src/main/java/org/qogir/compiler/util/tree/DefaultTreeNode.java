package org.qogir.compiler.util.tree;

import java.io.Serial;
import java.io.Serializable;

public class DefaultTreeNode implements Serializable {
    @Serial
    private static final long serialVersionUID = -7535431420416610980L;

    private DefaultTreeNode firstChild;
    private DefaultTreeNode nextSibling;

    public DefaultTreeNode(){
        this.firstChild = null;
        this.nextSibling = null;
    }

    public DefaultTreeNode(DefaultTreeNode firstChild, DefaultTreeNode nextSibling){
        this.firstChild = firstChild;
        this.nextSibling = nextSibling;
    }

    public void setFirstChild(DefaultTreeNode firstChild) {
        this.firstChild = firstChild;
    }

    public DefaultTreeNode getFirstChild() {
        return firstChild;
    }

    public void setNextSibling(DefaultTreeNode nextSibling) {
        this.nextSibling = nextSibling;
    }

    public DefaultTreeNode getNextSibling() {
        return nextSibling;
    }
}
