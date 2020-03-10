#ifndef PRODUCER_H
#define PRODUCER_H

#include <sys/sem.h>
#include "buffer.h"

void producer(int , int , int , int , buffer* );

#endif