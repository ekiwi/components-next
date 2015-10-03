// coding: utf-8
// -----------------------------------------------------------------------------
/*
 * Copyright (C) 2015 Kevin Laeufer <kevin.laeufer@rwth-aachen.de>, Roboterclub Aachen e.V.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, see <http://www.gnu.org/licenses/>.
 */
// -----------------------------------------------------------------------------

#include "stop_and_print_tracer.hpp"
#include <xpcc/architecture.hpp>
#include <xpcc/debug/logger.hpp>

// ----------------------------------------------------------------------------
// Set the log level
#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG

void StopAndPrintTracer::trace(const char* newName, const char* newDescription)
{
	const volatile uint32_t stopCount = xpcc::cortex::CycleCounter::getCount();
	const xpcc::Timestamp stopTime = xpcc::Clock::now();
	//
	if(firstTrace) {
		firstTrace = false;
	} else {
		cycles = calculateCycles(startCount, stopCount, constant_cycle_offset);
		milliseconds = calculateMilliseconds(startTime, stopTime);
		if(!silent) {
			printTrace(newName, newDescription);
		}
	}
	this->name = newName;
	this->description = newDescription;
	//
	startTime = xpcc::Clock::now();
	startCount = xpcc::cortex::CycleCounter::getCount();
}

void StopAndPrintTracer::printTrace(const char* newName, const char* newDescription)
{
	// const uint32_t us = cycles / 72;
	XPCC_LOG_DEBUG << cycles << " ";
	if(name && newName) {
		XPCC_LOG_DEBUG << "[" << name << "] -> [" << newName << "] (";
	} else if(name) {
		XPCC_LOG_DEBUG << "[" << name << "] -> [END] (";
	} else if(newName) {
		XPCC_LOG_DEBUG << "[" << newName << "] (";
	}
	XPCC_LOG_DEBUG << milliseconds << "ms)";
	if(description) {
		XPCC_LOG_DEBUG << ": \"" << description << "\"";
	}
	XPCC_LOG_DEBUG << xpcc::endl;
}

uint32_t
StopAndPrintTracer::calculateCycles(const uint32_t startCount, const uint32_t stopCount, const uint32_t offset)
{
	return ((stopCount > startCount)?
			(stopCount - startCount):
			(xpcc::ArithmeticTraits<uint32_t>::max - startCount + stopCount))
			- offset;
}

uint32_t
StopAndPrintTracer::calculateMilliseconds(const xpcc::Timestamp& startTime, const xpcc::Timestamp& stopTime)
{
	return (stopTime - startTime).getTime();
}

// TODO: is this actually accurate?
void StopAndPrintTracer::calibrate()
{
	const auto oldName = name;
	const auto oldDescription = description;
	const auto oldFirstTrace = firstTrace;
	const auto oldSilent = silent;
	//
	firstTrace = true;
	silent = true;
	constant_cycle_offset = 0;
	trace(nullptr);
	trace(nullptr);
	constant_cycle_offset = cycles;
	//
	silent = oldSilent;
	firstTrace = oldFirstTrace;
	name = oldName;
	description = oldDescription;
}

StopAndPrintTracer
StopAndPrintTracer::defaultTracer;
