
/* Kodlio 
*  18-08-2017 09:09 tarihinde oluşturuldu.
*  Dosya:	Droid.h
*/

#ifndef CYBER_DROID_H
#define CYBER_DROID_H

#include "Motor.h"
#include "SimpleSerial.h"

class Droid{

public:

	Droid();
	Droid(int sol1, int sol2 , int sag1, int sag2);
	Droid(int sol1, int sol2 , int solPwm , int sag1, int sag2 , int sagPwm);
	~Droid();
	void		throttle( int th , int steering );
	void		brake();
	void		ilerle( int gaz , int donus );
	void		fren();
	int			throttle();
	int			steering();
	int			gaz();
	int			donus();
	

private:

	RMotorDriver*	m_left;
	RMotorDriver*	m_right;
	int				m_throttle;
	int				m_steering;
	void			_throttle( int th , int steering );
	void			_brake();

};

#endif