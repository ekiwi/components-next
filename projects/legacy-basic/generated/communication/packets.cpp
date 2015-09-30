// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding XML file instead.
 */
// ----------------------------------------------------------------------------

#include "packets.hpp"

robot::packet::Position::Position() :
	x(), y()
{
}

robot::packet::Position::Position(int16_t x, int16_t y) :
	x(x), y(y)
{
}


// ----------------------------------------------------------------------------
// IOStream Helpers
xpcc::IOStream&
robot::packet::operator << (xpcc::IOStream& s, const Position e)
{
	s << "Position(";
	s << " x=" << e.x;
	s << " y=" << e.y;
	s << " )";
	return s;
}
