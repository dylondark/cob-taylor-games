/*
    qmlimagepreloader.h

    Class declaration for QMLImagePreloader.
 */

#ifndef QMLIMAGEPRELOADER_H
#define QMLIMAGEPRELOADER_H

#include <QObject>
#include <QQuickItem>

/*
    QMLImagePreloader class

    This class is meant to be a helper class for preloading images in QML. It is a QObject that can be instantiated in QML and used to preload images into memory.
    It does this by converting images into base 64 strings that can be used in the source property of an Image QML element. This solves the issue of images
    being reloaded from disk every single time the source property of an Image QML type is changed.
*/
class QMLImagePreloader : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:

    /*
        Constructor for QMLImagePreloader
    */
    explicit QMLImagePreloader();

    /*
        Add an image to the list of preloaded images.
    */
    Q_INVOKABLE void addImage(const QString& path);

    /*
        Retrieve a preloaded image as a base 64 encoded URL.
    */
    Q_INVOKABLE QString getImage(const QString& path);

private:
    // Stores the data as key value pairs with the key being the path and the value being the base 64 encoded image.
    std::map<QString, QString> data;
};

#endif // QMLIMAGEPRELOADER_H
