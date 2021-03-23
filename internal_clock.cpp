/*
 * internal_clock.cpp
 *
 *  Created on: 2 de mar de 2021
 *      Author: choiw
 */

#include "internal_clock.hpp"

// "Kills" the infinite loop to terminate internal thread
void internal_clock::terminate(){

	stop_clock.store(false);
	if (my_thread.joinable()){
		my_thread.join();
	}
	std::cout << "\nExisting clock thread has been terminated!\n";
}

// Set of instructions that will be sent to the child thread
void internal_clock::instructions(){
	while (stop_clock.load()){

		// Slices the interval in n pieces and checks accordingly
		std::this_thread::sleep_for(interval);

		// Does the check: Did it elapse?
		// If so increases the counter and fires a flag of a short duration.
		if ((elapsed_intervals.load() +  1)* interval < get_elapsed()){
			elapsed_intervals++;

			is_interval_elapsed.store(true);
			std::this_thread::sleep_for(interval);
			is_interval_elapsed.store(false);
		}
	}
}

internal_clock::internal_clock(time_unit _interval){
	interval = _interval;
}

// Resets the number of elapsed intervals and sets start to now.
void internal_clock::reset(){
	start = std::chrono::system_clock::now();
	elapsed_intervals.store(0);
}

void internal_clock::set_interval(time_unit x){
	interval = x;
}

void internal_clock::print_elapsed(){
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms\n";
}

time_unit internal_clock::get_interval(){
	return interval;
}

time_unit internal_clock::get_elapsed(){
	return std::chrono::duration_cast<time_unit>(std::chrono::system_clock::now() - start);
}

bool internal_clock::get_is_elapsed(){
	return is_interval_elapsed.load(std::memory_order::memory_order_seq_cst);
}

unsigned int internal_clock::get_elapsed_intervals(){
	return elapsed_intervals.load(std::memory_order::memory_order_seq_cst);
}

internal_clock::~internal_clock() {
	terminate();
}

void internal_clock::run(int interval_slice, int firing_slice){
	reset();
	is_interval_elapsed.store(false);
	stop_clock.store(true);
	elapsed_intervals.store(0);
	// Given the existence of a terminate function, it is needed to check the existence
	// and properly handle an existing thread here.
	my_thread = std::thread(&internal_clock::instructions, this, interval_slice, firing_slice);
}
