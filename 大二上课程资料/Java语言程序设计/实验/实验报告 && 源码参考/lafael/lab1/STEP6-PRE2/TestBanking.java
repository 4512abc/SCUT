import banking.domain.*;
import banking.reports.CustomerReport;

public class TestBanking {

    public static void main(String[] args) {
        Bank bank = Bank.getBank();  // 使用单例 Bank 对象
        Customer customer;
        CustomerReport report = new CustomerReport();

        // 创建多个客户及其账户
        bank.addCustomer("Jane", "Simms");
        customer = bank.getCustomer(0);
        customer.addAccount(new SavingsAccount(500.00, 0.05));
        customer.addAccount(new CheckingAccount(200.00, 400.00));

        bank.addCustomer("Owen", "Bryant");
        customer = bank.getCustomer(1);
        customer.addAccount(new CheckingAccount(200.00));

        bank.addCustomer("Tim", "Soley");
        customer = bank.getCustomer(2);
        customer.addAccount(new SavingsAccount(1500.00, 0.05));
        customer.addAccount(new CheckingAccount(200.00));

        bank.addCustomer("Maria", "Soley");
        customer = bank.getCustomer(3);
        // Maria 和 Tim 共享一个账户
        customer.addAccount(bank.getCustomer(2).getAccount(1));
        customer.addAccount(new SavingsAccount(150.00, 0.05));

        // 生成报告
        report.generateReport();
    }
}
