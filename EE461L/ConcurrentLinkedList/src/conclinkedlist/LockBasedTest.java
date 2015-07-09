package conclinkedlist;

import java.util.Random;

public class LockBasedTest implements Runnable{

	private int THREADS;
	LazyList<Integer> lockBasedInstance;
	
	public LockBasedTest(LazyList<Integer> lockBasedInstance_, int THREADS_){
		this.THREADS = THREADS_;
		this.lockBasedInstance = lockBasedInstance_;
	}
	
	public void run(){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		for(int i = 0; i < 25000 / THREADS; i++){
			int randomNum = rand.nextInt(10) + 1;
			if (randomNum <= 4){
				lockBasedInstance.add(random);
			}
			if (randomNum <= 9){
				lockBasedInstance.contains(random);
			}
			else{
				lockBasedInstance.remove(random);
			}
		}
	}
}
