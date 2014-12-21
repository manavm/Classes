package queue;

import java.util.Random;

public class LockFreeTest implements Runnable{

	private int THREADS;
	LockFreeQueue<Integer> lockFreeInstance;
	
	public LockFreeTest(LockFreeQueue<Integer> lockFreeInstance_, int THREADS_){
		this.THREADS = THREADS_;
		this.lockFreeInstance = lockFreeInstance_;
	}
	
	public void run(){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		for(int i = 0; i < 25000 / THREADS; i++){
			int randomNum = rand.nextInt(10) + 1;
			if (randomNum <= 6){
				lockFreeInstance.enq(random);
			}
			else{
				try {
					lockFreeInstance.deq();
				} catch (EmptyException e) {
					
				}
			}
		}
	}
}
