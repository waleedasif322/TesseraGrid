#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QtWidgets>
class QScrollArea;
class QScrollBar;

class ImageWindow : public QMainWindow {
    Q_OBJECT
public:
    ImageWindow(/*QWidget *parent=0, Qt::WindowFlags f=0*/);

    void	setImage	(const QImage &image);
    QScrollBar *H;
    QScrollBar *W;

protected:
    void	resizeEvent	(QResizeEvent *event);
    void	updatePixmap	();

    QPixmap			m_pixmap;
    QLabel		       *m_imageHolder;

private:

};


#endif // IMAGEWINDOW_H
