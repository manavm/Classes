package usa.texas.austin;

import java.util.Scanner;

public class HelloWorld {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Hello World");
        
	}
	
	public static int fibonacci(int number){
        if(number == 1 || number == 2){
            return 1;
        }
 
        return fibonacci(number-1) + fibonacci(number -2); //tail recursion
    }

}
