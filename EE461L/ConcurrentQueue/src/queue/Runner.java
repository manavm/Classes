package queue;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Runner {
	
	private final static int THREADS = 1;
	static LockFreeQueue<Integer> lockFreeInstance;
	static UnboundedQueue<Integer> lockBasedInstance;
	private static long finalTime;
	private static long startTime;

	public static void main(String[] args){
		System.out.println("For " + THREADS + " threads:");
		System.out.println();
		lockFreeInstance = new LockFreeQueue<Integer>();
	    lockBasedInstance = new UnboundedQueue<Integer>();
	    runLockFree(lockFreeInstance);
	    runLockBased(lockBasedInstance);
		
	}
	
	public static void runLockFree(LockFreeQueue<Integer> lockFreeInstance){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		ExecutorService es = Executors.newFixedThreadPool(THREADS);
		for(int i = 0; i < 5000; i++){
			lockFreeInstance.enq(random);
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
		
		System.out.println("For a lock free queue:");
		System.out.println("Execution time is:" + finalTime + "ms");
		System.out.println("Latency time is:" + (double) finalTime/25000 + "ms");
		System.out.println("Throughput:" + (25000/(double)finalTime)*100 + " operations per second");
		System.out.println();

	}
	
	public static void runLockBased(UnboundedQueue<Integer> lockBasedInstance){
		Random rand = new Random();
	    int random = rand.nextInt(100000) + 1;
		ExecutorService es = Executors.newFixedThreadPool(THREADS);
		for(int i = 0; i < 5000; i++){
			lockBasedInstance.enq(random);
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
		
		System.out.println("For a lock based queue:");
		System.out.println("Execution time is:" + finalTime + "ms");
		System.out.println("Latency time is:" + (double) finalTime/25000 + "ms");	
		System.out.println("Throughput:" + (25000/(double) finalTime)*100 + " operations per second");
		System.out.println("----------------------------------------------------");
	}
}
