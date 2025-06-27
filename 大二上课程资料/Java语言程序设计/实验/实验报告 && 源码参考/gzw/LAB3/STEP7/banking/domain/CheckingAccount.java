package banking.domain;
public class CheckingAccount extends Account{
    private double overdraftProtection;

    public CheckingAccount(double balance){
        super(balance);
    }
    public CheckingAccount(double balance, double protect){
        super(balance);
        this.overdraftProtection = protect;
    }
    public void withdraw(double amount) throws OverdraftException{
        if (amount <= balance + overdraftProtection){
            balance -= amount;
            if (balance < 0) {
                overdraftProtection += balance;
                balance = 0;
            }
        }
        else{
            if(overdraftProtection == 0){
                throw new OverdraftException("No overdraft protection", amount - balance);
            }
            else{
                throw new OverdraftException("Insufficient funds for overdraft protection", amount - balance - overdraftProtection);
            }
        }
    }
    public double getOverdraftProtection(){
        return overdraftProtection;
    }
}