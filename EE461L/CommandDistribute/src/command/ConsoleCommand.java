package command;

public class ConsoleCommand implements Command {
	private Console console;
	private String string;

    public ConsoleCommand(Console console, String string){
	this.console = console;
	this.string = string;
    }

    public void execute(){
	console.print(string);
    }
    // IMPLEMENT ME!

}