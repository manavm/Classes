package stack;

import java.util.Random;

public class EliminationLockFreeTest implements Runnable{

	private int THREADS;
	EliminationBackoffStack<Integer> lockFreeInstance;
	
	public EliminationLockFreeTest(EliminationBackoffStack<Integer> lockFreeInstance_, int THREADS_){
		this.THREADS = THREADS_;
		this.lockFreeInstance = lockFreeInstance_;
	}
	
	public void run(){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		for(int i = 0; i < 25000 / THREADS; i++){
			int randomNum = rand.nextInt(10) + 1;
			if (randomNum <= 6){
					lockFreeInstance.push(random);
			}
			else{
					try {
						lockFreeInstance.pop();
					} 
					catch (EmptyException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
			}
		}
	}
}
