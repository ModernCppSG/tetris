# tetris
[![CMake](https://github.com/ModernCppSG/tetris/actions/workflows/cmake.yml/badge.svg)](https://github.com/ModernCppSG/tetris/actions/workflows/cmake.yml)

Our attempt to implement Tetris in C++
### Short ```internal_clock``` description:
The internal clock class consists of:
 -  Some clock attributes (start and tick rate, here called interval)
 -  A ```std::thread``` object:
    A thread is created and the clock "runs" inside of it. It is simply a combination of ```std::this_thread::sleep_for```
 -  Some printing, get and set functions.

### How it was intended to use:
1. Instantiate the clock and initialize an interval:
   - ```internal_clock my_clock(std::chrono::milliseconds(200));```
   - Upon creation, the constructor will set the interval and private attributes (which includes creating an uninitialized ```std::thread```)
2. Start the clock with run() method:
   - ```my_clock.run();```
   - This will initialize the ```std::thread``` object and make the private variable ```internal_clock::is_interval_elapsed``` fire according to the set interval. You may check it with:
   - ```my_clock.get_is_elapsed();```

### Quick discussion:
As of now, the game engine will have to regularly check the clock and may also use a sleep function, such as ```std::this_thread::sleep_for```, which misses the point of creating an independent clock. A possible (currently under consideration) solution is using a ```<condition_variable>``` or ```<mutex>```. Although condition variables could indeed solve this problem, they cannot target specific threads. This might not cause any problem in this implementation, but, IMHO this is not a good pratice/solution. ```<mutex>``` option was not yet thoroughly studied.

There are still some issues regarding **expected behavior** x **actual implementation** of some methods, but they will be addressed as the project evolves.


## Tetriminos
![2880px-Tetrominoes_IJLO_STZ_Worlds svg](https://user-images.githubusercontent.com/19147489/109398997-d5ed2380-791e-11eb-9654-901fd01488e6.png)
