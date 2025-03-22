#include <stdio.h>  // for input and output
#include <stdlib.h> // in order to manage memory , to use malloc and free
#include <string.h> // to be able to use string operations

typedef struct Node
{   // I defined a node for the linked list structure, a node for every element
    // there are user id, item id, rating itself and a pointer to the next node in each node.
    int userid;
    int itemid;
    float rating;
    struct Node *next; // this is the pointer to the next node, self referential pointer.
} Node;

Node *head = NULL; // this is the global pointer to the initial node, the head, of the LL. set to null at first since the LL is empty.

// this is for finding a node by userid and itemid.
Node *findNode(int userid, int itemid)
{
    Node *current = head; // this starts it from the head of the list.
    // current is the pointer that goes through LL.

    // loops through every node and if it finds a match returns the pointer to that exact node.
    while (current != NULL)
    {
        if (current->userid == userid && current->itemid == itemid)
        {
            return current;
        }
        current = current->next;
    }
    return NULL; // if no match returns null.
}

// INSERT function
void insert(int userid, int itemid, float rating)
{

    Node *existing = findNode(userid, itemid); // checks if specific rating already exists.

    if (existing != NULL)
    {                                                                      // if node exists updates the rating
        existing->rating = rating;                                         // the existing pointer points to the in memory node directly
        printf("\nCustomer rating (%d, %d) is updated\n", userid, itemid); // print update
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node)); // memory allocation for new node and this returns a pointer to that memory.
    // value fillings.
    newNode->userid = userid;
    newNode->itemid = itemid;
    newNode->rating = rating;
    // a link to new node from the old node
    newNode->next = head;
    // update head in order to point to new first node
    head = newNode;

    printf("Customer rating (%d, %d) is added successful\n", userid, itemid); // print insertion
}

// REMOVE function
void removeRating(int userid, int itemid)
{
    // starts from the head
    Node *current = head; // use current to move through LL
    Node *prev = NULL;    // prev is to remember the node previous to the current.

    while (current != NULL)
    { // this loop finds the node to be deleted if ids match
        if (current->userid == userid && current->itemid == itemid)
        {
            if (prev == NULL)
            {
                head = current->next; // if it is head, update
            }
            else
            {
                prev->next = current->next;
            }
            free(current);                                                              // deallocate the memory for the removed node.
            printf("Customer rating (%d, %d) is removed successful\n", userid, itemid); // print removal.
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Customer rating (%d, %d) does not exist\n", userid, itemid); // print if rating does not exist.
}

// get rating function
void getRating(int userid, int itemid)
{
    Node *node = findNode(userid, itemid);
    // finding the node
    if (node != NULL)
    {
        printf("Customer rating (%d, %d) is: %.1f\n", userid, itemid, node->rating); // print rating.
    }
    else
    {
        printf("Customer rating (%d, %d) is: 0.0\n", userid, itemid); // 0.0 if not exists.
    }
}

// average rating function
void averageRating(int itemid)
{
    Node *current = head;
    float total = 0.0;
    int count = 0;

    while (current != NULL)
    { // loop through the list to find all the ratings for the item.
        if (current->itemid == itemid)
        {
            total += current->rating;
            count++;
        }
        current = current->next;
    }
    // add them up and count the ratings to find average
    float average = (count > 0) ? total / count : 0.0;
    printf("Average rating (%d) is: %.1f\n", itemid, average); // print average, if there is no rating it is 0.0
}

// processesLine function
void processLine(char *line)
{
    char command[20];
    int userid, itemid;
    float rating;

    // this is to read one line and understand the arguments and call the functions related.
    if (sscanf(line, "%s", command) == 1)
    {
        if (strcmp(command, "INSERT") == 0)
        { // for insert
            sscanf(line, "%*s %d %d %f", &userid, &itemid, &rating);
            insert(userid, itemid, rating);
        }
        else if (strcmp(command, "REMOVE") == 0)
        { // for remove
            sscanf(line, "%*s %d %d", &userid, &itemid);
            removeRating(userid, itemid);
        }
        else if (strcmp(command, "RATING") == 0)
        { // for rating
            sscanf(line, "%*s %d %d", &userid, &itemid);
            getRating(userid, itemid);
        }
        else if (strcmp(command, "AVERAGE") == 0)
        { // for average
            sscanf(line, "%*s %d", &itemid);
            averageRating(itemid);
        }
        else
        {
            printf("Wrong command !!!: %s\n", command); // if command is wrong.
        }
    }
}

int main()
{
    char line[256];
    while (fgets(line, sizeof(line), stdin))
    {                      // this keeps on reading input until user performs a Ctrl+D on the terminal. fgets reads only one item at a time.
        processLine(line); // and every line goes to processLine function in order to call according functions.
    }

    //
    Node *current = head;
    while (current != NULL)
    {                            // loop through the LL
        Node *temp = current;    // temp pointer for in order to free each node
        current = current->next; // I used temp pointer to prevent potential memory leak.
        free(temp);
    }

    return 0; // program finish
}
