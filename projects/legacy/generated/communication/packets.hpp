// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically from robot_packets.hpp.tpl.
 * Do not edit! Please modify the corresponding XML file instead.
 */
// ----------------------------------------------------------------------------

#ifndef	ROBOT_PACKETS_HPP
#define	ROBOT_PACKETS_HPP

#include <stdint.h>
#include <cstdlib>
#include <xpcc/io/iostream.hpp>
#include <xpcc/container/smart_pointer.hpp>

namespace robot
{
	namespace packet
	{
		/** On x86 systems the bool-type has 4 bytes and on AVRs it has 1 byte.
		 * This type is defined to make it posible to send bools from
		 * everywhere. */
		typedef uint8_t Bool;
	
		/** Position of the Robot on the Playground. */
		struct Position
		{
			Position();

			Position(int16_t x, int16_t y);
			
			int16_t x;
			int16_t y;
		} __attribute__((packed));

		xpcc::IOStream&
		operator << (xpcc::IOStream& s, const Position e);

	} // namespace packet
} // namespace robot

#endif	// ROBOT_PACKETS_HPP
