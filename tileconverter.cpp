#include "tileconverter.h"

using namespace std;

TileConverter::TileConverter()
{
    reset();
}

void
TileConverter::reset()      //initialize with every new image loaded
{
    m_bestTile = QImage();
    m_origImage = QImage();
    m_outImage = QImage();
    m_scaledInput = QImage();
    m_avgTiles = QList<QRgb>();
    tilesList = QList<QImage>();
    m_bestTiles = QList<QImage>();
    m_ImgRgb = QList<QRgb>();
    usedTiles = QList<int>();
}

void
TileConverter::setOriginalImage( QImage &image)
{
    m_origImage = image;
}

void
TileConverter::setImage( QImage &image)
{
    m_outImage = image;
}

const
QImage& TileConverter::originalImage() const
{
    return m_origImage;
}

const
QImage& TileConverter::tiledImage() const // return our final image
{
   return m_outImage;
}

/*
 *Important note!!!
 *Change directory in following function to get a working project build!!!
 */

void
TileConverter::getAvgTiles()
{
    QDir imagesDirectory("/home/waleed/practice/P1/Project1_6/tools"); // change this folder!!!
    QDirIterator iterator(imagesDirectory, QDirIterator::NoIteratorFlags);
    while (iterator.hasNext())
    {
        iterator.next();    // goes to next image in directory
        QString imageName = iterator.filePath();
        if(iterator.fileName().contains("A-.375-VG")) // only reading 3/8" VG tiles
        {
            QImage tiles(imageName);
            QImage newTile = tiles.scaled(1,1, Qt::IgnoreAspectRatio, // get avg value of tile
                                          Qt::SmoothTransformation);
            QRgb tilePixel = newTile.pixel(0,0);
            tilesList << tiles;             // store tiles in list
            m_avgTiles << tilePixel;
            usedTiles << 0;
        }
    }
}

void
TileConverter::ScanImage()
{
/*
 *
 * We want to scan every pixel in the image and retrieve the RGB values.
 * To simplify the process, we use scaled function to allow us to get
 * 1 pixel from each desired subregion. Since our customer wants
 * a 70" mosaic width, with 3/8" tiles, we can fit 187 tiles in that width
 * this means we can scale the image down to 187 by width and keep its aspect ratio
 * and retrieve our average values from the scaled down image.
 *
 *
 */
    double aspect = (double)m_origImage.height() / m_origImage.width();
    int imageWidth = 186;
    int imageHeight = imageWidth * aspect;
    m_scaledInput = m_origImage.scaled(imageWidth,imageHeight,
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation);
    int scaledWidth = m_scaledInput.width();
    int scaledHeight = m_scaledInput.height();
    qDebug () << scaledHeight << "scaled";
    QRgb ImgPixel;
    for (int y = 0; y < scaledHeight; y++)
    {
        for(int x = 0; x < scaledWidth; x++)
        {
             ImgPixel = m_scaledInput.pixel(x,y);
             m_ImgRgb << ImgPixel;
        }
    }
}

void
TileConverter::computeDiff()
/*
 *
 * In this function, we want to compare the average values of the all the 3/8" tiles
 * and compare it with all the subregions of our input image.
 * So to find the best matching tile, we find the difference of RGB values.
 * The smaller the difference, the better the match. To avoid negative values,
 * we square the integer values.
 * Before we start iterating through the database of tiles, we intialize a variable
 * to be the standard comaprison factor. This number should be bigger than any possible
 * RGB difference squared. After that, we set that variable to our RGB difference squared
 * variable and every time we see a better match, we set our best match variabel to the
 * index of the tiles database. This index will return us the value of the best tile found
 * after we have iterated through the database and then we can store that tile in our
 * final list of tiles to be drawn onto the mosaic.
 *
 *
 */
{
    getAvgTiles();
    ScanImage();
    int size1 = m_ImgRgb.size(); // input image avg vector 187 X ratio
    int size2 = m_avgTiles.size(); // tile images avg vector should be size 86 since we have 86 3/8" VG
    int testRed; int testGreen; int testBlue;
    int testTotal = 0;
    for (int x = 0; x < size1; x++) // going through vector of QRGB of scaled input image
    {
         int difference = 10000;
         int counter = 0;
        for (int y = 0; y < size2; y++) // going through vector of tiles i.e. 86
        {
            //get the squared difference, find smallest diff
            testRed = pow(qRed(m_avgTiles[y]) - (qRed(m_ImgRgb[x])), 2);
            testGreen = pow(qGreen(m_avgTiles[y]) - (qGreen(m_ImgRgb[x])), 2);
            testBlue = pow(qBlue(m_avgTiles[y]) - (qBlue(m_ImgRgb[x])), 2);
            testTotal = testRed + testBlue + testGreen;

            if(testTotal < difference)
            {
                difference = testTotal;
                counter = y; // set current index of database of tiles if best match found
            }
        }
        m_bestTiles << (tilesList[counter]); // tilesList: this is vector of QImages, best match in tiles DB is appended to DB of bestTiles
        usedTiles[counter]++;
    }
}

void
TileConverter::drawImage()
/*
 *
 * In this function, we want to calculate the final image width and height
 * We do this by seeing what is the max amount of pixels we can use.
 * We want a limit of 4000 pixels.
 * So we calculate the size of the tiles we will paint, given that we have 187
 * subregions to fill.
 * This gives us a tile size of 21 (width)
 * The rest of the function iterates through the calculated output image size
 * and skips by regions of 21 pixels. It then inserts the tile from the list of tiles.
 *
 */
{
    computeDiff();
    int tileSize = 21;
    int imageWidth = m_scaledInput.width() * tileSize;
    int imageHeight = m_scaledInput.height() * tileSize;
    m_outImage = QImage(imageWidth, imageHeight, QImage::Format_RGB32);
    m_outImage.fill(Qt::white);
    painter.begin(&m_outImage);
    int count = 0;
    for(int row = 0; row < m_outImage.height(); row+=tileSize)
    {
        for(int col = 0; col < m_outImage.width(); col+=tileSize)
        {
            QImage tileImage(m_bestTiles[count]);
            QImage scaledTiles;
            scaledTiles = tileImage.scaled(tileSize, tileSize,
                                           Qt::IgnoreAspectRatio,
                                           Qt::SmoothTransformation);
            painter.drawImage(col, row, scaledTiles);
            count++;
        }
    }
    painter.end();
}
