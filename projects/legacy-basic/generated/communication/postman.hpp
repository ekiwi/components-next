// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically from postman.hpp.tpl
 * Do not edit! Please modify the corresponding XML file instead.
 */
// ----------------------------------------------------------------------------

#ifndef	POSTMAN_HPP
#define	POSTMAN_HPP

#include <xpcc/communication.hpp>
#include <xpcc/communication/xpcc/postman/postman.hpp>
#include "packets.hpp"

class Postman : public xpcc::Postman
{
public:
	xpcc::Postman::DeliverInfo
	deliverPacket(const xpcc::Header& header, const xpcc::SmartPointer& payload);

	bool
	isComponentAvailable(uint8_t component) const;

	void
	update();

private:
};

#endif	// POSTMAN_HPP
