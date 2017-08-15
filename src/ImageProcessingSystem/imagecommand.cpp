#include "imagecommand.h"

ImageCommand::ImageCommand()
{
    firstTime = true;
}

QString* ImageCommand::getName()
{
    if(this->name != NULL)
        return name;
}
