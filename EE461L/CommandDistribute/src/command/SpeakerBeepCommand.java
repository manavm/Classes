package command;

public class SpeakerBeepCommand implements Command{
    private Speaker speaker;

    public SpeakerBeepCommand(Speaker speaker){
	this.speaker = speaker;
    }

    public void execute(){
	speaker.beep();
    }

}