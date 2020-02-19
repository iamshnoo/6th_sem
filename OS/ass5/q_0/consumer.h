#ifndef CONSUMER_H
#define CONSUMER_H

#include <sys/sem.h>
#include "buffer.h"

void consumer(int , int , int , int , buffer* );

#endif