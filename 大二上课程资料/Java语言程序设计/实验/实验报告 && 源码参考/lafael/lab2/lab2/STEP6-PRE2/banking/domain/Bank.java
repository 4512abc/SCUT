package banking.domain;

import java.util.ArrayList;

public class Bank {
    private static Bank instance = null; // 单例实例
    private ArrayList<Customer> customers;
    private int numberOfCustomers;

    // 构造函数设为私有
    private Bank() {
        customers = new ArrayList<>();
        numberOfCustomers = 0;
    }

    // 获取 Bank 单例实例的方法
    public static Bank getBank() {
        if (instance == null) {
            instance = new Bank();
        }
        return instance;
    }

    public void addCustomer(String f, String l) {
        customers.add(new Customer(f, l));
        numberOfCustomers++;
    }

    public int getNumOfCustomers() {
        return numberOfCustomers;
    }

    public Customer getCustomer(int index) {
        return customers.get(index);
    }
}
