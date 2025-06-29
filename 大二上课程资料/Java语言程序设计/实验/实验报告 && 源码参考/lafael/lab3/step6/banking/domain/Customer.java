package banking.domain;

import java.util.ArrayList;

public class Customer implements Comparable<Customer> {
    private String firstName;
    private String lastName;
    private ArrayList<Account> accounts;

    public Customer(String f, String l) {
        firstName = f;
        lastName = l;
        accounts = new ArrayList<>();
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void addAccount(Account account) {
        accounts.add(account);
    }

    public Account getAccount(int index) {
        return accounts.get(index);
    }

    public int getNumOfAccounts() {
        return accounts.size();
    }

    // 实现 Comparable 接口的 compareTo 方法
    @Override
    public int compareTo(Customer other) {
        // 比较姓氏，如果姓氏相同，则按名字排序
        int lastNameComparison = this.lastName.compareToIgnoreCase(other.lastName);
        if (lastNameComparison != 0) {
            return lastNameComparison;
        }
        return this.firstName.compareToIgnoreCase(other.firstName);
    }
}
