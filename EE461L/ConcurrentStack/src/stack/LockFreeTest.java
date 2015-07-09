package stack;

import java.util.Random;

public class LockFreeTest implements Runnable{

	private int THREADS;
	LockFreeStack<Integer> lockFreeInstance;
	
	public LockFreeTest(LockFreeStack<Integer> lockFreeInstance_, int THREADS_){
		this.THREADS = THREADS_;
		this.lockFreeInstance = lockFreeInstance_;
	}
	
	public void run(){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		for(int i = 0; i < 25000 / THREADS; i++){
			int randomNum = rand.nextInt(10) + 1;
			if (randomNum <= 6){
				try {
					lockFreeInstance.push(random);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			else{
					try {
						lockFreeInstance.pop();
					} 
					catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (EmptyException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
			}
		}
	}
}
