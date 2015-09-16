/**
 * Created by mahmud on 2015-09-16.
 */
public class Customer {
    private String name;
    private char gender;
    private String email;



    public Customer(String name){
        this.name=name;
    }
    public Customer(String name, String email, char gender){
        this.name=name;
        this.email=email;
        this.gender=gender;
    }
    public void setGender(char gender)
    {
        this.gender=gender;
    }
    public void setEmail(String email)
    {
        this.email=email;
    }
    public void print()
    {
        System.out.println(name+" ("+gender+") at "+email);
    }
    public String getName()
    {
        return name;
    }
    public String getEmail()
    {
        return email;
    }
    public char getGender()
    {
        return gender;
    }



}
