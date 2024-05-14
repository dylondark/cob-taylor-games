#ifndef IMGQUEUE_H
#define IMGQUEUE_H
#include <QPixmap>
#include <vector>

using std::vector;

/* imgQueue class
 *
 * This class provides the data structure used for the images in the background animation. At its base it is a linked list, but it is set up sort of as
 * a queue. It is constructed with a vector of QPixmaps (IMGLIST) as the images for use in the queue (can be any size). It then populates the list
 * with random images from the IMGLIST vector. The list can be looped through with next() and specific elements can be accessed with brackets [].
 * Calling shift() takes an image off the front of the queue and inserts a random new one at the end. In the background animation, the contents of the
 * queue are visible in each diagonal "line" of images down the screen, and shift() is called when the last image goes offscreen. This is done seamlessly
 * so that it appears that there is an infinite "line" of random images.
 */
class imgQueue
{
private:
    struct queueNode;
    queueNode* head;
    const int LENGTH; // how many images are in this queue
    const vector<QPixmap> IMGLIST; // to save the input images
    queueNode* nextPtr;
public:
    imgQueue(vector<QPixmap>); // constructor, array of images to use
    ~imgQueue(); // destructor, must delete all elements in queue from memory
    void shift();
    QPixmap operator[](int) const;
    QPixmap next();
    int getLength() const;
    int imageDim = 3840 / 20;
};

#endif // IMGQUEUE_H
