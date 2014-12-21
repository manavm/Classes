package stack;
/*
 * queue.UnboundedQueue.java
 *
 * Created on March 8, 2006, 8:02 PM
 *
 * From "The Art of Multiprocessor Programming"
 * by Maurice Herlihy and Nir Shavit.
 * Copyright 2006 Elsevier Inc. All rights reserved.
 */

import java.util.concurrent.locks.ReentrantLock;

/**
 * Bounded, blocking queue
 * @param T item type
 * @author Maurice Herlihy
 */
public class UnboundedStack<T> {

    ReentrantLock lock;
    /**
     * First entry in queue.
     */
    Node head;
    /**
     * Last entry in queue.
     */
    Node tail;
    /**
     * Queue size.
     */
    int size;
    /**
     * Constructor.
     */
    public UnboundedStack() {
        head = null;
        lock = new ReentrantLock();
    }
    /**
     * @return remove first item in queue
     * @throws EmptyException
     *
     */
    public T pop() throws EmptyException {
        T result;
        lock.lock();
        try {
            if (head == null) {
                throw new EmptyException();
            }
            result = head.value;
            head = head.next;
        } finally {
            lock.unlock();
        }
        return result;
    }
    /**
     * Add item to top of queue.
     * @param x item to append
     */
    public void push(T x) {
        if (x == null) throw new NullPointerException();
        lock.lock();
        try {
            Node e = new Node(x);
            e.next = head;
            head = e;
        } finally {
            lock.unlock();
        }
    }

    /**
     * Individual queue item.
     */
    protected class Node {
        /**
         * Actual value of queue item.
         */
        public T value;
        /**
         * next item in queue
         */
        public Node next;
        /**
         * Constructor
         * @param x Value of item.
         */
        public Node(T x) {
            value = x;
            next = null;
        }
    }
}
