#include <sched.h>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

const int NSEC_PER_SEC = 1000 * 1000 * 1000; /* The number of nsecs per sec. */
const int MICROSEC_PER_SEC = 1000 * 1000;    /* The number of nsecs per sec. */
const int SAMPLINGTIME = 5 * 1000 * 1000;    /* 1ms = 1000us = 1000*1000us*/

int main() {
  // pseudo-real time
  std::timespec t;
  struct sched_param param;
  param.sched_priority = 1;
  if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
    perror("sched_setscheduler failed");
    exit(-1);
  }

  // get current time
  /// for periodic execution
  clock_gettime(CLOCK_MONOTONIC, &t);
  /* start after one second */
  t.tv_sec++;

  /// for elapsed time
  auto start_time = std::chrono::high_resolution_clock::now();
  auto before_time = start_time;
  while (1) {
    /* wait until next shot */
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);

    auto now = std::chrono::high_resolution_clock::now();
    double elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(now - start_time)
            .count();
    double elapsed2 =
        std::chrono::duration_cast<std::chrono::microseconds>(now - before_time)
            .count();

    /* do something */
    std::cout << std::fixed << std::setprecision(7);
    std::cout << elapsed / (double)MICROSEC_PER_SEC << ", "
              << elapsed2 / (double)MICROSEC_PER_SEC  << std::endl;
    before_time = now;

    /* calculate next shot */
    t.tv_nsec += SAMPLINGTIME;
    while (t.tv_nsec >= NSEC_PER_SEC) {
      t.tv_nsec -= NSEC_PER_SEC;
      t.tv_sec++;
    }
  }

  return 0;
}