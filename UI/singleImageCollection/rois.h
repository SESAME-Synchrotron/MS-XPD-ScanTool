#ifndef ROIS_H
#define ROIS_H

#pragma once
#include <QString>
#include <array>

struct SingleROI {
    QString x1, y1, x2, y2;
};

struct ROIInfo {
    QString cam;
    std::array<SingleROI, 4> ROI;

    ROIInfo() = default;

    ROIInfo(const QString &base) : cam(base) {
        for (int i = 0; i < 4; ++i) {
            QString idx = QString::number(i+1);
            ROI[i].x1 = base + "ROI" + idx + ":x1";
            ROI[i].y1 = base + "ROI" + idx + ":y1";
            ROI[i].x2 = base + "ROI" + idx + ":x2";
            ROI[i].y2 = base + "ROI" + idx + ":y2";
        }
    }
};

#endif
