package banking.domain;

public class CheckingAccount extends Account {
    private double overdraftProtection;

    // 构造函数，初始化余额和透支保护
    public CheckingAccount(double balance) {
        super(balance);
        this.overdraftProtection = 0;
    }

    public CheckingAccount(double balance, double overdraftProtection) {
        super(balance);
        this.overdraftProtection = overdraftProtection;
    }

    // 重写 withdraw 方法，抛出 OverdraftException 异常
    @Override
    public void withdraw(double amount) throws OverdraftException {
        if (balance >= amount) {
            balance -= amount;
        } else if (overdraftProtection >= (amount - balance)) {
            overdraftProtection -= (amount - balance);
            balance = 0;
        } else {
            // 根据情况抛出不同的异常
            if (overdraftProtection == 0) {
                throw new OverdraftException("No overdraft protection", amount - balance);
            } else {
                throw new OverdraftException("Insufficient funds for overdraft protection", amount - balance);
            }
        }
    }

    // 获取透支保护金额
    public double getOverdraftProtection() {
        return overdraftProtection;
    }
}