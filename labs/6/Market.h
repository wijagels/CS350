#pragma once
#include <pthread.h>
#include <signal.h>

int market();
void sig_handler(int);
void watch_up();
void watch_down();

pthread_mutex_t _market_write_lock;
pthread_t _up_watch, _down_watch;
volatile float _market_value;
unsigned int _delta;
unsigned int _stocks;
