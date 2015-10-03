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

#include <xpcc/utils/arithmetic_traits.hpp>
#include <xpcc/processing/timer.hpp>

#ifndef STOP_AND_PRINT_TRACE_HPP
#define STOP_AND_PRINT_TRACE_HPP

#define TRACER_FILE_INFO STRINGIFY(BASENAME) "(" STRINGIFY(__LINE__) ")"
#define TRACE_LINE(description) StopAndPrintTracer::defaultTracer.trace(TRACER_FILE_INFO, description)
#define TRACE_END() StopAndPrintTracer::defaultTracer.trace(TRACER_FILE_INFO)

class StopAndPrintTracer {
public:
	void trace(const char* newName = nullptr, const char* newDescription = nullptr);
	void printTrace(const char* newName, const char* newDescription);
	static uint32_t
	calculateCycles(const uint32_t startCount, const uint32_t stopCount, const uint32_t offset);
	static uint32_t
	calculateMilliseconds(const xpcc::Timestamp& startTime, const xpcc::Timestamp& stopTime);
	void calibrate();
	inline uint32_t getConstantCycleOffset() { return constant_cycle_offset; }
private:
	volatile uint32_t startCount = 0;
	xpcc::Timestamp startTime;
	uint32_t cycles = 0;
	uint32_t milliseconds = 0;
	uint32_t constant_cycle_offset = 0;
	bool firstTrace = true;
	const char* name = nullptr;
	const char* description = nullptr;
	bool silent = false;
public:
	static StopAndPrintTracer defaultTracer;
};

#endif // STOP_AND_PRINT_TRACE_HPP
