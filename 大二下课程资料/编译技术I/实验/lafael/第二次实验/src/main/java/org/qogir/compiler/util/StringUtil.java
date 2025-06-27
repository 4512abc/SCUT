package org.qogir.compiler.util;

/**
 * A String object tool
 * @author xuyang
 */

public class StringUtil {

    public StringUtil(){

    }

    /**
     * Remove all space in strings.
     * @param string to be trimmed
     * @return trimmed string
     * @author xuyang
     */
    public String trim(String string){
        if(string == null)
            return null;
        StringBuilder trimmedString = new StringBuilder();
        for(char ch : string.toCharArray()){
            if(ch != ' '){
                trimmedString.append(ch);
            }
        }
        return trimmedString.toString();
    }
}
