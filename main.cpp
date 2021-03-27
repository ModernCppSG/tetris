/*
 * main.cpp
 *
 *  Created on: 2 de mar de 2021
 *      Author: choiw
 */

#include "internal_clock.hpp"

int main(){

	lock_wrapper teste;
	internal_clock a(std::chrono::milliseconds(200), 5, &teste);

	a.run();

	for (int x = 0; x < 50; ++x){
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	a.print_elapsed();

}
