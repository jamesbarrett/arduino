
#ifndef SteamRoller_h
#define SteamRoller_h
#include "Arduino.h"
#include "Servo.h"

class SteamRoller
{
	public:
		SteamRoller(int steamPin, int clutchPin, int kickPin);
		void initialise();
		void stopVehicle();
		void startVehicle(bool forwards);
		bool moving;
	
	private:
		void adjust(int percent);
		void engage();
		void disengage();
		void closeSteam();
		void openSteam();
		void kickstart(bool forwards);
		int _pos;

		Servo steamValve;
		Servo clutch;
		Servo kicker;
};
#endif