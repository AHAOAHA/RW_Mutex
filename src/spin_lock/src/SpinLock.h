/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: rw_mutex.h
 * Author: ahaoozhang
 * Date: 2019-07-28 17:34:46 (星期日)
 * Describe: 
 *************************************************/
#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

#include <atomic>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

namespace AHAOAHA {

    class SpinLock {
        const bool IS_LOCK = true;
        const bool NOT_LOCK = false;
        public:
            SpinLock() {
                std::atomic_init(&_status, NOT_LOCK);
            }
            ~SpinLock() {}

            bool lock();
            bool unlock();

        private:
            std::atomic<bool> _status;      //
    };
}

#endif // spin_lock.h
