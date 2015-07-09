package command;

public class MotorVibrateCommand implements Command{
	private VibrationMotor vibMotor;

    public MotorVibrateCommand(VibrationMotor vibMotor){
	this.vibMotor = vibMotor;
    }

    public void execute(){
	vibMotor.vibrate();
    }
    // IMPLEMENT ME!

}