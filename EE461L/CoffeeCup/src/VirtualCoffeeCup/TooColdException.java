package VirtualCoffeeCup;

class TooColdException extends TemperatureException{
	String message;
	
	public TooColdException(String message){
		super(message);
		this.message = message;
	}
	
	public String getMessage(){
		return message;
	}

	
}
