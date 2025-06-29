package banking.domain;

public class OverdraftException extends Exception {
    private double deficit;  // 亏空金额

    // 构造函数，接受消息和亏空金额
    public OverdraftException(String message, double deficit) {
        super(message);  // 调用父类构造函数传递消息
        this.deficit = deficit;
    }

    // 访问器方法，返回亏空金额
    public double getDeficit() {
        return deficit;
    }
}