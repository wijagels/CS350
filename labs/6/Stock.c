#include "Stock.h"
#include "Market.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void hurr_durr_im_a_stock() {
    signal(SIGUSR1, sig_handler);
    while(1) {
        pthread_mutex_lock(&_market_write_lock);
        double random = ((float)rand()/((float)RAND_MAX/2))-1;
        _market_value += random;
        pthread_mutex_unlock(&_market_write_lock);
    }
}
