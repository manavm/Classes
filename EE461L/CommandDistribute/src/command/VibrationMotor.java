package command;

// REFACTOR ME. I SHOULD BE A SINGLETON!

public class VibrationMotor {
	
	private static VibrationMotor instance = null;
    private VibrationMotor() {
    }
    
    public static VibrationMotor getInstance(){
    	if (instance == null){
    		synchronized(VibrationMotor.class){
    			if (instance == null){
    				instance = new VibrationMotor();
    			}
    		}
    	}
    	return instance;
    }


    public void vibrate() {
	System.out.println("Motor VIBRATE");
    }
}