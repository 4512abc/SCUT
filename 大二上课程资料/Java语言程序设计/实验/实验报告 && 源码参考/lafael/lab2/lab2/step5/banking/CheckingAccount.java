package banking;

public class CheckingAccount extends Account {
    private double overdraftProtection;

    public CheckingAccount(double balance) {
        super(balance);
        this.overdraftProtection = 0;
    }

    public CheckingAccount(double balance, double overdraftProtection) {
        super(balance);
        this.overdraftProtection = overdraftProtection;
    }

    @Override
    public boolean withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        } else if (overdraftProtection >= (amount - balance)) {
            overdraftProtection -= (amount - balance);
            balance = 0;
            return true;
        }
        return false;
    }

    public double getOverdraftProtection() {
        return overdraftProtection;
    }
}
