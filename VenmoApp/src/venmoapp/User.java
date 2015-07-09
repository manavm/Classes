package venmoapp;

import java.util.*;

public class User {
	private final String name;
	private double balance;
	private String cardNumber = null;		
	
	private ArrayList<Payment> payments = new ArrayList<Payment>();
			
	public User(String username, int balance){
		name = username;
		this.balance = balance;
	}
	
	public void addPayment(Payment pay){
		payments.add(pay);
	}
	
	public ArrayList<Payment> getPayments(){
		return payments;
	}
	
	public String getName() {
		return name;
	}
	
	public double getBalance() {
		return balance;
	}
	public void setBalance(double balance) {
		this.balance = balance;
	}
	
	public String getCardNumber() {
		return cardNumber;
	}
	public void setCardNumber(String cardNumber) {
		this.cardNumber = cardNumber;
	}
	
	
}
