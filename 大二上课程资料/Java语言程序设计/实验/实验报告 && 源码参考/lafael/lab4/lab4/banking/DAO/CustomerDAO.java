package banking.DAO;

import banking.domain.Customer;
import banking.domain.Bank;

import java.io.*;
import java.util.ArrayList;

public class CustomerDAO {
    private static final String FILE_NAME = "customers.dat";

    public void saveCustomers(ArrayList<Customer> customers) {
        try (RandomAccessFile raf = new RandomAccessFile(FILE_NAME, "rw")) {
            raf.setLength(0); // Clear the file before writing
            for (Customer customer : customers) {
                FixedLengthStringIO.writeFixedLengthString(customer.getFirstName(), 32, raf);
                FixedLengthStringIO.writeFixedLengthString(customer.getLastName(), 32, raf);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public ArrayList<Customer> loadCustomers() {
        ArrayList<Customer> customers = new ArrayList<>();
        try (RandomAccessFile raf = new RandomAccessFile(FILE_NAME, "r")) {
            while (raf.getFilePointer() < raf.length()) {
                String firstName = FixedLengthStringIO.readFixedLengthString(32, raf).trim();
                String lastName = FixedLengthStringIO.readFixedLengthString(32, raf).trim();
                customers.add(new Customer(firstName, lastName));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return customers;
    }
}