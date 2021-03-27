/*
 * internal_clock.cpp
 *
 *  Created on: 2 de mar de 2021
 *      Author: choiw
 */

#include "internal_clock.hpp"

// "Kills" the infinite loop to terminate internal thread
void internal_clock::terminate(bool print = false){

	stop_clock.store(false);

	if (my_thread.joinable()){
		my_thread.join();
	}

	if (print){
		std::cout << "\nExisting clock thread has been terminated!";
	}
}

// Set of instructions that will be sent to the child thread
void internal_clock::instructions(){

	unsigned int i;
	bool elapsed;
	time_unit mini_interval;
	time_unit watcher;	// difference between now and last elapsed interval

	while (stop_clock.load()){

		mini_interval = interval;
		elapsed = false;

		{
			std::lock_guard<std::mutex> g(clock_protect);

			for (i = 0; i < res; i++){

				mini_interval = mini_interval/2;
				std::this_thread::sleep_for(mini_interval);

				watcher = std::chrono::duration_cast<time_unit>(std::chrono::system_clock::now() - elapsed_time);

				// Does the check: Did it elapse?
				// If so increases the counter and sends a notification.
				if ( interval <= watcher ){

					elapsed_time = std::chrono::system_clock::now();
					elapsed_intervals++;

					semaphore->notify_all();

					elapsed = true;
					break;
				}
			}
			while (!elapsed){
				std::this_thread::sleep_for(mini_interval);

				watcher = std::chrono::duration_cast<time_unit>(std::chrono::system_clock::now() - elapsed_time);

				// Does the check: Did it elapse?
				// If so increases the counter and sends a notification.
				if ( interval <= watcher ){

					elapsed_time = std::chrono::system_clock::now();
					elapsed_intervals++;

					semaphore->notify_all();

					elapsed = true;
					break;
				}
			}

		}
	}
}

internal_clock::internal_clock(const time_unit& _interval, unsigned int _res, lock_wrapper* _semaphore){
	interval = _interval;
	semaphore = _semaphore;
	res = _res;
}

// Resets the number of elapsed intervals and sets start to now.
// Additionally, if argument = true, calls terminate(). Enables a quick "new game"
void internal_clock::reset(bool kill_thread = false){

	if (kill_thread){
		terminate();
	}

	// Protected block
	{
		std::lock_guard<std::mutex> g(clock_protect);

		start = std::chrono::system_clock::now();
		elapsed_time = std::chrono::system_clock::now();
		elapsed_intervals.store(0);
		stop_clock.store(true);
	}
}

void internal_clock::set_interval(const time_unit& x){
	// Protecting the function call. Prevent mid-iteration modification.
	std::lock_guard<std::mutex> g(clock_protect);

	interval = x;
}

// Actually start the clock, more like a stopwatch.
void internal_clock::run(){

	if ( !(my_thread.joinable()) ){
		// if (there is no existing thread):
		reset();	// resets control parameters;
		// creates thread;
		my_thread = std::thread(&internal_clock::instructions, this);
	}/*
	else{
		// if there is an existing thread:
		//		does nothing;
	}*/

}

void internal_clock::freeze(){

}

void internal_clock::resume(){

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

clock_int internal_clock::get_elapsed_intervals(){
	return elapsed_intervals.load(/*std::memory_order_seq_cst*/);
}

internal_clock::~internal_clock() {
	std::cout << "\nDestructor called! terminate() will be executed!";
	terminate(true);
}
