package banking.domain;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Bank {
    private static Bank instance = new Bank();
    private List<Customer> customers = new ArrayList<>();

    private Bank() {}

    public static Bank getBank() {
        return instance;
    }

    public int getNumOfCustomers() {
        return customers.size();
    }

    public Customer getCustomer(int index) {
        return customers.get(index);
    }

    public void addCustomer(String firstName, String lastName) {
        customers.add(new Customer(firstName, lastName));
    }

    public void sortCustomers() {
        Collections.sort(customers, (c1, c2) -> c1.getLastName().compareTo(c2.getLastName()));
    }

    // 添加这个方法
    public List<Customer> getCustomers() {
        return customers;
    }
}