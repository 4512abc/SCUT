
package banking;

public class Customer {
    private String firstName;
    private String lastName;
    private Account account;

    public Customer(String f, String l){
        this.firstName = f;
        this.lastName = l;
    }
    public String getFirstName(){
        return firstName;
    }
    public String getLastName(){
        return lastName;
    }
    public void setAccount(Account account_input){
        this.account = account_input;
    }
    public Account getAccount(){
        return this.account;
    }
}
