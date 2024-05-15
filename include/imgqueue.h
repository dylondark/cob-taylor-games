/*
    imgqueue.h

    This file is for the function declarations of image queuing.
*/

#ifndef IMGQUEUE_H
#define IMGQUEUE_H

#include <QPixmap>
#include <vector>

/*
    imgQueue class

    This class provides the data structure used for the images in the background animation. At its base it is a linked list, but it is set up sort of as
    a queue. It is constructed with a vector of QPixmaps (IMGLIST) as the images for use in the queue (can be any size). It then populates the list
    with random images from the IMGLIST vector. The list can be looped through with next() and specific elements can be accessed with brackets [].
    Calling shift() takes an image off the front of the queue and inserts a random new one at the end. In the background animation, the contents of the
    queue are visible in each diagonal "line" of images down the screen, and shift() is called when the last image goes offscreen. This is done seamlessly
    so that it appears that there is an infinite "line" of random images.
 */

class imgQueue
{

private:

    // Struct for the nodes.
    struct queueNode;

    // The current node.
    queueNode* head;

    // Tow many images are in this queue
    const int LENGTH;

    // To save the input images
    const std::vector<QPixmap> IMGLIST;

    // Points to the next node in queue
    queueNode* nextPtr;

public:

    /*
        Constructor, populates the queue linked list with all images in imglist and sets length to length of imglist.

        std::vector<QPixmap> imglist: the list of images to be populated.
    */
    imgQueue(std::vector<QPixmap>);

    /*
        Destructor, must delete all elements in queue from memory.
    */
    ~imgQueue();

    /*
        Removes an element from the front of the queue and adds a random element from imglist to the back of the queue.
    */
    void shift();

    /*
        Will return the image at the element specified.
        This is less efficient than next() but lets you specify the element.

        int index: the element specified.
    */
    QPixmap operator[](int) const;

    /*
        Returns the image that nextPtr is currently pointing to, and then makes nextPtr point to the next image in the queue.
        Provides a faster way of accessing the queue in series.
        This will return the first element (resetting the "series") if a shift has happened or we have looped through the queue already
    */
    QPixmap next();

    /*
        Returns the length of this queue (how many objects are in it).
    */
    int getLength() const;

    // Dimensions for each image to be used in scaling.
    int imageDim = 3840 / 20;

};

#endif // IMGQUEUE_H
