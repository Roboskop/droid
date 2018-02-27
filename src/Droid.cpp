
/* Kodlio 
*  18-08-2017 09:09 tarihinde oluşturuldu.
*  Dosya:	Droid.cpp
*/

#include "Droid.h"

Droid::Droid(){
    m_left = new RMotorDriver(7 , 8 , 9);
    m_right = new RMotorDriver(6 , 4 , 5);
}

Droid::Droid(int sol1, int sol2, int sag1, int sag2){
	m_left = new RMotorDriver(sol1 , sol2);
	m_right = new RMotorDriver(sag1 , sag2);
}

Droid::Droid(int sol1, int sol2 , int solPwm , int sag1, int sag2 , int sagPwm){
	m_left = new RMotorDriver(sol1 , sol2 , solPwm);
	m_right = new RMotorDriver(sag1 , sag2 , sagPwm);
}

Droid::~Droid(){
	delete m_left;
	delete m_right;
}

void Droid::throttle( int th , int steering ){
	_throttle( th , steering );
}

void Droid::brake(){
	_brake();
}

void Droid::ilerle( int gaz , int donus ){
	_throttle( gaz , donus );
}

void Droid::fren(){
	_brake();
}

int Droid::throttle(){
	return m_throttle;
}

int Droid::steering(){
	return m_steering;
}

int Droid::gaz(){
	return m_throttle;
}

int Droid::donus(){
	return m_steering;
}

void Droid::_brake(){
	m_throttle = 0;
	m_steering = 0;
	m_left->brake();
	m_right->brake();
}

void Droid::_throttle( int th , int steering ){
     if(th > 255)
          th = 255;
     else if(th < -255)
          th = -255;

     if(steering > 255)
          steering = 255;
     else if(steering < -255)
          steering = -255;

     bool forward = th > 0;

     float turningFactor = th / 255.0;

     float leftThrottle = abs(th) + (steering * turningFactor);
     float rightThrottle =  abs(th) - (steering * turningFactor);


     if(leftThrottle > 255){
          rightThrottle -= (leftThrottle - 255);
          leftThrottle = 255;
     }

     if(rightThrottle > 255){
          leftThrottle -= (rightThrottle - 255);
          rightThrottle = 255;
     }

     if(!forward){
          leftThrottle *= -1;
          rightThrottle *= -1;
     }

	m_left->throttle(leftThrottle);
	m_right->throttle(rightThrottle);
	m_steering = steering;
	m_throttle = th;
}