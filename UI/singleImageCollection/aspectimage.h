#ifndef ASPECTIMAGE_H
#define ASPECTIMAGE_H

#include <QEImage.h>

class AspectImage : public QEImage
{
    Q_OBJECT
public:
    explicit AspectImage(QWidget *parent = nullptr);
    bool hasHeightForWidth() const override { return true; }
    int heightForWidth(int width) const override;
    QSize sizeHint() const override;

    void setAspectRatio(float ratio);
    void setAspectRatio(int w, int h);

private:
    float m_aspectRatio = 1.0f;
};

#endif // ASPECTIMAGE_H
