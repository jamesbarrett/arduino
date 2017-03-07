
#include "SteamRoller.h"

#define sweepStep 5
#define wait 5000
#define initP 200

//define endpoints for steam valve
#define uSopen 2350
#define uSshut 580

// define endpoints for movement kicker
#define kSbackwards 2350
#define kSforwards 580

// define endpoints for clutch
#define clutchIn 2350
#define clutchOut 580



SteamRoller :: SteamRoller(int steamPin, int clutchPin, int kickPin)
{
	steamValve.attach(steamPin);
	clutch.attach(clutchPin);
	kicker.attach(kickPin);
	_pos = uSshut;
}

void SteamRoller::initialise(){
	Serial.println("Initialising valve servo");
        tone(2, 880,300);
	
	delay(initP);
	openSteam();
	delay(initP);
	closeSteam();
	delay(initP);
	Serial.println("Valve servo ready");
	delay(initP);
	Serial.println("Disengage drive");
        disengage();
	delay(initP);
	Serial.println("Prime kickstart for forward motion");
        kickstart(false);
	delay(initP);
	Serial.println("Initialisation complete\n\n");
	moving = false;
        tone(2, 880,300);
}
// change the steam valve
void SteamRoller::adjust(int myval)
{ 
	int percent = constrain(myval,0,100);
	int uSecs = map(percent, 0, 100, uSshut, uSopen);
	int servoIncrement = sweepStep * (abs(uSecs - _pos))/(uSecs - _pos);
	int dotMe = 0;

	Serial.print("valve servo to ");
	Serial.print(percent);
	Serial.println("%");
	// move to within sweepstep of final position
	while(abs(uSecs - _pos) > sweepStep){
		if (dotMe > (25/sweepStep)){
			Serial.print(".");
			dotMe = 0;
		}
		dotMe++;
		_pos += servoIncrement;
		steamValve.writeMicroseconds(_pos);
		delay(sweepStep);
	}
	//finalise ...
	Serial.print("\n");
	steamValve.writeMicroseconds(uSecs);
	_pos = uSecs;
}


// open the steam valve
void SteamRoller::openSteam()
{
	adjust(100);
}
// close the steam valve
void SteamRoller::closeSteam()
{
	adjust(0);
}

void SteamRoller::stopVehicle(){
  disengage();
  closeSteam();
  moving = false;
}

void SteamRoller::startVehicle(bool forwards){
  if(moving){
    stopVehicle();
  }
  kickstart(!forwards);
  openSteam();
  kickstart(forwards);
  engage();
  moving = true;
  
}
void SteamRoller::kickstart(bool forwards){
  if(forwards){
    kicker.writeMicroseconds(kSforwards);
  } else {
    kicker.writeMicroseconds(kSbackwards);
  }
}
void SteamRoller :: engage(){
    clutch.writeMicroseconds(clutchOut);
}
void SteamRoller :: disengage(){
    clutch.writeMicroseconds(clutchIn);
}