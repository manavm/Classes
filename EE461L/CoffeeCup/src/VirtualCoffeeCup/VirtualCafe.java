package VirtualCoffeeCup;

public class VirtualCafe {
	public static void serveCustomer(VirtualPerson customer, 
			VirtualCoffeeCup cup) { 
		try{ 
			customer.drinkCoffee(cup); 
		}  catch(TooHotException the) { 
			System.out.println("I'm so sorry. Let me get you an ice pack and a new cup of coffee."); 
		} catch(TooColdException tce) { 
			System.out.println("I'm so sorry. Let me get you new cup of coffee."); 
		} catch(TemperatureException te) {
			System.out.println("I'm sorry. Here's a new cup of coffee.");	
		}
	}
	
	public static void main(String[] args){
	    VirtualCoffeeCup cup1 = new 
	        VirtualCoffeeCup.Builder("Italian").temperature(180).build();
	    VirtualCoffeeCup cup2 = new
	        VirtualCoffeeCup.Builder("French").temperature(150).build(); 
	    VirtualPerson customer = new VirtualPerson(175, 185); 
	    VirtualCafe.serveCustomer(customer, cup1); 
	    VirtualCafe.serveCustomer(customer, cup2); 
	}

}
