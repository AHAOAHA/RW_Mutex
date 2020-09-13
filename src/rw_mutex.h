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
#include <mutex>
#include <condition_variable>

namespace AHAOAHA {

    class RW_Mutex{
        public:
            RW_Mutex() {}
            ~RW_Mutex() {}

            void r_lock();
            bool r_unlock();
            void w_lock();
            bool w_unlock();
        private:
            RW_Mutex(const RW_Mutex&);
            RW_Mutex operator=(const RW_Mutex&);

        private:
            std::mutex _mtx;
            std::condition_variable _reader_cv;
            std::condition_variable _writer_cv;
            bool _write_able = true;
            int32_t _reader_count = 0;
            int32_t _writer_count = 0;
    };
}

#endif // rw_mutex
