#include "aspectimage.h"

AspectImage::AspectImage(QWidget *parent) : QEImage(parent)
{
    //QSizePolicy sp = sizePolicy();
    QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sp.setHeightForWidth(true);
    setSizePolicy(sp);

}

void AspectImage::setAspectRatio(float ratio)
{
    if (ratio > 0.0f){
        m_aspectRatio = ratio;
        updateGeometry();
    }
}

void AspectImage::setAspectRatio(int w, int h)
{
    if (w > 0 && h > 0) {
        setAspectRatio(static_cast<float>(w) / static_cast<float>(h));
    }
}

int AspectImage::heightForWidth(int width) const
{
    return static_cast<int>(width / m_aspectRatio);
}

QSize AspectImage::sizeHint() const
{
    int w = 400;
    return QSize(w, heightForWidth(w));
}
