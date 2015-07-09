package stack;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Runner {
	
	private final static int THREADS = 1;
	static LockFreeStack<Integer> lockFreeInstance;
	static EliminationBackoffStack<Integer> EliminationlockFreeInstance;
	static UnboundedStack<Integer> lockBasedInstance;
	private static long finalTime;
	private static long startTime;

	public static void main(String[] args){
		System.out.println("For " + THREADS + " threads:");
		System.out.println();
		lockFreeInstance = new LockFreeStack<Integer>();
		EliminationlockFreeInstance = new EliminationBackoffStack<Integer>();
	    lockBasedInstance = new UnboundedStack<Integer>();
	    runLockFree(lockFreeInstance);
	    runEliminationLockFree(EliminationlockFreeInstance);
	    runLockBased(lockBasedInstance);
		
	}
	
	public static void runLockFree(LockFreeStack<Integer> lockFreeInstance){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		ExecutorService es = Executors.newFixedThreadPool(THREADS);
		for(int i = 0; i < 5000; i++){
			try {
				lockFreeInstance.push(random);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		startTime = System.currentTimeMillis();
		for(int i = 0; i < THREADS; i++){
			es.submit(new LockFreeTest(lockFreeInstance, THREADS));
		}
		es.shutdown();
		try{
			es.awaitTermination(60, TimeUnit.SECONDS);
		}
		catch(InterruptedException e){
			e.printStackTrace();
		}
		finalTime = System.currentTimeMillis() - startTime;
		
		System.out.println("For a lock free stack:");
		System.out.println("Execution time is:" + finalTime + "ms");
		System.out.println("Latency time is:" + (double) finalTime/25000 + "ms");
		System.out.println("Throughput:" + (25000/(double)finalTime)*100 + " operations per second");
		System.out.println();

	}
	
	public static void runEliminationLockFree(EliminationBackoffStack<Integer> EliminationlockFreeInstance){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		ExecutorService es = Executors.newFixedThreadPool(THREADS);
		for(int i = 0; i < 5000; i++){
					EliminationlockFreeInstance.push(random);
		}
		
		startTime = System.currentTimeMillis();
		for(int i = 0; i < THREADS; i++){
			es.submit(new LockFreeTest(lockFreeInstance, THREADS));
		}
		es.shutdown();
		try{
			es.awaitTermination(60, TimeUnit.SECONDS);
		}
		catch(InterruptedException e){
			e.printStackTrace();
		}
		finalTime = System.currentTimeMillis() - startTime;
		
		System.out.println("For a lock free stack using an elimination array:");
		System.out.println("Execution time is:" + finalTime + "ms");
		System.out.println("Latency time is:" + (double) finalTime/25000 + "ms");
		System.out.println("Throughput:" + (25000/(double)finalTime)*100 + " operations per second");
		System.out.println();

	}
	
	
	public static void runLockBased(UnboundedStack<Integer> lockBasedInstance){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		ExecutorService es = Executors.newFixedThreadPool(THREADS);
		for(int i = 0; i < 5000; i++){
			lockBasedInstance.push(random);
		}
		startTime = System.currentTimeMillis();
		for(int i = 0; i < THREADS; i++){
			es.submit(new LockBasedTest(lockBasedInstance, THREADS));
		}
		es.shutdown();
		try{
			es.awaitTermination(60, TimeUnit.SECONDS);
		}
		catch(InterruptedException e){
			e.printStackTrace();
		}
		finalTime = System.currentTimeMillis() - startTime;
		
		System.out.println("For a lock based stack:");
		System.out.println("Execution time is:" + finalTime + "ms");
		System.out.println("Latency time is:" + (double) finalTime/25000 + "ms");	
		System.out.println("Throughput:" + (25000/(double) finalTime)*100 + " operations per second");
		System.out.println("----------------------------------------------------");
	}
	
}
