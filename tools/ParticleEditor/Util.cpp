#include "Util.h"

Util::Util()
{
}

QColor Util::SColorToQColor (video::SColor c)
{
    return QColor (c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha());
}

video::SColor Util::QColorToSColor (QColor c)
{
    return video::SColor (c.alpha(), c.red(), c.green(), c.blue());
}
