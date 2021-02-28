#include <iostream>
#include <thread>
#include <iostream>
#include "user-input.h"

int main() {
    
    int time = 10e3;
    
    std::cout << "This will work for " << time << " milliseconds." << std::endl;
    std::cout << "Press arrow keys or anything to test." << std::endl;
    
    initUserInput();
    
    std::thread ui(loopReadUserInput);
    
    auto timeInit = std::chrono::high_resolution_clock::now();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    
    do {
        timeEnd = std::chrono::high_resolution_clock::now();
    } while( std::chrono::duration<double, std::milli>{timeEnd - timeInit}.count() < time );
    
    keepLooping = false;
    
    std::cout << "precisa juntar?" <<std::endl;
    
    if(ui.joinable()) {
        std::cout << "sim!" << std::endl;
        std::cout << "esperando juntar" << std::endl;
        ui.join();
    
        std::cout << "juntou" << std::endl;
    } else {
        std::cout << "nao!" << std::endl;
    }
    
    std::cout << "acabou!" << std::endl << std::endl;
    
    endUserInput();
    
    return 0;
}
