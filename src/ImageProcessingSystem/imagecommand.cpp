#include "imagecommand.h"

ImageCommand::ImageCommand()
{
    firstTime = true;
    imageLeft = NULL;
    imageRight = NULL;
    imageAfter = NULL;
}

QString* ImageCommand::getName()
{
    if(this->name != NULL)
        return name;
}

QImage* ImageCommand::getImageAfter()
{
    if(imageAfter == NULL)
        return NULL;
    return imageAfter;
}
