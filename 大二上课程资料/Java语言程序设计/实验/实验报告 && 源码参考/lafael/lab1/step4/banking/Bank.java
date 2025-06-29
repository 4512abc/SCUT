package banking;

public class Bank {
    private Customer[] customers;
    private int numberOfCustomers;

    // 构造函数初始化客户数组
    public Bank() {
        customers = new Customer[10];  // 数组容量至少为 5
        numberOfCustomers = 0;
    }

    // 添加客户
    public void addCustomer(String f, String l) {
        customers[numberOfCustomers] = new Customer(f, l);
        numberOfCustomers++;
    }

    // 获取客户数量
    public int getNumOfCustomers() {
        return numberOfCustomers;
    }

    // 获取指定索引的客户
    public Customer getCustomer(int index) {
        if (index >= 0 && index < numberOfCustomers) {
            return customers[index];
        }
        return null;
    }
}
