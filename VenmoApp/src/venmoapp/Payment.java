package venmoapp;

public class Payment {
	
	private String from_user;	// Actor
	private String to_user;		// Target
	private float amount;
	private String message;
	
	public Payment(String from_user, String to_user, float amount,
			String message) {
		this.from_user = from_user;
		this.to_user = to_user;
		this.amount = amount;
		this.message = message;
	}
	
	public String getFrom_user() {
		return from_user;
	}
	public void setFrom_user(String from_user) {
		this.from_user = from_user;
	}
	public String getTo_user() {
		return to_user;
	}
	public void setTo_user(String to_user) {
		this.to_user = to_user;
	}
	public float getAmount() {
		return amount;
	}
	public void setAmount(float amount) {
		this.amount = amount;
	}
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
}
