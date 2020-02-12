

void producer (buffer *qp, int semID){
    int count = 1;
    srand(getpid());
    while(count <= 10){
        int data;
        data = rand();
        Wait(semID, 1);     // wait(empty)
        Wait(semID, 0);     // wait(mutex)
        insertbuf(qp,data); // critical section
        Signal(semID,0);    // signal(mutex)
        Signal(semID,2);    // signal(full)
        printf("Process [%d] produced data %d. \n". getpid(),data);
        sleep(2);
    }
}

void consumer (buffer *qp, int semID){
    int count = 1;
    while(count<=10){
        int data;
        Wait(semID, 2);      // wait(full)
        Wait(semID, 0);      // wait(mutex)
        frontbuf(qp,&data);  // critical section
        deletebuf(qp);       // critical section
        Signal(semID, 0);    // Signal(mutex)
        Signal(semID, 1);    // Signal(empty)
        printf("Process [%d] consumerd data %d. \n". getpid(),data);
    }
}