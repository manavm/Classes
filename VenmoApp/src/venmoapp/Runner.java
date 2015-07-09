package venmoapp;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Runner {

	public static HashMap<String, User> userMap = new HashMap<String, User>();
	private static ArrayList<String> cards = new ArrayList<String>();

	public static void main(String[] args) {
		System.out.println("Welcome to SocPay 2.0. Please enter what you'd like to do:");
		// Run interactively through command-line
		if (args.length > 0) {
			try{
				FileInputStream fstream = new FileInputStream("/Users/manavm/Documents/workspace/VenmoApp/src/venmoapp/test_input.txt");
				BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
				String line = null;
				while ((line = br.readLine()) != null) {
					if(delegateTask(line))
						break;
				}
				br.close();
			}
			catch(IOException e){
				System.out.println("ERROR: file cannot be read");
			}
		}
		// Run using file input
		else{
			try(Scanner scanner = new Scanner(System.in);){
				while(true){
					String input = scanner.nextLine();
					if(delegateTask(input))
						break;
				}

			}
		}
		System.out.println("Thanks for using the App!");

	}

	/*
	 * Accepts User input and delegates task based on command
	 */
	public static boolean delegateTask(String input){
		UserAction action = new UserAction(userMap, cards);
		String[] parsed_input = input.split("\\s+");
		String command;
		try{
			command = parsed_input[0].toLowerCase();
			if(command.equals("quit") && parsed_input.length == 1)
				return true;
			else if (command.toLowerCase().equals("user")){
				try{
					action.addUser(parsed_input[1]);
				}
				catch(ArrayIndexOutOfBoundsException e){
					System.out.println("ERROR: invalid arguments");
				}
			}
			else if (command.toLowerCase().equals("add")){
				try{
					action.addCard(parsed_input[1], parsed_input[2]);
				}
				catch(ArrayIndexOutOfBoundsException e){
					System.out.println("ERROR: invalid arguments");
				}
			}
			else if (command.toLowerCase().equals("pay")){
				if(parsed_input.length < 5){
					System.out.println("ERROR: invalid arguments");
				}
				else if(!parsed_input[3].startsWith("$")){
					System.out.println("ERROR: invalid arguments");
				}
				else{
					float amount = Float.parseFloat(parsed_input[3].substring(1));			// Convert string to float
					String message = parsed_input[4];
					for(int i=5; i<parsed_input.length;i++){								// Concatenate strings to create message
						message = message + " " + parsed_input[i];
					}
					action.addPayment(parsed_input[1], parsed_input[2], amount, message);
				}
			}
			else if (command.toLowerCase().equals("feed")){
				try{
					action.getFeed(parsed_input[1]);
				}
				catch(ArrayIndexOutOfBoundsException e){
					System.out.println("ERROR: invalid arguments");
				}
			}
			else if (command.toLowerCase().equals("balance")){
				try{
					action.getBalance(parsed_input[1]);
				}
				catch(ArrayIndexOutOfBoundsException e){
					System.out.println("ERROR: invalid arguments");
				}
			}
			else{
				System.out.println("ERROR: command not recognized");
			}
			
		}
		catch(ArrayIndexOutOfBoundsException e){
			System.out.println("ERROR: command not recognized");
		}
		return false;
	}

}
