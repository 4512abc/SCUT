
package banking;

public class Account
{
    private double balance;
    public Account(double init_balance){
        balance = init_balance;
    }
    public double getBalance(){
        return balance;
    }
    public void deposit(double amount){
        if(balance > 0)
            balance += amount;
        else
            System.out.println("存的钱必须是正数");
    }
    public void withdraw(double amount){
        if(balance > 0)
            balance -= amount;
        else
            System.out.println("取出的钱必须是正数");
    }
}