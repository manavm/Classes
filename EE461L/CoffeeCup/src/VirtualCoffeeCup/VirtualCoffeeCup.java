package VirtualCoffeeCup;

public class VirtualCoffeeCup {
	private final String roast;
	private final int temperature;
	
	public static class Builder{
		private final String roast;
		private int temperature;
		
		public Builder(String roast){
			this.roast = roast;
		}

		public Builder temperature(int temp){
			temperature = temp;
			return this;
		}
		
		public VirtualCoffeeCup build(){
			return new VirtualCoffeeCup(this);
		}
	}
	
	public String getRoast(){
		return roast;
	}

	public int getTemperature(){
		return temperature;
	}
	
	public VirtualCoffeeCup(Builder builder){
		roast = builder.roast;
		temperature = builder.temperature;
	}
	
}

