package queue;

import java.util.Random;

public class LockBasedTest implements Runnable{

	private int THREADS;
	UnboundedQueue<Integer> lockBasedInstance;
	
	public LockBasedTest(UnboundedQueue<Integer> lockBasedInstance_, int THREADS_){
		this.THREADS = THREADS_;
		this.lockBasedInstance = lockBasedInstance_;
	}
	
	public void run(){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		for(int i = 0; i < 25000 / THREADS; i++){
			int randomNum = rand.nextInt(10) + 1;
			if (randomNum <= 6){
				lockBasedInstance.enq(random);
			}
			else{
				try {
					lockBasedInstance.deq();
				} catch (EmptyException e) {
					e.printStackTrace();
				}
			}
		}
	}
}