package command;

// REFACTOR ME. I SHOULD BE A SINGLETON!

public class Speaker {
	private static Speaker instance = null;
    private Speaker() {
    }
    
    public static Speaker getInstance(){
    	if (instance == null){
    		synchronized(Speaker.class){
    			if (instance == null){
    				instance = new Speaker();
    			}
    		}
    	}
    	return instance;
    }
    
    public void beep() {
	System.out.println("Speaker BEEP!");
    }
}