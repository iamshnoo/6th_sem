#include "list.h"

/*
Can take data of 2 nodes of this list as parameters and compare them.
Returns 0 if data1 and data2 are "same",-1 if data1 is "less than" data2
and 1 if data1 is "greater than" data2.
*/

//Function to compare two integers.
int intCompare(void* data1,void* data2)
{
    int *p1,*p2 ;
    p1 = (int *)data1;
    p2 = (int *)data2;
    return (*p1 - *p2);
}

//Function to compare two strings.
int stringCompare(void* data1,void* data2)
{
    char ** a, **b;
    a = data1;
    b = data2;
    return strcmp(*a,*b);
}

//Function to compare two floating point numbers.
int floatCompare(void* data1,void* data2)
{
	float *a,*b ;
        a = (float*)data1;
        b = (float*)data2;
	if(*a>*b)
		return 1;
	if(*a == *b)
		return 0;
	else
		return -1;
}

//Allocates minimal required space (struct gll) for the list and returns a reference to that.
genericLL* createGLL(int dsize, int (*cfunction)(void *, void *))
{
    // Allocate space for a structure of type genericLL.
    genericLL *LL ;
    LL = (genericLL*)malloc(sizeof(genericLL));
    if(LL == NULL)
        printf("Space can't be allocated.\n");

    //Assign value to the fields of the created structure.
    LL->dsize = dsize;
    LL->compareFn = cfunction;
    LL->list = NULL;

    return LL;

}

/*
Adds a new node at the end of the linked list g.
The data of the new node comes from d. contain that is being llocates (mallocs) a  new node,
copies the contents of the parameter s in the newly allocated node and adds the node to
the linked list referred to by "start" (that is, whose 1st node is pointed to by the parameter start).
The function returns the address of the 1st node of the resulting linked list.
*/

void addNodeGLL(genericLL * g, void *d)
{
    //Head of LL is given by g->list.

    if(g->list == NULL) //No LL exists yet.
    {

        node *temp ;
        temp = (node*)malloc(sizeof(node));
        temp->data = malloc(g->dsize);
        temp->next = NULL;
        memcpy(temp->data, d, g->dsize);
        g->list = temp;

    }

    else
    {
        node *current;
        current = g->list;

        while(current->next!=NULL)// Traverse to the end of the LL.
        {
            current = current->next;
        }

        node *temp ;
        temp = (node*)malloc(sizeof(node));
        temp->data = malloc(g->dsize);
        temp->next = NULL;
        memcpy(temp->data, d, g->dsize);
        current->next = temp;

    }

}

/*
Similar to addNodeGLL().
This function, however, does not add the new node at the end of the linked list.
This function assumes that the existing linked list associated with g
is already sorted in ascending order and the new node should be added somewhere
in the linked list so that after the addition the linked list will remain sorted in ascending order.
*/

void addNodeGLLSorted(genericLL *g, void *d)
{
    //Head of LL is given by g->list.

    if(g->list == NULL || (g->compareFn)( g->list->data,d ) >= 0)
    {

        node *temp ;
        temp = (node*)malloc(sizeof(node));
        temp->data = malloc(g->dsize);
        temp->next = NULL;

        memcpy(temp->data, d, g->dsize);

        temp->next = g->list;
        g->list = temp;

    }

	else
	{
		/*A temporary node used to traverse along the linked list,
		is assigned to start.*/
		node *current;
		current = g->list;

		while(current->next!=NULL && (g->compareFn)( current->next->data,d  ) < 0)
		{
			/*Traverse along the linked list till you reach the end and
			with the restriction of sorted entry.*/
		    current = current->next;
		}

		/*After reaching the desired position by traversal,
		the new node is inserted at the correct sorted position.*/

		node *temp ;
                temp = (node*)malloc(sizeof(node));
		temp->data = malloc(g->dsize);
    		temp->next = NULL;

    		memcpy(temp->data, d, g->dsize);

        	temp->next = current->next;
        	current->next = temp;

	}

}

/*
Searches for presence of a node (in the linked list associated with g) whose
data matches with whatever available at d(the 2nd parameter of the function). If such a node is found,
the function returns its position in the linked list,
otherwise (such a node is not there) the function returns 0.
*/
int isPresentGLL(genericLL * g, void *d)
{
    //Head of LL is given by g->list.

    //A temporary node for traversal.
    node *temp;
    temp = g->list;

    int position = 1;

    while(temp!=NULL)
    {
        //if temp->data = d , return position
        if((g->compareFn)( d, temp->data ) == 0)
        {
            return position;
        }

        temp = temp->next;
	position++;

    }

    printf("Data not found\n");// Executes if LL is empty or has been completely traversed without finding matching data.
    return 0;

}

/*
Deletes the 1st node of the linked list  (associated with g) whose data
matches with whatever available at d(the 2nd parameter of the function). If such a node is deleted,
the function returns the position it had in the linked list,
otherwise (such a node is not there) the function returns 0. The deleted node must be freed too.
*/
int deleteNodeGLL(genericLL * g, void *d)
{
    //Head of LL is given by g->list.

    //A temporary node for traversal.
    node *temp;
    temp = g->list;

    // If the starting node itself is to be deleted.
    if((g->compareFn)( d, temp->data ) == 0)
    {
        g->list = temp->next;
	free(temp);
        //Start was deleted.
        return 1;
    }

    else
    {
        int position = 1;
        while(temp!=NULL)// Traverse the Linked list till there are no more nodes.
        {
            if((g->compareFn)( d, temp->next->data  ) == 0)
            {
                node *temp1;
                temp1 = temp->next;
		temp->next = temp1->next;
		free(temp1); // free the node to be deleted from linked list.
                position++;
                return position;
            }

            temp = temp->next;
        }
    }

    printf("No match detected.\n");
    return 0;

}

//Copies the data of the ith node of the linked list (associated with g) to d.
//The function returns 0 if such a node does not exist. Otherwise it returns 1.

int getNodeDataGLL(genericLL * g, int i, void *d)
{
    //Head of LL is given by g->list.

    //a temporary node for traversal.
    int position = 1;
    node *temp;
    temp = g->list;

    if (temp==NULL) return 0;
    while(position != i && temp!= NULL)
    {
        temp = temp->next;
        position++;
    }

    if(temp!=NULL)
    {
    	memcpy(d, temp->data, g->dsize);
    	return 1;
    }
    return 0;

}


/*Function to print the character linked list.*/
void printLL_char(genericLL * g)
{
    	node *temp;
	temp = g->list;

	int position = 1;
	//Loop to traverse the linked list.
	while(temp!=NULL)
	{
        	char current;
        	int m ;
		m = getNodeDataGLL(g,position,&current);
        	(void)m;//to remove unused variable warning.
        	printf("%c\n",current);
		temp = temp->next;
        	position++;
	}
}

/*Function to print the integer linked list.*/
void printLL_int(genericLL * g)
{
    	node *temp;
	temp = g->list;

	int position = 1;
	//Loop to traverse the linked list.
	while(temp!=NULL)
	{

        	int current;
        	int m ;
		m = getNodeDataGLL(g,position,&current);
        	(void)m;//to remove unused variable warning.
        	printf("%d\n",current);
		temp = temp->next;
        	position++;
        }
}

/*Function to print the float linked list.*/
void printLL_float(genericLL * g)
{
    	node *temp;
	temp = g->list;

	int position = 1;
	//Loop to traverse the linked list.
	while(temp!=NULL)
	{
        	float current;
        	int m;
		m = getNodeDataGLL(g,position,&current);
        	(void)m;//to remove unused variable warning.
        	printf("%.2f\n",current);
		temp = temp->next;
        	position++;
        }

}

/*Function to print the strings linked list.*/
void printLL_string(genericLL * g)
{
    	node *temp;
	temp = g->list;

	//Loop to traverse the linked list.
	while(temp!=NULL)
	{
        	char *current;
		printf("%s\n", *((char **)temp->data));
		temp = temp->next;
        }
}