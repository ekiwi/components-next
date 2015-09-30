// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding XML file instead.
 */
// ----------------------------------------------------------------------------


#include "component_sender/sender.hpp"
#include "component_receiver/receiver.hpp"

#include "identifier.hpp"
#include "postman.hpp"

namespace component
{
	extern Sender	sender;
	extern Receiver	receiver;
}

// ----------------------------------------------------------------------------
xpcc::Postman::DeliverInfo
Postman::deliverPacket(const xpcc::Header& header, const xpcc::SmartPointer& payload)
{
	xpcc::ResponseHandle response(header);

	// Avoid warnings about unused variables
	(void) payload;
	(void) response;

	switch (header.destination)
	{
		case robot::component::SENDER:
		{
			switch (header.packetIdentifier)
			{

				default:
					return NO_ACTION;
			}
			break;
		}

		case robot::component::RECEIVER:
		{
			switch (header.packetIdentifier)
			{
				case robot::action::SET_POSITION:
					// void actionSetPosition(const xpcc::ResponseHandle& responseHandle, const robot::packet::Position *payload);
					component::receiver.actionSetPosition(response, &payload.get<robot::packet::Position>());
					return OK;
				case robot::action::GET_POSITION:
					// void actionGetPosition(const xpcc::ResponseHandle& responseHandle);
					component::receiver.actionGetPosition(response);
					return OK;

				default:
					return NO_ACTION;
			}
			break;
		}


		// Events
		case 0:
			switch (header.packetIdentifier)
			{
				default:
					break;
			}
			return OK;

		default:
			return NO_COMPONENT;
	}

	return NOT_IMPLEMENTED_YET_ERROR;
}

// ----------------------------------------------------------------------------
bool
Postman::isComponentAvailable(uint8_t component) const
{
	switch (component)
	{
		case robot::component::SENDER:
		case robot::component::RECEIVER:
			return true;
			break;

		default:
			return false;
	}
}

void
Postman::update()
{
}

// ----------------------------------------------------------------------------
