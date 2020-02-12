#ifndef BUFFER_H
#define BUFFER_H

#define MAX 5

typedef struct{
    int data[MAX];
    int front, rear, count;
} buffer;


void __init__ (buffer *);
void insertbuf(buffer *, int);
void deletebuf(buffer *);
void frontbuf (buffer *, int *);

#endif