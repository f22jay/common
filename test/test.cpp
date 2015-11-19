/***************************************************************************
 *
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$
 *
 **************************************************************************/

 /**
 * @file test/test.cpp
 * @author zhangfangjie(zhangfangjie@baidu.com)
 * @date 2015/11/19 10:56:21
 * @version $Revision$
 * @brief
 *
 **/

/* vim: set ts=4 sw=4 sts=4 tw=100 */
#include <iostream>
#include <pthread.h>
#include "../include/thread_pool.h"

void test() {
    std::cout<<"thread id "<<pthread_self()<<std::endl;
}

void test_thread_pool() {
    common::ThreadPool threadPool(10);
    threadPool.Start();
    for(int i = 0; i<10000000; i++) {
        threadPool.AddTask(test);
    }
    while (true) ;
}

int main() {
     test_thread_pool();
     return 0;
}
