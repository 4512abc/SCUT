package banking.UI;

import banking.domain.Bank;
import banking.domain.Customer;
import banking.DAO.CustomerDAO;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainWindow extends JFrame {
    private JList<String> customerList;
    private DefaultListModel<String> listModel;
    private JTextField firstNameField;
    private JTextField lastNameField;
    private JTextField searchField;

    public MainWindow() {
        setTitle("Bank Customer Management");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        Bank bank = Bank.getBank();
        listModel = new DefaultListModel<>();
        for (int i = 0; i < bank.getNumOfCustomers(); i++) {
            Customer customer = bank.getCustomer(i);
            listModel.addElement(customer.getFirstName() + " " + customer.getLastName());
        }
        customerList = new JList<>(listModel);
        JScrollPane scrollPane = new JScrollPane(customerList);

        firstNameField = new JTextField(15);
        lastNameField = new JTextField(15);
        searchField = new JTextField(15);

        JButton addButton = new JButton("Add");
        JButton deleteButton = new JButton("Delete");
        JButton searchButton = new JButton("Search");
        JButton sortButton = new JButton("Sort");

        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new GridLayout(3, 2));
        inputPanel.add(new JLabel("First Name:"));
        inputPanel.add(firstNameField);
        inputPanel.add(new JLabel("Last Name:"));
        inputPanel.add(lastNameField);
        inputPanel.add(new JLabel("Search:"));
        inputPanel.add(searchField);

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(addButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(searchButton);
        buttonPanel.add(sortButton);

        setLayout(new BorderLayout());
        add(scrollPane, BorderLayout.CENTER);
        add(inputPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.SOUTH);

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String firstName = firstNameField.getText();
                String lastName = lastNameField.getText();
                if (!firstName.isEmpty() && !lastName.isEmpty()) {
                    Bank.getBank().addCustomer(firstName, lastName);
                    listModel.addElement(firstName + " " + lastName);
                    firstNameField.setText("");
                    lastNameField.setText("");
                }
            }
        });

        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedIndex = customerList.getSelectedIndex();
                if (selectedIndex != -1) {
                    Bank.getBank().getCustomers().remove(selectedIndex);
                    listModel.remove(selectedIndex);
                }
            }
        });

        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String searchQuery = searchField.getText();
                listModel.clear();
                for (int i = 0; i < Bank.getBank().getNumOfCustomers(); i++) {
                    Customer customer = Bank.getBank().getCustomer(i);
                    if (customer.getFirstName().contains(searchQuery) || customer.getLastName().contains(searchQuery)) {
                        listModel.addElement(customer.getFirstName() + " " + customer.getLastName());
                    }
                }
            }
        });

        sortButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Bank.getBank().sortCustomers();
                listModel.clear();
                for (int i = 0; i < Bank.getBank().getNumOfCustomers(); i++) {
                    Customer customer = Bank.getBank().getCustomer(i);
                    listModel.addElement(customer.getFirstName() + " " + customer.getLastName());
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MainWindow window = new MainWindow();
            window.setVisible(true);
        });
    }
}