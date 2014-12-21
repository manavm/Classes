package stack;

import java.util.concurrent.TimeoutException;

public class EliminationBackoffStack<T> extends LockFreeStack<T> {
	static final int capacity = 50;
	EliminationArray<T> eliminationArray = new EliminationArray<T>(capacity); 
	static ThreadLocal<RangePolicy> policy = new ThreadLocal<RangePolicy>() {
		protected synchronized RangePolicy initialValue() { 
			return new RangePolicy(capacity);
		}
	};

	public void push(T value) {
		RangePolicy rangePolicy = policy.get(); Node node = new Node(value);
		while (true) {
			if (tryPush(node)) { 
				return;
			}
			else{
				try {
					T otherValue = eliminationArray.visit
							(value, rangePolicy.getRange()); 
					if (otherValue == null) {
						rangePolicy.recordEliminationSuccess();
						return; // exchanged with pop }
					}
				}
				catch (TimeoutException ex) { 
					rangePolicy.recordEliminationTimeout();
				}
			}
		}
	}


	public T pop() throws EmptyException { 
		RangePolicy rangePolicy = policy.get(); 
		while (true) {
			Node returnNode = tryPop(); 
			if (returnNode != null) {
				return (T) returnNode.value;
			}
			else try {
				T otherValue = eliminationArray.visit(null, rangePolicy.getRange()); 
				if (otherValue != null) {
					rangePolicy.recordEliminationSuccess();
					return otherValue; 
				}
			}
			catch (TimeoutException ex) { 
				rangePolicy.recordEliminationTimeout();
			}
		}
	}
}
