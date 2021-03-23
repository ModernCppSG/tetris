/*
 * internal_clock.hpp
 *
 *  Created on: 2 de mar de 2021
 *      Author: choiw
 */

#ifndef INTERNAL_CLOCK_HPP_
#define INTERNAL_CLOCK_HPP_

#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

using time_unit = std::chrono::milliseconds;
using clock_int = uint32_t;

class internal_clock {

private:

	std::chrono::time_point<std::chrono::system_clock> start;
	time_unit interval;

	std::thread my_thread;
	std::atomic<bool> is_interval_elapsed;// Might want to use condition_variable
	std::atomic<bool> stop_clock;
	std::atomic<clock_int> elapsed_intervals; // this MIGHT overflow
	std::mutex mtx;

	// Private functions
	void terminate();
	void instructions();

public:
	// Constructor
	internal_clock(time_unit x);

	// Functions that change something
	void reset();
	void set_interval(time_unit x);

	// Functions that print something
	void print_elapsed();

	// Functions that return something
	time_unit get_interval();
	time_unit get_elapsed();
	bool get_is_elapsed();
	clock_int get_elapsed_intervals();

	~internal_clock();

	// Most important function
	void run(int interval_slice, int firing_slice);
};


#endif /* INTERNAL_CLOCK_HPP_ */
