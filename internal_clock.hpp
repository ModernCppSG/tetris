/*
 * internal_clock.hpp
 *
 *  Created on: 2 de mar de 2021
 *      Author: choiw
 */

#ifndef INTERNAL_CLOCK_HPP_
#define INTERNAL_CLOCK_HPP_

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using time_unit = std::chrono::milliseconds;

class internal_clock {
 private:
  std::chrono::time_point<std::chrono::system_clock> start;
  time_unit interval;

  std::thread my_thread;
  std::atomic<bool>
      is_interval_elapsed;  // Might want to use condition_variable
  std::atomic_flag stop_clock = ATOMIC_FLAG_INIT;
  std::atomic<uint32_t> elapsed_intervals;  // this MIGHT overflow

 public:
  internal_clock(time_unit x);
  void reset();
  void set_interval(time_unit x);
  time_unit get_interval();
  void print_elapsed();
  time_unit get_elapsed();

  bool get_is_elapsed();
  unsigned int get_elapsed_intervals();

  ~internal_clock();

  void run(int interval_slice, int firing_slice);
  void terminate();
  void instructions(int interval_slice, int firing_slice);
};

#endif /* INTERNAL_CLOCK_HPP_ */
