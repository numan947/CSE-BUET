/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package muman.models;

/**
 *
 * @author ab9ma
 */
public class UserInfo {
    private String username;
    private String user_full_name;
    private String email;
    private String register_date;
    private String birth_date;
    private String region;

    public UserInfo(String username, String user_full_name, String email, String register_date, String birth_date, String region) {
        this.username = username;
        this.user_full_name = user_full_name;
        this.email = email;
        this.register_date = register_date;
        this.birth_date = birth_date;
        this.region = region;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getUser_full_name() {
        return user_full_name;
    }

    public void setUser_full_name(String user_full_name) {
        this.user_full_name = user_full_name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getRegister_date() {
        return register_date;
    }

    public void setRegister_date(String register_date) {
        this.register_date = register_date;
    }

    public String getBirth_date() {
        return birth_date;
    }

    public void setBirth_date(String birth_date) {
        this.birth_date = birth_date;
    }

    public String getRegion() {
        return region;
    }

    public void setRegion(String region) {
        this.region = region;
    }
    
    
    
    
    
    public String toTable(){
        return "<table>"
                + "<tr><td>Username</td><td>"+getUsername()+"</td></tr>"
                + "<tr><td>Full Name</td><td>"+user_full_name+"</td></tr>"
                + "<tr><td>Email</td><td>"+email+"</td></tr>"
                + "<tr><td>Register Date</td><td>"+register_date+"</td></tr>"
                + "<tr><td>Date of Birth</td><td>"+birth_date+"</td></tr>"
                + "<tr><td>Region</td><td>"+region+"</td></tr>"
                + "</table";
    }
    
}
