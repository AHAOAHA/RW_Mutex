/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: rw_mutex.cpp
 * Author: ahaoozhang
 * Date: 2019-07-28 17:34:32 (星期日)
 * Describe: 
 *************************************************/
#include "rw_mutex.h"

bool AHAOAHA::SpinLock::lock() {
    //判断当前资源是否正在被其他写者占有
    bool w_exp = NOT_LOCK;
    while(!_status.compare_exchange_strong(w_exp, IS_LOCK)) {
        w_exp = NOT_LOCK;
    }
    //当资源正在别其他写者占有时 会一直再此地自旋 当状态不为IS_WRITE之后 会原子性的将状态改为IS_WRITE
    
    return true;
}

bool AHAOAHA::SpinLock::unlock() {
    bool exp = IS_LOCK;
    while(!_status.compare_exchange_strong(exp, NOT_LOCK)) {
        return false;
    }
    return true;
}
