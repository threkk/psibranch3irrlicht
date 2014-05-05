#ifndef UTIL_H
#define UTIL_H

#include <irrlicht.h>
#include <QMainWindow>

using namespace irr;

class Util
{
public:
    Util();
    static QColor SColorToQColor (video::SColor c);
    static video::SColor QColorToSColor (QColor c);
};

#endif // UTIL_H
