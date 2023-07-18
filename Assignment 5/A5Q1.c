/*
Michael McPhee and Ryan Scomazzon
A5Q1.c
October 25, 2022
program that drives robot in square until button press and reverses direction when hit
*/


void configureAllSensors(); //configures all sensors to standard configuration
void drive(int motor_power); //powers both drive motors with the same power
void driveBoth (int motor_power_A, int motor_power_D); //powers both motors independently
void waitButton(TEV3Buttons button_name);  // wait for push and release of specified button

/*
If you chose to do the bonus, replace this text with a description of the improvements made on the rotateRobot function
and reasoning behind them

To make the rotation more accurate, we made it so the motor eases into the end of its rotation. Past a vertain point, the speed of
the motors slowly begins to fade off based on how far it is from its desired rotation. This means the motor will gradually slow down
and finish at a low speed, so the angular momentum will be minimal to prevent overshooting.
*/
void rotateRobot(int angle) //rotates robot in place to given angle then stops. Positive angles are clockwise when viewed from above
{
	const int ROTATESPEED = 20;
	const int SLOWFACTOR = 5;

	resetGyro(S4);
	int WheelDirA = 0;
	int WheelDirB = 0;

	if (angle>0)
	{
		WheelDirA = -1;
		WheelDirB = 1;
	}
	else
	{
		WheelDirA = 1;
		WheelDirB = -1;
	}

	int speed = 0;

	while (abs(getGyroDegrees(S4))<abs(angle))
	{
		if (getButtonPress(buttonEnter))
		{
			angle = 0;
		}

		speed = ROTATESPEED * (abs(angle) - abs(getGyroDegrees(S4)))/SLOWFACTOR ;

		if (speed > 1) speed = 1; 
		else if (speed < -1) speed = -1;

		driveBoth(ROTATESPEED*WheelDirA*speed, ROTATESPEED*WheelDirB*speed);
	}

	drive(0);
}


/*
If you chose to do the bonus, replace this text with a description of the improvements made on the driveDistance function
and reasoning behind them

To prevent overshooting, we made it so our code eases into a stop by slowing down based on how fir it is from its desired location. 
The motor gets slower as it approaches the target to minimize momentum pushing it past the target
*/

int driveDistance(int distance, int direction) //drives robot straight for given distance based on motor encoders and nominal wheel diameter. Positive distance is forward
{
	const int DRIVESPEED = 50;
	const int SLOWFACTOR = 5;

	int turn = direction;
	nMotorEncoder[motorA]=0;
	const float CM_TO_DEG = 180/(2.75*PI);
	int speed = DRIVESPEED;


	while (abs(nMotorEncoder[motorA])<abs(distance*CM_TO_DEG))
	{
		speed = (abs(distance*CM_TO_DEG) - abs(nMotorEncoder[motorA]))/SLOWFACTOR;

		if (speed > 1) speed = 1;
		else if (speed < -1) speed = -1;

		drive(speed*DRIVESPEED);

		if (SensorValue[S1] == 1)
		{
			drive(0);
			int dist = 0;
			dist = nMotorEncoder[motorA];
			rotateRobot(180);
			nMotorEncoder[motorA]=0;
			drive(DRIVESPEED);
			while (abs(nMotorEncoder[motorA]) < abs(dist))
			{
				speed = (abs(dist) - abs(nMotorEncoder[motorA]))/SLOWFACTOR;
				if (speed > 1) speed = 1;
				else if (speed < -1) speed = -1;
			}
			drive(0);
			turn *= -1;
			distance = 0;
		}
		if (getButtonPress(buttonEnter))
		{
			distance = 0;
		}
	}
	drive(0);
	return turn;
}


task main()
{
	const int ANGLE_CORNER = 90;
	const int SIDE_LENGTH = 50;
	int direction = 1;
	configureAllSensors();
	waitButton(buttonEnter);

	while(!getButtonPress(buttonEnter))
	{
		direction = driveDistance(SIDE_LENGTH, direction);
		rotateRobot(direction*ANGLE_CORNER);
	}


}

void configureAllSensors()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);

	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
}

void drive(int motor_power)//powers both drive motors with the same power
{
	motor[motorA] = motor[motorD] = motor_power;
}

void driveBoth(int motor_power_A, int motor_power_D)//powers both motors independently
{
	motor[motorA] = motor_power_A;
	motor[motorD] = motor_power_D;
}

void waitButton(TEV3Buttons button_name)
{
	while(!getButtonPress(button_name))
	{}
	while(getButtonPress(button_name))
	{}
}
