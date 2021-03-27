# tetris
Our attempt to implement Tetris in C++

### Short ```internal_clock``` description:
The internal clock class consists of:
 -  Some clock attributes (start and tick rate, here called interval);
 -  A ```std::thread``` object:
    A thread is created and the clock "runs" inside of it. It is simply a combination of ```std::this_thread::sleep_for```
 -  ```mutex``` object to protect some operations;
 -  Some printing, get and set functions.

### How it was intended to use:
1. Instantiate the clock and initialize an interval:
   - ```internal_clock my_clock(const time_unit &x, unsigned int _res, lock_wrapper* _semaphore);```
   - Upon creation, the constructor will set the interval and private attributes (which includes creating an uninitialized ```std::thread```)
   - x is the interval, res is resolution, semaphore is a pointer ```lock_wrapper``` object, which encloses ```mutex``` and ```condition_variable``` objects and must be given by the calling thread.
2. Start the clock with run() method:
   - ```my_clock.run();```
   - This will initialize the ```std::thread``` object and it will automatically call the ```notify_all();``` method inside of ```lock_wrapper::condition_variable cv```, according to the given interval. Therefore, the calling thread must place the ```wait();``` method in a suitable location.

### Quick discussion:
There are still some issues regarding **expected behavior** x **actual implementation** of some methods, but they will be addressed as the project evolves.
In this update (27/03/2021), we suggest two methods: ```freeze();``` and ```resume();``` to enable pausing the game, but it has not been implemented yet.


## Tetriminos
![2880px-Tetrominoes_IJLO_STZ_Worlds svg](https://user-images.githubusercontent.com/19147489/109398997-d5ed2380-791e-11eb-9654-901fd01488e6.png)
