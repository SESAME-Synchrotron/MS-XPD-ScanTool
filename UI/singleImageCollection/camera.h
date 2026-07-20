#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <QString>

struct CameraInfo {
    QString prefix;
    QString deliveredFrameCount;
    QString acquireTime;
    QString pixelFormatRBV;
    QString pixelFormat;
    QString acquire;
    QString acquireBusy;
    QString image;
    QString sizeX;
    QString sizeY;

    CameraInfo() = default;

    CameraInfo(const QString &base)
        : prefix(base),
          deliveredFrameCount(base + ":ArrayCounter_RBV"),
          acquireTime(base + ":AcquireTime"),
          pixelFormatRBV(base + ":PixelFormat_RBV"),
          pixelFormat(base + ":PixelFormat"),
          acquire(base + ":Acquire"),
          acquireBusy(base + ":AcquireBusy"),
          image(base.left(base.indexOf(':')) + ":Trans1:image1:ArrayData"),
          sizeX(base + ":SizeX"),
          sizeY(base + ":SizeY")
    {}
};

#endif // CAMERA_H
