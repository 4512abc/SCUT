package banking.domain;

public class Account
{
    protected double balance;
    public Account(double init_balance){
        balance = init_balance;
    }
    public double getBalance(){
        return balance;
    }
    public boolean deposit(double amount){
        if(balance > 0){
            balance += amount;
            return true;
        }
        else{
            return false;
        }
    }
    public void withdraw(double amount) throws OverdraftException{
        if(balance > 0 && amount <= this.balance){
            balance -= amount;
        } else{
            throw new OverdraftException("Insufficient funds", amount - this.balance);
        }
    }
}

