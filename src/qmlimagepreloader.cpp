/*
    qmlimagepreloader.cpp

    Class implementation for QMLImagePreloader.
*/

#include "qmlimagepreloader.h"
#include <QImage>
#include <QBuffer>

/*
    Constructor for QMLImagePreloader
*/
QMLImagePreloader::QMLImagePreloader() {}

/*
    Add an image to the list of preloaded images.
*/
void QMLImagePreloader::addImage(const QString& path)
{
    // Load the image from the path
    QImage image(path);

    // Convert the image to a base 64 encoded string
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    QString base64 = QString::fromLatin1(byteArray.toBase64().data());

    // Store the base 64 encoded image in the data map
    data[path] = base64;
}

/*
    Retrieve a preloaded image as a base 64 encoded URL.
*/
QString QMLImagePreloader::getImage(const QString& path)
{
    // Retrieve the base 64 encoded image from the data map
    return data[path];
}
