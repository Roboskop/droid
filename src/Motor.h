
/* Kodlio 
*  18-08-2017 09:10 tarihinde oluşturuldu.
*  Dosya:	motor.h
*/

#ifndef R_MOTOR_H
#define R_MOTOR_H

#include <Arduino.h>

class RMotorDriver{

public:

	RMotorDriver();
	RMotorDriver(int in1, int in2);
	RMotorDriver(int in1, int in2 , int pwm);
	void	throttle(int th);	//Ingilizce
	void	brake();
	int		throttle();
	int		gaz();
	void	dondur( int guc );	//Turkce
	void	fren();
	
private:

	int		m_in1;
	int		m_in2;
	int		m_pwm;
	int		m_throttle;
	int		m_steering;

	void	_throttle( int th );
	void	_brake();
	int		_throttle();

};

#endif
