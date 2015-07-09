How to run the program:

- Unzip the provided zip file (VenmoApp.zip)
- Move to the parent directory (cd VenmoApp)

Run the script "runvenmo.sh" to launch the program. This can be run in 2 configurations:
- With no arguments to run interactively (bash runvenmo.sh)
- With filename as argument to run using a file input (bash runvenmo.sh <path_to_filename>)

Desing Decisions:

The program enters into a Runner class which delegates the task based on the command.
Commands are handled in a UserAction class which holds a method for every possible input. Any new commands added can be provided a method here in addition to existing methods.
The User class represents a particular user and holds the user's profile
Each transaction that occurs between users is represented using the Payment class that holds all the information associated with any payment.

The usernames are stored in a hashmap to provide quicker (O(1)) access.
Card numbers are stored as strings since a 19-digit number cannot fit using any primitive type. Even long cannot store larger 19-digit numbers. 

I chose to implement my solution using Java for it's object-oriented capabilities and my comfort with the langauge and its tools.

Assumptions made:

- Usernames are case-sensitive, command names are not
- Program execution finishes when user enters "quit"