/*
A3Q1.c
Michael McPhee and Daniel Luchian
September 28, 2022
*/

task main()
{
	//initializations
	SensorType[S1] = sensorEV3_Touch;
	motor[motorA] = motor[motorD] = 0;
	nMotorEncoder(motorA) = 0;
	nMotorEncoder(motorD) = 0;
	
	int distance = 20;
	float originalDistanceEncoder = 0;
	

	//display first line
	displayString(5, "Group 75 DL MM");

	//get button press
	while(!getButtonPress(buttonEnter))
		{}

	
	while(getButtonPress(buttonEnter))
		{}

	motor[motorA] = motor[motorD] = 40;

	//stop once robot hits wall
	while (SensorValue[S1] == 0)
		{}
	originalDistanceEncoder = nMotorEncoder(motorD);


	motor[motorA] = motor[motorD] = 0;
	wait1Msec(2000);

	nMotorEncoder(motorA) = 0;

	//go backwards for a set distance
	motor[motorA] = motor[motorD] = -40;
	while (abs(nMotorEncoder(motorA))<=(distance * (360/(2*PI*2.75))))
	{}

	motor[motorA] = motor[motorD] = -40;
	nMotorEncoder(motorD)=0;

	//go backwards until another set distance
	while (abs(nMotorEncoder(motorD)) > 2*originalDistanceEncoder-20*(360/(2*PI*2.75)))
	{}

	//stop
	motor[motorA] = motor[motorD] = 0;

	//display final message and wait
	displayString(5, "Group 75 DL MM");
	wait1Msec(3000);
}
