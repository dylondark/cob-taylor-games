#ifndef IMGQUEUE_H
#define IMGQUEUE_H
#include <cstdlib>
#include <QPixmap>
#include <vector>

using std::vector;

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
    bool isRand() const;
};

#endif // IMGQUEUE_H
