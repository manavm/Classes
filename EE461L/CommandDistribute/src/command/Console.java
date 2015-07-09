package command;

// REFACTOR ME. I SHOULD BE A SINGLETON!

public class Console{
    private static Console instance = null;
    private Console(){
    }
    
    public static Console getInstance(){
    	if (instance == null){
    		synchronized(Console.class){
    			if (instance == null){
    				instance = new Console();
    			}
    		}
    	}
    	return instance;
    }


    public void print(String toPrint){
	System.out.println(toPrint);
    }
}