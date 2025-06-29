package banking;

public class Account {
    // 声明余额属性
    private double balance;

    // 构造函数初始化余额
    public Account(double init_balance) {
        this.balance = init_balance;
    }

    // 获取当前余额
    public double getBalance() {
        return balance;
    }

    // 存款方法
    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // 取款方法
    public void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
    }
}
