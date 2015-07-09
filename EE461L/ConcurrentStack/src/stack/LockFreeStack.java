package stack;

import java.util.concurrent.atomic.AtomicReference;

public class LockFreeStack<T> {
	AtomicReference<Node> top = new AtomicReference<Node>(null); 
	static final int MIN_DELAY = 100;
	static final int MAX_DELAY = 10000;
	Backoff backoff = new Backoff(MIN_DELAY, MAX_DELAY);
	
	protected boolean tryPush(Node node){
		Node oldTop = top.get();
		node.next = oldTop; return(top.compareAndSet(oldTop, node));
	}
	public void push(T value) throws InterruptedException {
		Node node = new Node(value); 
		while (true) {
			if (tryPush(node)) { 
				return;
			} else { 
				backoff.backoff();
			}
		}
	}

	protected Node tryPop() throws EmptyException { 
		Node oldTop = top.get();
		if (oldTop == null) {
			throw new EmptyException();
		}
		Node newTop = oldTop.next;
		if (top.compareAndSet(oldTop, newTop)) 
		{
				return oldTop; 
			}
		else
		{
			return null;
		}
	}



public T pop() throws EmptyException, InterruptedException {
	while (true) {
		Node returnNode = tryPop(); 
		if (returnNode != null) {
			return (T) returnNode.value; 
			} 
		else {
				backoff.backoff();
			}
		}
	}	
}