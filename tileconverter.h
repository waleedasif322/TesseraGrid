#ifndef TILECONVERTER_H
#define TILECONVERTER_H

#include <QtGui>
#include <QtCore>


class TileConverter

{

public:
    TileConverter();

    void reset();
    void setOriginalImage(QImage&);
    void setImage(QImage&);
    void ScanImage	();
    void computeDiff();
    const QImage& originalImage() const;
    const QImage &tiledImage() const;
    void getAvgTiles();
    void drawImage();
    QImage m_bestTile;
    QImage m_origImage;
    QImage m_outImage;
    QImage m_scaledInput;
    QList<QRgb> m_avgTiles;
    QList<QRgb> m_ImgRgb;
    QList<QImage> tilesList;
    QList<QImage> m_bestTiles;
    QList<int> usedTiles;
    QPainter painter;

};

#endif // TILECONVERTER_H
