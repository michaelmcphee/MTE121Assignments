/*
A4Q1.c
Michael McPhee and Olivia Markham
October 5, 2022
*/


//trivial function that recieves two motor powers and sets the respective motors to those powers
void set_motor_power(float motor_power_1, float motor_power_2)
{
 motor[motorA] = motor_power_1;
 motor[motorD] = motor_power_2;
}

//function that receives te integer related to the paper color, measures the paper using the ultrasonic sensor and returns length
float ultrasonic_measurer(int color)
{
    while(SensorValue[S3]!=color)
    {}
    float distance_to_wall_1 = SensorValue[S2];
    
    while(SensorValue[S3]==color)
    {}
    float distance_to_wall_2 = SensorValue[S2];

    return distance_to_wall_1 - distance_to_wall_2;
}

float motor_encoder_measurer(int color)
{


    while(SensorValue[S3]!=color)
    {}
    float distance_travelled_1 = nMotorEncoder(motorA);
    
    while(SensorValue[S3]==color)
    {}
    float distance_travelled_2 = nMotorEncoder(motorA);


    return ((distance_travelled_1 - distance_travelled_2)*(2*PI*2.75) / 360);
}

task main()
{

nMotorEncoder[motorA] = 0;
//S1 is the ultrasonic
//S4 is the gyro

SensorMode[S3]=modeEV3Color_Color;
SensorType[S2]=sensorEV3_Ultrasonic;
SensorType[S4]=sensorEV3_Gyro;
SensorType[S1]=sensorEV3_Touch;

//recalibrates the gyro
SensorType[S4] = sensorEV3_Gyro;
wait1Msec(50);
SensorMode[S4]= modeEV3Gyro_Calibration;
wait1Msec(50);
SensorMode[S4]=modeEV3Gyro_RateAndAngle;
wait1Msec(50);


//trivial function is NOT user-provided
//non-trivial function IS user-provided
float motor_power_1 = 40;
float motor_power_2 = 40;

//display string on robot screen
displayString(3, "Group 76 OM MM");


//Waits for the enter buttn to be pushed and released
//Once hit, sensor returns 1 and thus exits the while
motor[motorA] = motor[motorD] = 0;
while(!getButtonPress(buttonEnter))
{}
while(getButtonPress(buttonEnter))
{}
//Drives forward at 40% power

set_motor_power(motor_power_1, motor_power_2);

int distance1 = ultrasonic_measurer((int)colorRed);

while(!SensorValue[S1])//wait until hits the wall
{}
motor[motorA] = motor[motorD] = 0;
wait1Msec(500);//stops for 0.5 seconds


//drives backwards to original location using the motor encoders
motor[motorA] = motor[motorD] = -40;

int distance2 = motor_encoder_measurer((int)colorRed);

while(nMotorEncoder(motorA)>0)
{}
motor[motorA] = motor[motorD] = 0;


displayString(5, "ultrasonic distance %f",distance1);
displayString(7, "motor encoder distance %f", distance2);

//waits two seconds
wait1Msec(2000);

//does a 360 degree counter-clockwise turn at 30% power
motor[motorA]=-30;
motor[motorD]=30;
while(getGyroDegrees(S4)<360)
{}
motor[motorA]=motor[motorD]=0;



//displays the codeword for 4 seconds on line 10
displayString(10, "pumpkin");
wait1Msec(4000);

}
