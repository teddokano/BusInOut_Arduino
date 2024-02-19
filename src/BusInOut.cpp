#include "BusInOut.h"

BusInOut::BusInOut(
				   uint8_t bit0,
				   uint8_t bit1,
				   uint8_t bit2,
				   uint8_t bit3,
				   uint8_t bit4,
				   uint8_t bit5,
				   uint8_t bit6,
				   uint8_t bit7
				   )
{
	_bits[ 0 ]	= bit0;
	_bits[ 1 ]	= bit1;
	_bits[ 2 ]	= bit2;
	_bits[ 3 ]	= bit3;
	_bits[ 4 ]	= bit4;
	_bits[ 5 ]	= bit5;
	_bits[ 6 ]	= bit6;
	_bits[ 7 ]	= bit7;
	
	config( INPUT );
}

uint8_t BusInOut::config( int conf )
{
	uint8_t	last_bit	= -1;
	
	for ( int i = 0; i < 8; i++ )
	{
		if ( _bits[ i ] == nc )
			continue;
		
		pinMode( _bits[ i ], conf );
		last_bit	= i;
	}
	
	_width	= last_bit + 1;
	_mode	= conf;
	
	return last_bit;
}

void BusInOut::value( uint8_t v )
{
	for ( int i = 0; i < _width; i++ )
	{
		if ( _bits[ i ] == nc )
			continue;
		
		digitalWrite( _bits[ i ], (v >> i) & 0x01 );
	}
}

uint8_t BusInOut::value( void )
{
	uint8_t	r	= 0x00;
	
	for ( int i = 0; i < _width; i++ )
	{
		if ( _bits[ i ] == nc )
			continue;
		
		r	|= (digitalRead( _bits[ i ] ) ? 0x01 : 0x00) << i;
	}
	
	return r;
}

BusInOut& BusInOut::operator=( uint8_t v )
{
	value( v );
	return *this;
}

BusInOut& BusInOut::operator=( BusInOut& )
{
	return *this;
}

BusInOut::operator int()
{
	return value();
}
