/*************************************************
 * Copyright(C) 2016-2019. All right reserved.
 * 
 * Filename: test.cpp
 * Author: ahaoozhang
 * Date: 2019-08-04 20:21:22 (星期日)
 * Describe: 
 *************************************************/
#include "test.h"

int num = 0;
int count = 0;
AHAOAHA::rw_mutex rw_mtx;


void read() {
    rw_mtx.r_lock();
    printf("num = %d, count: %d\n", num, count++);
    rw_mtx.r_unlock();
}

void write() {
    rw_mtx.w_lock();
    num++;
    rw_mtx.w_unlock();
}

void* read_handle(void* arg) {
    //while(1) {
        read();
    //}
    return arg;
}

void* write_handle(void* arg) {
    //while(1) {
        write();
    //}
    return arg;
}

int main() {
    pthread_t p1;
    pthread_t p2;


    //for(int i = 0; i < 100000; i++) {
    //    pthread_create(&p1, NULL, read_handle, NULL);
    //}


    for(int i = 0; i < 1000; i++) {
        pthread_create(&p2, NULL, write_handle, NULL);
    }

    while(1) {   //主线程不退出
        printf("current num: %d\n", num);
        sleep(1);
    }
    return 0;
}
