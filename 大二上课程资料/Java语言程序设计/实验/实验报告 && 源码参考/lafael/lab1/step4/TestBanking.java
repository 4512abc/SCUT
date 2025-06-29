import banking.*;

public class TestBanking {

  public static void main(String[] args) {
    Bank bank = new Bank();

    // 添加客户
    bank.addCustomer("Jane", "Simms");
    bank.addCustomer("Owen", "Bryant");
    bank.addCustomer("Tim", "Soley");
    bank.addCustomer("Maria", "Soley");

    // 输出客户信息
    for (int i = 0; i < bank.getNumOfCustomers(); i++) {
        Customer customer = bank.getCustomer(i);
        System.out.println("Customer [" + (i+1) + "] is " + customer.getLastName() + ", " + customer.getFirstName());
    }
  }
}
