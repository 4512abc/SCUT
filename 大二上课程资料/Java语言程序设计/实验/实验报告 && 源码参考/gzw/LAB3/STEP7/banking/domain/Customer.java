
package banking.domain;

import java.util.ArrayList;

public class Customer implements Comparable<Customer>{
    private String firstName;
    private String lastName;

    private ArrayList<Account> account;
    private int accountNumber;

    public Customer(String f, String l){
        this.firstName = f;
        this.lastName = l;
        this.accountNumber = 0;
        this.account = new ArrayList<Account>();
    }
    public String getFirstName(){
        return firstName;
    }
    public String getLastName(){
        return lastName;
    }
    public void addAccount(Account account_input){
        
        account.add(account_input);
        accountNumber ++;
    }
    public Account getAccount(int index){
        return account.get(index);
    }
    public int getNumOfAccounts(){
        return accountNumber;
    }

    @Override
    public int compareTo(Customer other){
        int lastNameCompare = lastName.compareTo(other.lastName);
        if(lastNameCompare != 0){
            return lastNameCompare;
        }
        return firstName.compareTo(other.firstName);
    }
}
