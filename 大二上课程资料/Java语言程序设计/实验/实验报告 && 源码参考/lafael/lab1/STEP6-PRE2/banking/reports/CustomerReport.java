package banking.reports;

import banking.domain.*;

public class CustomerReport {

    public void generateReport() {
        Bank bank = Bank.getBank();  // 使用单例 Bank 对象

        System.out.println("\t\t\tCUSTOMERS REPORT");
        System.out.println("\t\t\t================");

        for (int cust_idx = 0; cust_idx < bank.getNumOfCustomers(); cust_idx++) {
            Customer customer = bank.getCustomer(cust_idx);

            System.out.println();
            System.out.println("Customer: "
                    + customer.getLastName() + ", "
                    + customer.getFirstName());

            for (int acct_idx = 0; acct_idx < customer.getNumOfAccounts(); acct_idx++) {
                Account account = customer.getAccount(acct_idx);
                String account_type = "";

                if (account instanceof SavingsAccount) {
                    account_type = "Savings Account";
                } else if (account instanceof CheckingAccount) {
                    account_type = "Checking Account";
                }

                System.out.println("    " + account_type + ": current balance is € "
                        + String.format("%.2f", account.getBalance()));
            }
        }
    }
}
