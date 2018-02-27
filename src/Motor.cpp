
/* Kodlio 
*  18-08-2017 09:11 tarihinde oluşturuldu.
*  Dosya:	motor.cpp
*/

#include "Motor.h"

RMotorDriver::RMotorDriver()	:	m_in1( 0 ) , m_in2( 0 )
{	}

RMotorDriver::RMotorDriver(int in1 , int in2) : m_in1( in1 ) , m_in2( in2 ){
	pinMode( in1 , OUTPUT );
	pinMode( in2 , OUTPUT );
}

RMotorDriver::RMotorDriver(int in1 , int in2 , int pwm ) : 
	m_in1(in1) , m_in2(in2) , m_pwm(pwm)
{
	pinMode(m_in1 , OUTPUT );
	pinMode(m_in2 , OUTPUT );
	pinMode(m_pwm , OUTPUT );
}

void RMotorDriver::throttle( int th ) {
	_throttle( th );
}

void RMotorDriver::brake(){
	_brake();
}

void RMotorDriver::dondur( int guc ){
	_throttle( guc );
}

void RMotorDriver::fren(){
	_brake();
}

void RMotorDriver::_throttle( int th ){
	
	if( th > 0 ){
		digitalWrite( m_in1 , HIGH );
		digitalWrite( m_in2 , LOW );
	} else {
		digitalWrite( m_in1 , LOW );
		digitalWrite( m_in2 , HIGH );
	}

	analogWrite(m_pwm , abs(th));
	Serial.print(m_pwm);
	Serial.print(" : ");
	Serial.println(abs(th));

	m_throttle = th;
}

void RMotorDriver::_brake(){
	digitalWrite( m_in1 , HIGH );
	digitalWrite( m_in2 , HIGH );
	m_throttle = 0;
}

int RMotorDriver::throttle(){
	return _throttle();
}

int RMotorDriver::gaz(){
	return _throttle();
}

int RMotorDriver::_throttle(){
	return m_throttle;
}