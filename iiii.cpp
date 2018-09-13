//
// Created by Gubaidan on 2018/9/2.
//

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <atomic>
#include <unistd.h>

using namespace std;

//落在四维空间内的次数
static int num = 0;

//总的实验次数
static int sum = 1000000;

//线程总数
static int thread_sum = 1000;

//每个线程执行的实验次数 (=线程总数 / 总的实验次数)
static int sum_per_thread = 1000;

//剩下的实验数
static atomic<int> left_num;

//获取积分表达式的值（上限）
static double result(double x, double y, double z) {
 return 4 * x * x + x * y * y + 5 * y + y * z + 6 * z;
}

//获取随机数
static double random(int i) {
 double rand_num = (rand() / double(RAND_MAX)) * i;
// printf("随机数 : %f \n",(rand_num));
 return rand_num;
}

void *execute(void *threadid) {

 for(int i=0;i<sum_per_thread;i++){
  double x = random(4);
  double y = random(3);
  double z = random(2);
  double n = random(133);

  double res = result(x, y, z);

  if (n <= res) {
   num++;
  }

  left_num--;
 }

 pthread_exit(NULL);
}

int main() {

 left_num.store(sum);

 pthread_t threads[thread_sum];

 int rc;
 long t;
 for (t = 0; t < thread_sum; t++) {

  rc = pthread_create(&threads[t], NULL, execute, (void *) t);
  if (rc) {
   printf("error : %d\n", rc);
   exit(-1);
  }
 }

 while(left_num > 0){
  sleep(1);
 }

 printf("落入数 : %d \n",num);
 printf("总数 : %d \n",sum);
 printf("概率 : %.5lf \n " ,((double) num / (double) sum));
 printf("积分值 : %.5lf \n " ,((double) num / (double) sum)*2*3*4*133);

 pthread_exit(NULL);

 return 0;
}