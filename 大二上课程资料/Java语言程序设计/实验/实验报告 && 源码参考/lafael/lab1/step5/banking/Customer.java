package banking;

public class Customer {
    // 声明私有属性
    private String firstName;
    private String lastName;
    private Account account;

    // 构造函数初始化 firstName 和 lastName
    public Customer(String f, String l) {
        this.firstName = f;
        this.lastName = l;
    }

    // 获取 firstName
    public String getFirstName() {
        return firstName;
    }

    // 获取 lastName
    public String getLastName() {
        return lastName;
    }

    // 设置账户
    public void setAccount(Account account) {
        this.account = account;
    }

    // 获取账户
    public Account getAccount() {
        return account;
    }
}
