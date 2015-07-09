package command;

/* 
 * No need to touch this code. This just launches everything for you on the local
 * machine. The chat driver expects you to input at least one friend's name (you can enter
 * as many as you want). The driver then launches a ChatServer for each of your friends and 
 * a Chat client for you.
 */
public class ChatDriver {
    
    private static int startPort = 1977;

    public static void main(String[] args){
	if(args.length < 1){
	    System.err.println("You have to provide at least one name!");
	    System.exit(0);
	}
	for(int i = 0; i<args.length; i++){
	    (new Thread((new ChatServer(args[i], (startPort + i))))).start();
	}
	ChatClient c = new ChatClient(args.length, startPort);
	c.run();
    }
    
}