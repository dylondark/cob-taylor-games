/*
    qmlimagepreloader.cpp

    Class implementation for QMLImagePreloader.
*/

#include "qmlimagepreloader.h"
#include <QImage>
#include <QBuffer>
#include "cliparser.h"

/*
    Constructor for QMLImagePreloader
*/
QMLImagePreloader::QMLImagePreloader() {}

/*
    Add an image to the list of preloaded images.
    NOTE: Do not include filepath in front of the path when calling this function!
    This function automatically prepends filepath due to issues using filepath when calling this in QML.
*/
void QMLImagePreloader::addImage(const QString& path)
{
    // Load the image from the path
    QImage image(CliParser::getPath() + path);

    // Convert the image to a base 64 encoded string
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    QString base64 = QString::fromLatin1(byteArray.toBase64().data());
    base64.prepend("data:image/png;base64,");

    // Store the base 64 encoded image in the data map
    data[path] = base64;
}

/*
    Retrieve a preloaded image as a base 64 encoded URL.
    NOTE: Do not include filepath in front of the path when calling this function!
*/
QString QMLImagePreloader::getImage(const QString& path)
{
    // Retrieve the base 64 encoded image from the data map
    return data[path];
}
