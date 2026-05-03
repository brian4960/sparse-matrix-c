#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct Node {
    ListElement data;
    struct Node* next;
    struct Node* prev;
} Node;

// private ListObj type
typedef struct ListObj {
    Node* front;
    Node* back;
    Node* cursor;
    int length;
    int position;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns a pointer to new Node object. Initializes next and data fields.
Node* newNode(ListElement data) {
    Node* N = malloc(sizeof(Node));
    assert( N!=NULL );
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

// newList() 
// Creates a new empty list. 
List newList() {
    List L;
    L = malloc(sizeof(ListObj));
    assert( L!=NULL );
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->position = -1;
    return(L);
}

// freeList()
// Frees heap memory associated with *pL, sets *pL to NULL. 
// We use a pointer to List so that we can set the List = NULL by *pL = NULL.
// We don't use List type itself in the call because you can't make a change to the call.
// Therefore, you can't make the List = NULL if the List is in the call ().
// If you don't pass a pointer, it simply creates a local copy. 
// We want the List type that pL points to to be set to NULL.
void freeList(List* pL) {
    if (pL!=NULL && *pL!=NULL) { 
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions ----------------------------------------------------------- 

// length()
// Returns the number of elements in L.
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: length(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    return (L->length);
}

// position()
// If cursor is defined, returns the position of the cursor element, otherwise
// returns -1.
int position(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: position(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        return -1;
    }

    return (L->position);
}

// front()
// Returns front element. Pre: length()>0
ListElement front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: front(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: front(): empty List\n");
        exit(EXIT_FAILURE);
    }

    return (L->front->data);
}

// back()
// Returns back element. Pre: length()>0
ListElement back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: back(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: back(): empty List\n");
        exit(EXIT_FAILURE);
    }

    return (L->back->data);
}

// Returns cursor element. Pre: length()>0, position()>=0
ListElement get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: get(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: get(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (position(L) < 0) {
        fprintf(stderr, "List Error: get(): undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    return (L->cursor->data);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: clear(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node* current_node = L->front;
    Node* next_node;

    while (current_node != NULL) {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->position = -1;
}

// set ()
// Overwrites the cursor element's data with x. Pre: length()>0, position () >=0
void set(List L, ListElement x) {
    if (L == NULL) {
        fprintf(stderr, "List Error: set(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: set(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (position(L) < 0) {
        fprintf(stderr, "List Error: set(): undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
}

// moveFront ()
// If L is non-empty, places the cursor under the front element, otherwise does
// nothing.
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveFront(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        return;
    }

    L->cursor = L->front;
    L->position = 0;
}

// moveBack()
// If List is non-empty, places the cursor under the back element, otherwise
// does nothing.
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveBack(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        return;
    }

    L->cursor = L->back;
    L->position = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward front of
// L, if cursor is defined and at front, cursor becomes undefined, if cursor is
// undefined does nothing.
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: movePrev(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        return;
    }

    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->position = -1;
        return;
    }

    L->cursor = L->cursor->prev;
    L->position--;
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward back of
// L, if cursor is defined and at back, cursor becomes undefined, if cursor is
// undefined does nothing.
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: moveNext(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == NULL) {
        return;
    }

    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->position = -1;
        return;
    }

    L->cursor = L->cursor->next;
    L->position++;
}

// prepend()
// Insert new element into L. If List is non-empty, insertion takes place
// before front element.
void prepend(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: prepend(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    Node* temp = newNode(data);

    if (length(L) == 0) {
        L->front = temp;
        L->back = temp;

    } else {
        temp->next = L->front;
        L->front->prev = temp;
        L->front = temp;
    }

    // Length always increases by 1
    L->length++;

    // Only increase cursor position (index) value by 1 if the cursor is currently pointing to something
    if (L->cursor != NULL || L->position > -1) {
        L->position++;
    }   
}

// append()
// Insert new element into L. If List is non-empty, insertion takes place
// after back element.
void append(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: append(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    
    Node* temp = newNode(data);

    if (length(L) == 0) {
        L->front = temp;
        L->back = temp;

    } else {
        temp->prev = L->back;
        L->back->next = temp;
        L->back = temp;
    }

    // Length always increases by 1
    L->length++;
}

// insertBefore()
// Insert new element before cursor. Pre: length()>0, position()>=0
// position variable should be adjusted accordingly
// i.e. if position = 3 and you insert a variable at position 2 , position should be increased to 4
void insertBefore(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: insertBefore(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: insertBefore(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (position(L) < 0) {
        fprintf(stderr, "List Error: insertBefore(): undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    // Temp node
    Node* temp = newNode(data);

    if (position(L) == 0) {                          // Checks if there is a new front element
        temp->next = L->cursor;
        L->cursor->prev = temp;
        L->front = temp;
    } else {
        // Link the new node to the linked list
        temp->next = L->cursor;
        temp->prev = L->cursor->prev;

        // Place it in the middle
        L->cursor->prev->next = temp;
        L->cursor->prev = temp;
    }

    // Always increase position and length by 1 b/c you are inserting an element behind the current one
    L->length++;
    L->position++;
}

// insertAfter ()
// Inserts new element after cursor. Pre: length()>0, position()>=0
void insertAfter(List L, ListElement data) {
    if (L == NULL) {
        fprintf(stderr, "List Error: insertAfter(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: insertAfter(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (position(L) < 0) {
        fprintf(stderr, "List Error: insertAfter(): undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    // Temp node
    Node* temp = newNode(data);

    if (position(L) == length(L) - 1) {              // Checks if there is a new back element
        temp->prev = L->cursor;
        L->cursor->next = temp;
        L->back = temp;
    } else {
        temp->next = L->cursor->next;
        temp->prev = L->cursor;

        L->cursor->next->prev = temp;
        L->cursor->next = temp;
    }

    // Increase length by 1
    L->length++;
}

// deleteFront ()
// Deletes the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: deleteFront(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: deleteFront(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 1) {                                     // Check if there is only one (front) node
        // Since we are removing the one and only node, we can simply reset L back to its original state
        clear(L);
    } else {
        // Create a pointer to the front node so that we can later have access to it to free it
        Node* temp = L->front;

        // Update front node
        L->front = L->front->next;
        L->front->prev = NULL;

        if (position(L) == 0) {                              // Check if the cursor is set to front node
            L->cursor = NULL;
            L->position = -1;
        } else if (L->cursor != NULL) {
            // If the cursor is not set to the front element and exists, we can simply decrement by 1
            L->position--;
        }

        // Decrease length by 1 and free the node
        L->length--;
        free(temp); 
    }
}

// deleteBack()
// Deletes the back element. Pre: length()>0
// Adjust position variable accoridngly
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: deleteBack(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: deleteBack(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) == 1) {                                     // Check if there is only one (front) node
        // Since we are removing the one and only node, we can simply reset L back to its original state
        clear(L);
    } else {
        Node* temp = L->back;

        L->back->prev->next = NULL;
        L->back = L->back->prev;

        if (position(L) == length(L) - 1) {                              // Check if the cursor is set to front node
            L->cursor = NULL;
            L->position = -1;
        }

        // Decrease length by 1 and free the node
        L->length--;
        free(temp); 
    }
}

// delete ()
// Deletes cursor element, making cursor undefined. Pre: length()>0, position() >=0
// Adjust position variable accordingly
// So, make cursor = NULL, position = -1
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: delete(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: delete(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (position(L) < 0) {
        fprintf(stderr, "List Error: delete(): undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    if (L->position == 0) {
        deleteFront(L);
    } else if (L->position == length(L) - 1) {
        deleteBack(L);
    } else {
        Node* temp = L->cursor;

        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;

        free(temp);
        L->cursor = NULL;
        L->position = -1;
        L->length--;
    }
}

// Other operations -----------------------------------------------------------

// join()
// Returns the concatenation of A followed by B. The cursor in the new List is
// undefined, regardless of the states of the cursors A in and B. The states of
// A and B are unchanged.
List join(List A, List B) {
    if (A == NULL) {
        fprintf(stderr, "List Error: join(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "List Error: join(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List new_list = newList();

    // Start with List A and append the elements to the new list
    Node* curr_node = A->front;

    while (curr_node != NULL) {
        append(new_list, curr_node->data);
        curr_node = curr_node->next;
    }

    // Move on to List B
    curr_node = B->front;
    while (curr_node != NULL) {
        append(new_list, curr_node->data);
        curr_node = curr_node->next;
    }

    return new_list;
}

// split()
// Removes all elements before (in front of but not equal to) the cursor element
// in L. The cursor element in L is unchanged. Returns a new List consisting of
// all the removed elements. The cursor in the returned list is undefined.
// Pre: length (L)>0, position (L)>=0
List split(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: split(): NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) <= 0) {
        fprintf(stderr, "List Error: split(): empty List\n");
        exit(EXIT_FAILURE);
    }

    if (position(L) < 0) {
        fprintf(stderr, "List Error: split(): undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    List new_list = newList();

    while (L->position != 0) {
        append(new_list, front(L));
        deleteFront(L);
    }

    return new_list;
}