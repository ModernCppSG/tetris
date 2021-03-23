/*
 * main.cpp
 *
 *  Created on: 2 de mar de 2021
 *      Author: choiw
 */

#include "internal_clock.hpp"

int main(){

	internal_clock a(std::chrono::milliseconds(200));

	a.run(5, 6);

	for (int x = 0; x < 50; ++x){
		std::this_thread::sleep_for(std::chrono::milliseconds(30));

		std::cout << "flag is: " << a.get_is_elapsed() << std::endl;
	}

	a.print_elapsed();

}
