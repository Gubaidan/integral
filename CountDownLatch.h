//
// Created by Gubaidan on 2018/9/3.
//
#include<iostream>
#ifndef INTEGRAL_PP_H
#define INTEGRAL_PP_H

#endif //INTEGRAL_PP_H
class CountDownLatch
{
public:

    CountDownLatch();

    CountDownLatch(int count);  //构造方法

    void countDown();           //任务数减1

    int getCount();             //获取剩余任务

private:
    pthread_mutex_t mutex;      //互斥量，同步减少 jobs变量值
    int count_;
};

CountDownLatch::CountDownLatch(int count) {
    count_ = count;

}

void CountDownLatch::countDown() {
    pthread_mutex_lock(&mutex);
    count_--;
    pthread_mutex_unlock(&mutex);
}

int CountDownLatch::getCount() {
    return count_;
}

CountDownLatch::CountDownLatch() {

}
