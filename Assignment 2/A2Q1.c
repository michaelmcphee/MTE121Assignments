/*
A2Q1.c
Michael McPhee and Vinesh Vivekanand
September 20, 2022
Code allows robot to move forward, move back to original position
then rotate 90 degrees clockwise and wait 10 seconds.
*/

task main()

{
    SensorType[S4] = sensorEV3_Gyro; //setting up the gryo
    wait1Msec(50);
    SensorMode[S4] = modeEV3Gyro_Calibration;
    wait1Msec(50);
    SensorMode[S4] = modeEV#Gyro_RateAndAngle;
    wait1Msec(50);

    nMotorEncoder(motorA) = 0; //reads initial position with encoder

    displayString(5, "Group 73 MM VV");
    motor[motorA]=motor[motorD]=50; //forward for 2 seconds
    wait1Msec(2000);
    motor[motorA]=motor[motorD]=0;

    motor[motorA]=motor[motorD]=-50; //repeats driving backwards
    while (nMotorEncoder(motorA) > 0) // continues until returns back to position
    {}
    motor[motorA]=motor[motorD]=0; //stop the motor

    motor[motorA]=-50; //turn clockwise
    motor[motorD]=50;
    while(getGyroDegrees(S4) < 90) //turn until 90 deg clockwise
    {}
    motor[motorA]=motor[motorD]=0; //stop the motor

    wait1Msec(10000); //waits 10 seconds

}

