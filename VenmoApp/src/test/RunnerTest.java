package venmoapp;

import static org.junit.Assert.*;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

import org.junit.Test;

public class RunnerTest
{

  @Test
  public void testGivenInputs()
  {
	final ByteArrayOutputStream outContent = new ByteArrayOutputStream();  	  
    System.setOut(new PrintStream(outContent)); 	
	// Simulate input
    
    Runner.delegateTask("user Thomas");
    Runner.delegateTask("user Lisa");
    Runner.delegateTask("user");
    Runner.delegateTask("foobar");
    Runner.delegateTask("user Quincy");
    Runner.delegateTask("add Thomas 4111111111111111");
    Runner.delegateTask("add Thomas 5454545454545454");
    Runner.delegateTask("add Lisa 5454545454545454");
    Runner.delegateTask("add Quincy 1234567890123456");
    Runner.delegateTask("pay Thomas Lisa $10.25 burritos");
    Runner.delegateTask("pay Thomas Quincy $10.00 you're awesome");
    Runner.delegateTask("pay Lisa Quincy $5.00 pot-luck supplies");
    Runner.delegateTask("pay Thomas Thomas $1.00 to myself");
    Runner.delegateTask("pay Quincy Thomas $2.00 a subway card");
    Runner.delegateTask("add Quincy 5454545454545454");
    Runner.delegateTask("add Quincy 5555555555554444");
    Runner.delegateTask("pay Quincy Thomas $14.50 a redbull vodka");
    Runner.delegateTask("feed Quincy");
    Runner.delegateTask("balance Quincy");
    Runner.delegateTask("feed Thomas");
    Runner.delegateTask("feed Lisa");
    assertEquals("ERROR: invalid arguments\nERROR: command not recognized\nERROR: this user already has a valid credit card\nERROR: this card is invalid\nERROR: users cannot pay themselves\nERROR: this user does not have a credit card\nERROR: that card has already been added by another user, reported for fraud!\n-- Thomas paid you $10.00 for you're awesome\n-- Lisa paid you $5.00 for pot-luck supplies\n-- You paid Thomas $14.50 for a redbull vodka\n-- $15.00\n-- You paid Lisa $10.25 for burritos\n-- You paid Quincy $10.00 for you're awesome\n-- Quincy paid you $14.50 for a redbull vodka\n-- Thomas paid you $10.25 for burritos\n-- You paid Quincy $5.00 for pot-luck supplies\n", outContent.toString());
    
  }
  
  @Test
  public void testEmpty(){
	  final ByteArrayOutputStream outContent = new ByteArrayOutputStream();  
	  System.setOut(new PrintStream(outContent));
	  
	  System.setIn(new ByteArrayInputStream(" ".getBytes()));
	  Scanner inputScanner = new Scanner(System.in);
	  String input = inputScanner.nextLine();
	  Runner.delegateTask(input);
	  assertEquals("ERROR: command not recognized\n", outContent.toString());
  }


	@Test
	public void testDollarSign(){
	  final ByteArrayOutputStream outContent = new ByteArrayOutputStream();  
	  System.setOut(new PrintStream(outContent));
	  
	  System.setIn(new ByteArrayInputStream("pay Lisa Quincy 5 mamma mia".getBytes()));
	  Scanner inputScanner = new Scanner(System.in);
	  String input = inputScanner.nextLine();
	  Runner.delegateTask(input);
	  assertEquals("ERROR: invalid arguments\n", outContent.toString());
	}
	
	@Test
	public void testUserExistance(){
	  final ByteArrayOutputStream outContent = new ByteArrayOutputStream();  
	  System.setOut(new PrintStream(outContent));
	  
	  System.setIn(new ByteArrayInputStream("pay Jacob Quincy $5 mamma mia".getBytes()));
	  Scanner inputScanner = new Scanner(System.in);
	  String input = inputScanner.nextLine();
	  Runner.delegateTask(input);
	  assertEquals("ERROR: this user does not exist\n", outContent.toString());
	}

}
