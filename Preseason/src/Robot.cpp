#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	Compressor *compressor;
	DoubleSolenoid *dS1;
	DoubleSolenoid *dS2;
	Joystick *stick;
	TalonSRX *frontLeft;
	TalonSRX *frontRight;
	TalonSRX *backLeft;
	TalonSRX *backRight;
	TalonSRX *lazySusan;
	RobotDrive *drive;
	//Encoder *encL;
	//Encoder *encR;
	float move = 0.0;
	float rotate = 0.0;
	//19.0896 rotations per 20 feet

	void RobotInit()
	{

		compressor = new Compressor(0);

		compressor->SetClosedLoopControl(true);


		//encL = new Encoder(0,1,false,Encoder:EncodingType::k4X);
		//encR = new Encoder(1,1,false,Encoder:ENcodingType::k4X);
		//encL->SetSamplesToAverage(7);
		//encR->SetSamplesToAverage(7);

		dS1 = new DoubleSolenoid(0, 2);
		dS2 = new DoubleSolenoid(1, 3);
		dS1->Set(DoubleSolenoid::Value::kOff);
		dS2->Set(DoubleSolenoid::Value::kOff);

		stick = new Joystick(0);

		frontLeft = new TalonSRX(1);
		backLeft = new TalonSRX(0);
		frontRight = new TalonSRX(8);
		backRight = new TalonSRX(9);
		lazySusan = new TalonSRX(4);

		drive = new RobotDrive(backLeft, frontLeft, backRight, frontRight);
	}
	void AutonomousInit()
	{
	}
	void AutonomousPeriodic()
	{
	}
	void TeleopInit()
	{

	}
	void TeleopPeriodic()
	{
		//left = 0.0;
		//right = 0.0;
		//left = stick->GetRawAxis(0);
		//right = stick->GetRawAxis(1);
		//left = stick-> GetRawAxis(1);
		//right = stick-> GetRawAxis(5);
		//drive->TankDrive(left, right);
		//drive->TankDrive(stick, 0, stick, 5, false);
		move = stick->GetRawAxis(5);
		rotate = stick->GetRawAxis(4);
		if(move <= .1)
		{
			move = 0.0;
		}
		if(rotate <= .1)
		{
			rotate = 0.0;
		}
		drive->ArcadeDrive(move, rotate, false);
		if(stick->GetRawAxis(3) == 0.0)
		{
			lazySusan->Set((-stick->GetRawAxis(2)) * .1);
		}
		else
		{
			lazySusan->Set((stick->GetRawAxis(3)) * .1);
		}
		if(stick->GetRawButton(5)) {
			dS1->Set(DoubleSolenoid::Value::kForward);
		}else{
			dS1->Set(DoubleSolenoid::Value::kReverse);
		}
		if(stick->GetRawButton(6)) {
			dS2->Set(DoubleSolenoid::Value::kForward);
		}else{
			dS2->Set(DoubleSolenoid::Value::kReverse);
		}
	}
	void TestPeriodic()
	{
	}
};
START_ROBOT_CLASS(Robot);
