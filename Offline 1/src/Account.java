/**
 * Created by numan947 on 2015-09-16.
 */
public class Account {

    private Customer customer;
    private int accountNumber;
    private double balance;
    private String branch;


    public Account(Customer customer, int accountNumber,double balance)
    {
        this.balance=balance;
        this.accountNumber=accountNumber;
        this.customer=customer;
    }
    public Account(Customer customer,int accountNumber, String branch)
    {
        this.customer=customer;
        this.accountNumber=accountNumber;
        this.branch=branch;
        this.balance=0;
    }
    public void setBranch(String branch)
    {
        this.branch=branch;
    }
    public void credit(double amount)
    {
        this.balance+=amount;
    }
    public void debit(double amount)
    {
        if(balance>=amount)
            this.balance-=amount;
        else
        System.out.println("Amount withdrawn exceeds the current balance!");
    }
    public String getCustomerName()
    {
        return this.customer.getName();
    }
    public String getBranch()
    {
        return this.branch;
    }
    public int getAccountNumber()
    {
        return this.accountNumber;
    }
    public double getBalance()
    {
        return this.balance;
    }
    public void print() {
        System.out.println("Customer: " + this.customer.getName() + " Branch: " + this.getBranch() + " A/C no: " + this.getAccountNumber() + " Balance " + this.getBalance());
    }
    public void setBalance(double balance)
    {
        this.balance=balance;
    }
    public Customer getCustomer()
    {
        return this.customer;
    }
}
