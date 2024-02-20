/** BusInOut library for Arduino
 *
 *  @author Tedd OKANO
 *
 *  Released under the MIT license License
 */

#ifndef ARDUINO_BUSINOUT_H
#define ARDUINO_BUSINOUT_H

#include <Arduino.h>
#include <stdint.h>

/** BusInOut class
 *	
 *  @class BusInOut
 *  
 *	This class can be inherited. 
 *	When the "operator=" need to be used in inherited class, 
 *	use "using BusInOut::operator=;" in that class. 
 */

class BusInOut {
public:
	/** To define non-connected pin, use BusInOut::nc */
	constexpr static uint8_t	nc	= 0xFF;

	/** Create a BusInOut instance with specified pins
	 *
	 * @param bit<n> pin number to connect bus bit<n> (0-13, nc)
	 *
	 * @note define pins from lower to upper. No need to define upper bits if those are not be used 
	 */
	BusInOut(	uint8_t bit0 = nc,
				uint8_t bit1 = nc,
				uint8_t bit2 = nc,
				uint8_t bit3 = nc,
				uint8_t bit4 = nc,
				uint8_t bit5 = nc,
				uint8_t bit6 = nc,
				uint8_t bit7 = nc
			 );

	/** Configure BusInOut IO direction
	 *
	 * @param conf INPUT or OUTPUT (defined in Arduino.h)
	 */
	virtual uint8_t		config( int conf );

	/** Output a value to BusInOut pins
	 *
	 * @param v value to be set to pins
	 */
	virtual void		value( uint8_t v );
	
	/** Input a value from BusInOut pins
	 *
	 * @return value read from pins
	 */
	virtual uint8_t		value( void );
	
	
	/** A short hand for setting pins
	 */
	BusInOut&	operator=( uint8_t v );
	BusInOut&	operator=( BusInOut& rhs );

	/** A short hand for reading pins
	 */
	operator	int();
	
private:
	uint8_t	_bits[ 8 ];
	uint8_t	_width;
	uint8_t	_mode;
};

#endif //	ARDUINO_BUSINOUT_H
