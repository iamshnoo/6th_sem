#include "buff.h"
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>

void __init__(buffer *q){
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

void insertbuf(buffer *q, int n){
    q->rear = (q->rear + 1 ) % MAX;
    q->data[q->rear] = n;
    q->count = q->count + 1;
}

void deletebuf(buffer *q){
    q->front = (q->front + 1) % MAX;
    q->count = q->count - 1;
}

void frontbuf (buffer *q, int *n){
    *n = q->data[(q->front + 1) % MAX];
}

