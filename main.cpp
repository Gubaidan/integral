#include<iostream>
#include<cmath>
#include<zconf.h>
#include<ctime>
#include "CountDownLatch.h"

using namespace std;


struct Point
{
    double x, y, z, g;
};

pthread_mutex_t mutex_jobs;      //互斥量，同步减少 jobs变量值
pthread_mutex_t mutex_count;     //互斥量， 同步增加 nums_count变量值


int all_jobs = 10000000;      //全部随机落点个数，用于计算最终结果，计算过程中值不更改
int jobs = 10000000;          //全部随机落点个数， 用于任务分发，计算过程中值会减少
int nums_count = 0;           //命中积分区域落点个数
int strip = 10000;            //步长，每个线程请求的任务数
CountDownLatch *countDownLatch;


//随机数生成
double Rand(double L, double R)
{
    return L + (R - L) * rand() * 1.0 / RAND_MAX;
}

//获取随机数点
Point getPoint(double xl, double xh, double yl, double yh,double zl, double zh, double gl, double gh)
{
    Point t;
    t.x = Rand(xl, xh);
    t.y = Rand(yl, yh);
    t.z = Rand(zl, zh);
    t.g = Rand(gl, gh);
    return t;
}

//获得规定步长的任务，获取任务时进行同步
int tryGetWork(){
    int sub = 0;
    pthread_mutex_lock(&mutex_jobs);
    if(nums_count <= all_jobs){
        if((jobs-strip)>=0){            //如果剩余任务大于步长，则获得"步长（strip）"个任务
            sub = strip;
        }else{
            sub = jobs;                 //如果小于步长，则获得剩余所有任务
        }
        jobs -= sub;                    //从总任务数中减去获得的步长
    }
    pthread_mutex_unlock(&mutex_jobs);
    return sub;

}

//累加落在积分区域中的点
void tryAddCount(int total) {
    pthread_mutex_lock(&mutex_count);
    if(nums_count + total <= all_jobs){
        nums_count += total;
    }
    pthread_mutex_unlock(&mutex_count);
}


//积分计算函数
void *Thread_work(void *){
    int n = 0;
    while(jobs > 0){
        n = tryGetWork();                //jobs > 0时尝试获取任务
        if(n == 0) continue;             //如果获取失败则跳出本次循环进行下一次获取
        double x , y, z, g, total = 0;
        for(int i = 1;i <= n;i++)
        {
            Point t = getPoint(0.0, 4.0, 0.0, 3.0, 0.0, 2.0, 0.0, 133.0);   //获得积分区域内的随机点
            x = t.x; y = t.y; z = t.z; g = t.g;
            if(4.0*x*x + x*y*y + 5.0*y + y*z + 6.0*z >= g) total++;         //判断是否在四维空间内部 是则total++
        }
        tryAddCount(static_cast<int>(total));                               //调用累加函数，累加命中四维空间的点的个数
        printf("pid：：%ld  命中个数 ：%d\n", reinterpret_cast<long>(pthread_self()), static_cast<int>(total));
    }
    countDownLatch->countDown();                                      //当前线程执行完成
    pthread_exit(nullptr);
}



int main()
{
    pthread_mutex_init(&mutex_jobs, nullptr);            // 初始化
    pthread_mutex_init(&mutex_count, nullptr);           // 初始化
    srand(static_cast<unsigned int>(time(nullptr)));     //初始化随机函数
    long thread_nums = 10;                               //线程数
    countDownLatch = new CountDownLatch((int)thread_nums);       //初始化
    pthread_t *thread_handles;                           //线程队列
    int res;
    thread_handles = static_cast<pthread_t *>(malloc(thread_nums * sizeof(pthread_t)));
    for(long i = 0; i < thread_nums; i++){
        res = pthread_create(&thread_handles[i], nullptr, Thread_work, (void *) i);
        if (res) {
            printf("error : %d\n", res);
            exit(res);
        }
//        pthread_join(thread_handles[i], nullptr);     //会导致其他线程饿死
    }

    while(countDownLatch->getCount());                  //等待所有线程执行完毕

    printf("总落点数：%d\n", all_jobs);
    printf("命中个数：%d\n", nums_count);
    printf("命中概率：%.5lf\n", (nums_count / (double)all_jobs));
    printf("积分结果：%.5lf\n", (nums_count / (double)all_jobs) * 2.0 * 3.0 * 4.0 * 133.0);
    free(thread_handles);


    return 0;
}