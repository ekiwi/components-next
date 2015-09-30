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

#include <xpcc/utils/arithmetic_traits.hpp>

class Tracer {
public:
	ALWAYS_INLINE  void start() {
		startTime = xpcc::Clock::now();
		startCount = xpcc::cortex::CycleCounter::getCount();
	}
	ALWAYS_INLINE  void stop() {
		const uint32_t stopCount = xpcc::cortex::CycleCounter::getCount();
		const xpcc::Timestamp stopTime = xpcc::Clock::now();
		if(stopCount > startCount) {
			cycles = stopCount - startCount;
		} else {
			cycles = xpcc::ArithmeticTraits<uint32_t>::max - startCount + stopCount;
		}
		cycles -= constant_cycle_offset;
		milliseconds = (stopTime - startTime).getTime();
	}
	inline uint32_t getCycles() { return cycles; }
	inline void printDebug() {
		XPCC_LOG_DEBUG << "Cycles: " << cycles << xpcc::endl;
		const uint32_t us = cycles / 72;
		XPCC_LOG_DEBUG << "        => ~" << us << "us" << xpcc::endl;
		XPCC_LOG_DEBUG << "Time:  ~" << milliseconds << "ms" << xpcc::endl;
	}
	inline void stopAndPrintDebug() { stop(); printDebug(); }
	// TODO: is this actually accurate?
	inline void calibrate() {
		constant_cycle_offset = 0;
		start();
		stop();
		constant_cycle_offset = cycles;
	}
	inline uint32_t getConstantCycleOffset() { return constant_cycle_offset; }
private:
	uint32_t startCount = 0;
	xpcc::Timestamp startTime;
	uint32_t cycles = 0;
	uint32_t milliseconds = 0;
	uint32_t constant_cycle_offset = 0;
};


// ----------------------------------------------------------------------------
MAIN_FUNCTION
{
	Board::initialize();
	Tracer tracer;
	tracer.calibrate();

	// initialize Uart2 for XPCC_LOG_
	GpioOutputA2::connect(Usart2::Tx);
	GpioInputA3::connect(Usart2::Rx, Gpio::InputType::PullUp);
	// unbuffered uart in order not to disturb the measurements
	Usart2::initialize<Board::systemClock, 115200>();

	XPCC_LOG_INFO << xpcc::endl << xpcc::endl;
	XPCC_LOG_INFO << XPCC_FILE_INFO << "XPCC Dispatcher CycleCounter" << xpcc::endl;

	//
	XPCC_LOG_INFO << "dispatcher.update() nothing to do" << xpcc::endl;
	tracer.start();
	dispatcher.update();
	tracer.stopAndPrintDebug();

	component::sender.sendGetPosition();

	// dispatch GET_POSITION message
	XPCC_LOG_INFO << "dispatcher.update() message to send" << xpcc::endl;
	tracer.start();
	dispatcher.update();
	tracer.stopAndPrintDebug();

	// dispatch GET_POSITION answer
	XPCC_LOG_INFO << "dispatcher.update() answer to send" << xpcc::endl;
	tracer.start();
	dispatcher.update();
	tracer.stopAndPrintDebug();

	// call GET_POSITION as funcion
	XPCC_LOG_INFO << "calling get position as a function" << xpcc::endl;
	tracer.start();
	volatile auto position = component::receiver.functionGetPosition();
	tracer.stopAndPrintDebug();

	while (1)
	{
		Board::LedNorth::toggle();
		xpcc::delayMicroseconds(1000);
	}

	return 0;
}
