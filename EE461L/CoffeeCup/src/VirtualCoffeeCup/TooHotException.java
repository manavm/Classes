package VirtualCoffeeCup;

class TooHotException extends TemperatureException{
	String message;
	int temperature;
	
	public TooHotException(String message){
		super(message);
		this.message = message;
	}
	
	public String getMessage(){
		return message;
	}
	

	
}
