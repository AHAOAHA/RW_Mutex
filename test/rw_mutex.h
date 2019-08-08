/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: rw_mutex.h
 * Author: ahaoozhang
 * Date: 2019-07-28 17:34:46 (星期日)
 * Describe: 
 *************************************************/
#ifndef __RW_MUTEX_H__
#define __RW_MUTEX_H__

#include <atomic>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

namespace AHAOAHA {

    class rw_mutex{
        const bool IS_WRITE = true;
        const bool NOT_WRITE = false;

        public:
            rw_mutex() {
                std::atomic_init(&_status, NOT_WRITE);
                std::atomic_init(&_r_count, uint64_t(0));
            }
            ~rw_mutex() {}

            bool r_lock();
            bool r_unlock();
            bool w_lock();
            bool w_unlock();
            uint32_t status() const;

        private:
            std::atomic<bool> _status;      //
            std::atomic<uint64_t> _r_count;       //原子性的计数
    };
}

#endif // rw_mutex
