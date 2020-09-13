/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: rw_mutex.cpp
 * Author: ahaoozhang
 * Date: 2019-07-28 17:34:32 (星期日)
 * Describe: 
 *************************************************/
#include "rw_mutex.h"

void AHAOAHA::RW_Mutex::r_lock() {
    std::unique_lock<std::mutex> lock(_mtx);
    _reader_cv.wait(lock, [&] {return 0 == _writer_count;});
    ++_reader_count;
}

bool AHAOAHA::RW_Mutex::r_unlock() {
    std::unique_lock<std::mutex> lock(_mtx);
    if (_reader_count == 0) {
        return false;
    }
    --_reader_count;
    _writer_cv.notify_one();
    return true;
}

void AHAOAHA::RW_Mutex::w_lock() {
    std::unique_lock<std::mutex> lock(_mtx);
    ++_writer_count;
    _writer_cv.wait(lock, [&] {return (0 == _reader_count) && (_write_able == true);});
    _write_able = false;
}

bool AHAOAHA::RW_Mutex::w_unlock() {
    std::unique_lock<std::mutex> lock(_mtx);
    if (_writer_count == 0) {
        return false;
    }

    --_writer_count;
    _write_able = true;
    if (0 == _writer_count) {
        _reader_cv.notify_all();
    } else {
        _writer_cv.notify_one();
    }
    return true;
}
