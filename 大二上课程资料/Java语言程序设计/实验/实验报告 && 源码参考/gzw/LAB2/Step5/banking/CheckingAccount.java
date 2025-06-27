package banking;
public class CheckingAccount extends Account{
    private double overdraftProtection;

    public CheckingAccount(double balance){
        super(balance);
    }
    public CheckingAccount(double balance, double protect){
        super(balance);
        this.overdraftProtection = protect;
    }
    public boolean withdraw(double amount){
        if(amount > 0 && amount <= this.balance){
            this.balance -= amount;
            return true;
        }
        if(amount > 0 && amount > this.balance && amount <= this.balance + this.overdraftProtection){
            balance = 0;
            double remain = amount - balance;
            overdraftProtection -= remain;
            return true;
        }
        else return false;   
    }
    public double getOverdraftProtection(){
        return overdraftProtection;
    }
}