#include "Market.h"
#include "Stock.h"
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int market() {
    srand(time(NULL));
    _market_value = 100 * _stocks;
    pthread_t threads[_stocks];
    pthread_create(&_up_watch, NULL, (void*)watch_up, NULL);
    pthread_create(&_down_watch, NULL, (void*)watch_down, NULL);
    for(int i = 0;i < _stocks;i++) {
        pthread_create(&threads[i], NULL, (void*)hurr_durr_im_a_stock, NULL);
    }
    pthread_join(_up_watch, NULL);
    pthread_join(_down_watch, NULL);
    for(int i = 0;i < _stocks;i++) {
        pthread_cancel(threads[i]);
    }
    return 0;
}

void sig_handler(int signum) {
    pthread_exit(0);
}


void watch_up() {
    signal(SIGUSR1, sig_handler);
    while(1) {
        pthread_mutex_lock(&_market_write_lock);
        // fprintf(stdout, "%f\n", _market_value);
        // fprintf(stdout, "%f\n", (1.0+((float)_delta/100)) * 100  * (float)_stocks);
        if(_market_value > (1.0+((float)_delta/100)) * 100  * (float)_stocks) {
            fprintf(stdout, "Market up to %f\n", _market_value);
            fprintf(stdout, "Total Market Price of %d Stocks: %f\n", _stocks, _market_value);
            pthread_kill(_down_watch, SIGUSR1);
            pthread_mutex_unlock(&_market_write_lock);
            pthread_exit(0);
        }
        pthread_mutex_unlock(&_market_write_lock);
    }
}


void watch_down() {
    signal(SIGUSR1, sig_handler);
    while(1) {
        pthread_mutex_lock(&_market_write_lock);
        // fprintf(stdout, "%f\n", (1.0-((float)_delta/100)) * 100 * (float)_stocks);
        if(_market_value < (1.0-((float)_delta/100)) * 100 * (float)_stocks) {
            fprintf(stdout, "Market down to %f\n", _market_value);
            fprintf(stdout, "Total Market Price of %d Stocks: %f\n", _stocks, _market_value);
            pthread_kill(_up_watch, SIGUSR1);
            pthread_mutex_unlock(&_market_write_lock);
            pthread_exit(0);
        }
        pthread_mutex_unlock(&_market_write_lock);
    }
}
