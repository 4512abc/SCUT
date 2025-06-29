package banking.domain;

public class Account {
    protected double balance;

    // 构造函数初始化余额
    public Account(double init_balance) {
        this.balance = init_balance;
    }

    // 获取当前余额
    public double getBalance() {
        return balance;
    }

    // 存款方法，返回 true
    public boolean deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            return true;
        }
        return false;
    }

    // 取款方法，条件化取款，返回 true 或 false
    public boolean withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
}

