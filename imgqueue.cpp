#include "imgqueue.h"

struct imgQueue::queueNode
{
    QPixmap img;
    queueNode* next;
};

// constructor, populates the queue linked list with all images in imglist and sets length to length of imglist
imgQueue::imgQueue(vector<QPixmap> imglist) : LENGTH(imglist.size()), IMGLIST(imglist)
{
    // init rng with current time
    srand(time(0));

    // populate this list randomly
    head = new queueNode{IMGLIST[rand() % LENGTH], nullptr};
    queueNode* nodePtr = head->next;
    for (int x = 0; x < LENGTH - 1; x++)
    {
        nodePtr = new queueNode{IMGLIST[rand() % LENGTH], nullptr};
        nodePtr = nodePtr->next;
    }
}

// destructor, must delete all elements in queue from memory
imgQueue::~imgQueue()
{
    queueNode* nodePtr = head; // for traversing the list, starts at head
    queueNode* nextNode; // to save the next node after nodeptr is deleted

    while (nodePtr != nullptr)
    {
        // save pointer to next node
        nextNode = nodePtr->next;

        // delete current node
        delete nodePtr;

        // go to next node
        nodePtr = nextNode;
    }

    nextPtr = head;
}

// removes an element from the front of the queue and adds a random element from imglist to the back of the queue
void imgQueue::shift()
{
    // remove first element from queue
    // get last and second to last elements
    queueNode* removeNode;
    queueNode* previousNode = head;
    // we can cheat a little bit (and maybe optimize) since we know the length of the list and it never changes
    for (int x = 0; x < LENGTH - 1; x++)
        previousNode = previousNode->next;
    removeNode = previousNode->next;
    // remove from queue
    previousNode->next = nullptr;
    delete removeNode;

    // add new element to back of queue
    srand(time(0)); // init rng with current time
    queueNode* newNode = new queueNode{IMGLIST[rand() % LENGTH], head};
    head = newNode;

    nextPtr = head; // reset nextPtr
}

// will return the image at the element specified
// this is less efficient than next() but lets you specify the element
QPixmap imgQueue::operator[](int index) const
{
    queueNode* nodePtr = head;

    for (int x = 0; x < index; x++)
        nodePtr = nodePtr->next;

    return nodePtr->img;
}

// returns the image that nextPtr is currently pointing to and then makes nextPtr point to the next image in the queue
// provides a faster way of accessing the queue in series
// this will return the first element (resetting the "series") if a shift has happened or we have looped through the queue already
QPixmap imgQueue::next()
{
    QPixmap out = nextPtr->img; // get the image before we change nextPtr
    nextPtr = (nextPtr->next != nullptr) ? nextPtr->next : head; // if we have reached the end then reset
    return out;
}

// returns the length of this queue (how many objects are in it)
int imgQueue::getLength() const
{
    return LENGTH;
}
