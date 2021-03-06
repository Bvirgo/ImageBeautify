#include "util.h"
#include <QImageReader>
#include <QImageWriter>
#define _PATH_  ".img.jpg"

QImage Tools::Mat2QImage(const cv::Mat & src)
{
     cv::imwrite(_PATH_, src);
     QImageReader reader(_PATH_);
     reader.setAutoTransform(true);
     return reader.read();
}

cv::Mat Tools::QImage2Mat(const QImage& src)
{
    QImageWriter writer(_PATH_);
    if (writer.write(src))
    {
        return  cv::imread(_PATH_);
    }
    else {
        return cv::Mat();
    }
}
