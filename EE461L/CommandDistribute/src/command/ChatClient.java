package command;

import java.io.*;
import java.net.*;
import java.util.concurrent.*;

/*
 * This is the ChatClient. It's basically your controller for your side of chat things.
 * When it is created, the ChatClient creates and launches a dedicated listener thread for each
 * of the friends. Then the ChatClient processes commands that the friends send.
 */

public class ChatClient implements Runnable{

    private int numServers;
    private int startPort;

    // It's possible that I have SO MANY friends that I get too many messages to deal with at once.
    // Let's put them in a queue and deal with them one at a time.
    private LinkedBlockingQueue<Command> queue;

    public ChatClient(int numServers, int startPort){
	this.numServers = numServers;
	this.startPort = startPort;
	queue = new LinkedBlockingQueue<Command>();
	for(int i = 0; i<numServers; i++){
	    Socket nextSocket = null;
	    try{
		nextSocket = new Socket("127.0.0.1", (startPort+i));
	    }
	    catch(IOException ioe){
		ioe.printStackTrace();
	    }
	    (new Thread(new ChatListener(nextSocket, this))).start();
	}
}

    public void run(){
	System.out.println("Chat client started");
	while(true){
	    Command c = null;
	    try{
		c = queue.take();
	    }
	    catch(InterruptedException ie){
		ie.printStackTrace();
	    }
	    c.execute();
	    // WHAT SHOULD YOU DO WITH THE COMMAND?

	}
}

    /*
     * This is kind of something you should be familiar with. Do you know how to use queues?
     * Do you know what my comment embedded in the method below means?
     */
    public void enqueueCommand(Command c){
	// don't have to worry about thread safety because the queue is itself thread safe
	try{
	    queue.put(c);
	}
	catch(InterruptedException ie){
	    ie.printStackTrace();
	}
    }

}


