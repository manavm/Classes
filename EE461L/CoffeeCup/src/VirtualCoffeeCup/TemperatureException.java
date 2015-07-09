package VirtualCoffeeCup;

public class TemperatureException extends Exception{
	String message;
	public TemperatureException(String message){
		System.out.println(message);
	}
}
