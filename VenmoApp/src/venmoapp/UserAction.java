package venmoapp;

import java.util.ArrayList;
import java.util.HashMap;

public class UserAction {
	
	public HashMap<String, User> userMap;
	public ArrayList<String> cards;
	
	public UserAction(HashMap<String, User> userMap, ArrayList<String> cards){
		this.userMap = userMap;
		this.cards = cards;
	}
	
	/*
	 * Add user to existing session
	 */
	public void addUser(String username){
		String pattern= "^[a-zA-Z0-9_-]*$";
		if(!username.matches(pattern)){								// Check if alphanumeric with underscores and dashes
			System.out.println("ERROR: invalid arguments(1)");
		}
		if (username.length() <= 4 && username.length() >= 15){		// Check if appropriate length
			System.out.println("ERROR: invalid arguments");
		}
		User newUser = new User(username, 0);
		userMap.put(username, newUser);
	}

	/*
	 * Validate card number and add it to user profile
	 */
	public void addCard(String username, String card_number){
		int card_length = card_number.length();
		int[] card_digits = new int[card_length];
		User user = userMap.get(username);

		for(int i=0;i<card_length;i++) {
			card_digits[i] = Integer.parseInt(String.valueOf(card_number.charAt(i)));
		}
		for(String card: cards){
			if (card_number.equals(card)){
				System.out.println("ERROR: that card has already been added by another user, reported for fraud!");
				return;
			}
		}
		if(user == null){
			System.out.println("ERROR: this user does not exist");
		}
		else if(card_length > 19){
			System.out.println("ERROR: this card is invalid(1)");
		}
		else if(!luhnCheck(card_digits)){
			System.out.println("ERROR: this card is invalid");
		}
		else if(user.getCardNumber() != null){
			System.out.println("ERROR: this user already has a valid credit card");
		}
		else{
			cards.add(card_number);
			user.setCardNumber(card_number);
		}
	}	

	public boolean luhnCheck(int[] digits) {
		int sum = 0;
		int length = digits.length;
		for (int i = 0; i < length; i++) {
			int digit = digits[length - i - 1];
			if (i % 2 == 1) {
				digit *= 2;
			}
			sum += digit > 9 ? digit - 9 : digit;
		}
		return sum % 10 == 0;
	}

	/*
	 *	Create a new payment object and link it to user profiles 
	 */
	public  void addPayment(String from_user, String end_user, float amount, String message){
		//		System.out.println(message);
		//		System.out.println(amount);
		User fromUser = userMap.get(from_user);
		User endUser = userMap.get(end_user);

		if(fromUser == null || endUser == null){
			System.out.println("ERROR: this user does not exist");
		}
		else if(from_user.equals(end_user)){
			System.out.println("ERROR: users cannot pay themselves");
		}
		else if(fromUser.getCardNumber() == null){
			System.out.println("ERROR: this user does not have a credit card");
		}
		else{
			Payment pay = new Payment(from_user, end_user, amount, message);

			fromUser.addPayment(pay);
			endUser.addPayment(pay);

			endUser.setBalance(endUser.getBalance() + amount);
		}
	}

	/*
	 * Retrieve user feed
	 */
	public void getFeed(String username){
		User user = userMap.get(username);
		if(user == null){
			System.out.println("ERROR: this user does not exist");
		}
		else{
			ArrayList<Payment> payments = user.getPayments();

			for(Payment payment: payments){
				if(payment.getFrom_user().equals(username)){
					System.out.println("-- You paid " + payment.getTo_user() + " $" + String.format("%.2f", payment.getAmount()) + " for " + payment.getMessage());
				}
				else if(payment.getTo_user().equals(username)){
					System.out.println("-- " + payment.getFrom_user() + " paid you $" + String.format("%.2f", payment.getAmount()) + " for " + payment.getMessage());
				}
			}
		}
	}

	/*
	 * Retrieve balance from user profile
	 */
	public void getBalance(String username){
		User user = userMap.get(username);
		if(user == null){
			System.out.println("ERROR: this user does not exist");
		}
		else{
			System.out.println("-- $" + String.format("%.2f", user.getBalance()));
		}
	}
}
