package command;

import java.net.*;
import java.io.*;

/**
 * This class is somewhat secondary to your assignment, but it's a good idea to figure
 * out what's going on in here. I've tried to insert some comments to give you some hints.
 */

// I'm a runnable. You'll make one of me for everyone one your "friends"
public class ChatServer implements Runnable {

    // my name
    private String name;
    // the network port I'm assigned; we're running everything on the localhost
    private int port;
    // the commands I know how to send (plus send you a message, of course)
    private static String[] sendStrings = {"BEEP", "VIBRATE", "QUIT"};
    // when this is true, this thread will die
    private boolean stopped = false;

    public ChatServer(String name, int port){
	this.name = name;
	this.port = port;
    }

    // this gets called by start()
    public void run(){
    	PrintWriter out = null;
	try{
	    // set up the server socket, and wait for the client to connect to it
	    ServerSocket serverSocket = new ServerSocket(port);
	    // accept is a blocking call. The server will wait here until the client
	    // connects from the other side
	    Socket clientSocket = serverSocket.accept();
	    // once we're connected, I'll get the stream I'll use to send you messages
	    out = new PrintWriter(clientSocket.getOutputStream(), true);
	}
	catch(IOException ioe){
	    ioe.printStackTrace();
	}
	// for simplicity, if I send you a message, I only ever send this same message
	String toPrint = name + " says hello!";
	// until I've stopped
	while(!stopped){
	    //select a random number between 0-3, inclusive
	    int randomNumber = (int)(Math.random() * 4);
	    // if I picked 3, I'll send you a hello text otherwise, I'll send you the string
	    // from above using the random number I picked as an index into my string array
	    if(randomNumber < 3){
		out.println(sendStrings[randomNumber]);
	    }
	    else{
		out.println(toPrint);
	    }
	    // If I sent you "QUIT" then I should stop this thread
	    if(randomNumber == 2){
		System.out.println("Server " + name + " is leaving");
		stopped = true;
	    }
	    else{
		// after I send you something, I'll sleep for a random bit then do it again
		try{
		    Thread.sleep((long)(Math.random() * 1000));
		}
		catch(InterruptedException ie){
		    ie.printStackTrace();
		}
	    }
	}
    }
}

    