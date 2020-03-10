#include <pthread.h>
#include "list.h"

int main()
{
    int c = 5,d = 9,e = 100,g,x,y,z,k,K,m,sizeA,sizeB,sizeC,sizeD;
    genericLL *gll1,*gll_int,*gll_char,*gll_float,*gll_string;
    int A[] = {100,200,25,50,30,260};
    char B[] = {'c','o','d','e'};
    char *C[] = {"Sayan","Abhinav","Sagnik","Abhishek"};
    float  D[] = {5.6,6.7,9.2,3.4,2.1,87.9,8.32,4.5};


    printf("Testing the functions other than addNodeGLLSorted().\n");
    printf("...........................\n");

    gll1 = createGLL( sizeof(int), (int (*)(void*,void*))intCompare );
    addNodeGLL(gll1,&c);
    addNodeGLL(gll1,&d);
    addNodeGLL(gll1,&e);

    printf("Testing isPresentGLL().\n");

    x = isPresentGLL(gll1,&c);
    printf("Position %d present\n",x);

    y = isPresentGLL(gll1,&d);
    printf("Position %d present\n",y);

    z = isPresentGLL(gll1,&e);
    printf("Position %d present\n",z);

    printLL_int(gll1);

    k = deleteNodeGLL(gll1,&e);
    printf("position %d deleted\n",k);
    printf("Because of deletion of element 100, isPresentGLL(gll1,100) is false. \n");

    K = isPresentGLL(gll1,&e);
    (void)K;//to remove unused variable warning.
    printf("......\n");
    printLL_int(gll1);

    m = getNodeDataGLL(gll1,2,&g);
    (void)m;//to remove unused variable warning.
    printf("getNodeDataGLL() gives %d from position 2\n",g);
    printf("...........................\n");

    //...................................................................................//

    printf("Testing addNodeGLLSorted().\n");
    printf("...........................\n");


    sizeA = sizeof(A)/sizeof(A[0]);
    gll_int = createGLL( sizeof(int) ,  (int (*)(void*,void*))intCompare );

    for(int i = 0;i<sizeA;i++)
    {
        addNodeGLLSorted(gll_int,&A[i]);
    }
    printf("Sorted Integer linked list :\n");
    printLL_int(gll_int);
    printf("..................................\n");


    sizeB = sizeof(B)/sizeof(B[0]);
    gll_char = createGLL( sizeof(char) ,  (int (*)(void*,void*))strcmp );

    for(int i = 0;i<sizeB;i++)
    {
        addNodeGLLSorted(gll_char,&B[i]);
    }
    printf("Sorted Character linked list :\n");
    printLL_char(gll_char);
    printf("................................\n");


    sizeC = sizeof(C)/sizeof(C[0]);
    gll_string = createGLL( sizeof(char **) ,  stringCompare );
    for(int i = 0;i<sizeC;i++)
    {
        addNodeGLLSorted(gll_string,&C[i]);
    }
    printf("Sorted String linked list :\n");
    printLL_string(gll_string);
    printf("................................\n");


    printf("Sorted floating point numbers linked list :\n");
    sizeD = sizeof(D)/sizeof(D[0]);
    gll_float =  createGLL( sizeof(float),  floatCompare );

    for(int i = 0;i<sizeD;i++)
    {
        addNodeGLLSorted(gll_float,&D[i]);
    }

    printLL_float(gll_float);
    printf("..................................\n");

}
