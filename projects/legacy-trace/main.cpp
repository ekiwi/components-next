#include "../../xpcc/develop/examples/stm32f3_discovery/stm32f3_discovery.hpp"
#include <xpcc/debug/logger.hpp>

// ----------------------------------------------------------------------------
// Set the log level
#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG

// Create an IODeviceWrapper around the Uart Peripheral we want to use
xpcc::IODeviceWrapper< Usart2, xpcc::IOBuffer::BlockIfFull > loggerDevice;

// Set all four logger streams to use the UART
xpcc::log::Logger xpcc::log::debug(loggerDevice);
xpcc::log::Logger xpcc::log::info(loggerDevice);
xpcc::log::Logger xpcc::log::warning(loggerDevice);
xpcc::log::Logger xpcc::log::error(loggerDevice);

//------------------------------------------------------------------------------
#include <component_receiver/receiver.hpp>
#include <component_sender/sender.hpp>

#include <communication/postman.hpp>
#include <communication/identifier.hpp>
#include <xpcc/communication/xpcc/backend/can.hpp>

static Can1 canXpcc;
static xpcc::CanConnector< Can1 > connector(&canXpcc);

// create an instance of the generated postman
static Postman postman;

static xpcc::Dispatcher dispatcher(&connector, &postman);

namespace component
{
	Sender sender(robot::component::SENDER, &dispatcher);
	Receiver receiver(robot::component::RECEIVER, &dispatcher);
}

#include "stop_and_print_tracer.hpp"

// ----------------------------------------------------------------------------
MAIN_FUNCTION
{
	Board::initialize();
	StopAndPrintTracer tracer;
	tracer.calibrate();

	// initialize Uart2 for XPCC_LOG_
	GpioOutputA2::connect(Usart2::Tx);
	GpioInputA3::connect(Usart2::Rx, Gpio::InputType::PullUp);
	// unbuffered uart in order not to disturb the measurements
	Usart2::initialize<Board::systemClock, 115200>();

	XPCC_LOG_INFO << xpcc::endl << xpcc::endl;
	XPCC_LOG_INFO << XPCC_FILE_INFO << "XPCC Dispatcher CycleCounter" << xpcc::endl;

	while (1)
	{
		dispatcher.update();
		component::sender.run();
	}

	return 0;
}
