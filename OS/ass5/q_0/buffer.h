#ifndef BUFFER_H
#define BUFFER_H

#define MAX 5

typedef struct{
    int data[MAX];
    int front, rear, count;
} buffer;


buffer* createbuf (int);
int     insertbuf (buffer *);
int     deletebuf (buffer *);

#endif