package conclinkedlist;

import java.util.Random;

public class LockFreeTest implements Runnable{

	private int THREADS;
	LockFreeList<Integer> lockFreeInstance;
	
	public LockFreeTest(LockFreeList<Integer> lockFreeInstance_, int THREADS_){
		this.THREADS = THREADS_;
		this.lockFreeInstance = lockFreeInstance_;
	}
	
	public void run(){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		for(int i = 0; i < 25000 / THREADS; i++){
			int randomNum = rand.nextInt(10) + 1;
			if (randomNum <= 4){
				lockFreeInstance.add(random);
			}
			if (randomNum <= 9){
				lockFreeInstance.contains(random);
			}
			else{
				lockFreeInstance.remove(random);
			}
		}
	}
}
