package banking;

public class Bank{
    private int numberOfCustomers;
    private Customer[] customers;
    public Bank(){
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
}
