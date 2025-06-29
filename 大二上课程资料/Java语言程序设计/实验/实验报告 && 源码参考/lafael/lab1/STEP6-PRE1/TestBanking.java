/*
 * This class creates the program to test the banking classes.
 * It creates a set of customers, with a few accounts each,
 * and generates a report of current account balances.
 */

import banking.*;
import java.text.NumberFormat;

public class TestBanking {

  public static void main(String[] args) {
    NumberFormat currency_format = NumberFormat.getCurrencyInstance();
    Bank     bank = new Bank();
    Customer customer;

    // Create several customers and their accounts
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
    // Maria and Tim have a shared checking account
    customer.addAccount(bank.getCustomer(2).getAccount(1));
    customer.addAccount(new SavingsAccount(150.00, 0.05));

    // Generate a report
    System.out.println("\t\t\tCUSTOMERS REPORT");
    System.out.println("\t\t\t================");

    for ( int cust_idx = 0; cust_idx < bank.getNumOfCustomers(); cust_idx++ ) {
      customer = bank.getCustomer(cust_idx);

      System.out.println();
      System.out.println("Customer: "
			 + customer.getLastName() + ", "
			 + customer.getFirstName());

      for ( int acct_idx = 0; acct_idx < customer.getNumOfAccounts(); acct_idx++ ) {
	Account account = customer.getAccount(acct_idx);
	String  account_type = "";

// Step 1: 确定账户类型
if (account instanceof SavingsAccount) {
  account_type = "Savings Account";
} else if (account instanceof CheckingAccount) {
  account_type = "Checking Account";
}

// Step 2: 打印账户类型和余额
System.out.println("    " + account_type + ": current balance is " 
  + currency_format.format(account.getBalance()));
      }
    }
  }
}
