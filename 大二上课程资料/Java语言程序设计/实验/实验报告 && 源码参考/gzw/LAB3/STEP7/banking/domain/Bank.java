package banking.domain;

import java.util.Arrays;

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

    public void sortCustomers(){
        Arrays.sort(customers, 0, numberOfCustomers);
    }
    public void searchCustomers(String lName, String fName){
        for(int i = 0; i < numberOfCustomers; i++){
            if(customers[i].getLastName().equals(lName) && customers[i].getFirstName().equals(fName)){
                System.out.println("Customer found: " + customers[i].getLastName() + " " + customers[i].getFirstName());
            }
        }
    }
}
