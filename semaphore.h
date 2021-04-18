//
// Created by grilo on 17/04/2021.
// From here: https://riptutorial.com/cplusplus/example/30142/semaphore-cplusplus-11
//

#ifndef TETRIS_SEMAPHORE_H
#define TETRIS_SEMAPHORE_H


#include <mutex>
#include <condition_variable>

class semaphore {
public:
    semaphore (int count_ = 0)
            : count(count_)
    {
    }
    
    inline void notify( /*int tid*/ ) {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        //cout << "thread " << tid <<  " notify" << endl;
        //notify the waiting thread
        cv.notify_one();
    }
    inline void wait( /*int tid*/ ) {
        std::unique_lock<std::mutex> lock(mtx);
        while(count == 0) {
            //cout << "thread " << tid << " wait" << endl;
            //wait on the mutex until notify is called
            cv.wait(lock);
            //cout << "thread " << tid << " run" << endl;
        }
        count--;
    }
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};


#endif //TETRIS_SEMAPHORE_H
