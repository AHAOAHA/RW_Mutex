/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: rw_mutex.cpp
 * Author: ahaoozhang
 * Date: 2019-07-28 17:34:32 (星期日)
 * Describe: 
 *************************************************/
#include "rw_mutex.h"

bool AHAOAHA::rw_mutex::r_lock() {
    bool exp = NOT_WRITE;
    while (!_status.compare_exchange_strong(exp, NOT_WRITE)) {
        exp = NOT_WRITE;
    }
    //当status为NOT_WRITE 使用NOT_WRITE刷新_status和exp
    //当status为IS_WRITE cas会使用_status刷新exp的值 需要在循环内部更新exp的值

    _r_count.fetch_add(1);
    return true;
}

bool AHAOAHA::rw_mutex::r_unlock() {
    _r_count.fetch_sub(1);
    return true;
}

bool AHAOAHA::rw_mutex::w_lock() {
    //判断当前资源是否正在被其他写者占有
    bool w_exp = NOT_WRITE;
    while(!_status.compare_exchange_strong(w_exp, IS_WRITE)) {
        w_exp = NOT_WRITE;
    }
    //当资源正在别其他写者占有时 会一直再此地自旋 当状态不为IS_WRITE之后 会原子性的将状态改为IS_WRITE
    
    //等待之前的读者全部退出
    uint64_t exp = 0;
    while(!_r_count.compare_exchange_strong(exp, 0)) {
        exp = 0;
    }
    //当前读者不为0时 exp值会被cas刷新为当前读者的值 需要在循环内部刷新exp值
    //当前读者为0时 exp值和_r_count的值会被val刷新

    return true;
}

bool AHAOAHA::rw_mutex::w_unlock() {
    bool exp = IS_WRITE;
    while(!_status.compare_exchange_strong(exp, NOT_WRITE)) {
        return false;
    }
    return true;
}
