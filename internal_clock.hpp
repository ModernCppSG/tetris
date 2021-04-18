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
#include <vector>
#include <algorithm>
#include "lockWrapper.h"

using time_unit = std::chrono::milliseconds;
using clock_unit = std::chrono::time_point<std::chrono::system_clock>;
using clock_int = uint32_t;

/*
 * Put a cool description here. :b
 */
class internal_clock {

private:

	// time related attributes
	clock_unit start;
	clock_unit elapsed_time;	/* Clock that moves by a interval step.
	 	 	 	 	 	 	 	 * EXTREME care handling it, because it cannot be atomic,
	 	 	 	 	 	 	 	 * but needs thread safety.*/
	time_unit interval;
	unsigned int res;
	/* Divides the interval by n parts, each with the length 1/(2^n), and repeats
	 * the last (to guarantee sleep function is met). Example: n = 3.
	 * There will be intervals corresponding to 1/2, 1/4, 1/8, 1/8, 1/8...
	 * Using 1 or 0 sleeps the whole interval.*/

	// multi-threading related attributes
	std::thread my_thread;
	std::atomic<bool> stop_clock;	// Flag to kill the thread.
	std::atomic<clock_int> elapsed_intervals;	/* this MIGHT overflow. Number
	 	 	 	 	 	 	 	 	 	 	 	 * of elapsed intervals. */
	std::mutex clock_protect;	// guarantees some integrity.
	lock_wrapper* semaphore;	/* Condition variable given by the
	 	 	 	 	 	 	 	 	 	 * main thread that will hold the engine
	 	 	 	 	 	 	 	 	 	 * of the game. */
	/* A possible issue (and reason why we should not used pointers and threads):
	 *  What if the objected pointed by this pointer is released/freed? How to
	 *  even check it? */

	// Private functions
	void terminate(bool print);
	void instructions();

public:
	// Constructor
	internal_clock(const time_unit &x, unsigned int _res, lock_wrapper* _semaphore);

	// Functions that change something
	void reset(bool kill_thread);
	void set_interval(const time_unit &x);

	// Most important functions
	void run();
	void freeze();	// still not implemented
	void resume();	// still not implemented

	// Functions that print something
	void print_elapsed();

	// Functions that return something
	time_unit get_interval();
	time_unit get_elapsed();
	clock_int get_elapsed_intervals();

	// Destructor
	~internal_clock();
};


#endif /* INTERNAL_CLOCK_HPP_ */
