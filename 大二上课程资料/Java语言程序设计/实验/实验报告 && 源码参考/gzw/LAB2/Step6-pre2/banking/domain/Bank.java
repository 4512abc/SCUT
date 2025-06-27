package banking.domain;

public class Bank{
    private static Bank instance;

    private int numberOfCustomers;
    private Customer[] customers;
    private Bank(){
        numberOfCustomers = 0;
        customers = new Customer[10];
    }
    public void addCustomer(String f, String l){
        customers[numberOfCustomers] = new Customer(f, l);
        numberOfCustomers ++;
    }
    public int getNumOfCustomers(){
        return numberOfCustomers;
    }
    public Customer getCustomer(int index){
        return customers[index];
    }
    public static Bank getBank(){
        if(instance == null){
            instance = new Bank();
        }
        return instance;
    }
}
