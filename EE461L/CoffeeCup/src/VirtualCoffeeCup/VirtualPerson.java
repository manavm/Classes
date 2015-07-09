package VirtualCoffeeCup;

public class VirtualPerson {
	int coldref;
	int hotref;
	
	public VirtualPerson(int tooCold, int tooHot){
		coldref = tooCold;
		hotref = tooHot;
	}
	
	public void drinkCoffee(VirtualCoffeeCup cup) throws TooHotException, TooColdException, TemperatureException{
		if(cup.getTemperature() >= hotref){
			throw new TooHotException("The temperature of " + cup.getTemperature() + " is too hot");
		}
		else if(cup.getTemperature() <= coldref){
			throw new TooColdException("The temperature of " + cup.getTemperature() + " is too hot");
		}
	}
}
