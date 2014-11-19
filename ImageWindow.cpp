#include "ImageWindow.h"


ImageWindow::ImageWindow(/*QWidget *parent, Qt::WindowFlags f) : QWidget(parent,f*/){

    m_imageHolder = new QLabel("Load an image to start");
    m_imageHolder->setAlignment(Qt::AlignCenter);
    m_imageHolder->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_imageHolder->setScaledContents(false);//false
    m_imageHolder->setMinimumSize(200,200);
    m_imageHolder->setBackgroundRole(QPalette::Base);//new
    //QVBoxLayout *vbox1 = new QVBoxLayout;
   // vbox1->addWidget(m_imageHolder);
    //setLayout(vbox1);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(m_imageHolder);
    scrollArea->setWidgetResizable(true);
    QScrollBar *H = new QScrollBar;
    QScrollBar *W = new QScrollBar;
    scrollArea->setHorizontalScrollBar(W);
    scrollArea->setVerticalScrollBar(H);
    scrollArea->isMaximized();
    setCentralWidget(scrollArea);
}

void
ImageWindow::setImage(const QImage &image)
{
    m_pixmap = QPixmap::fromImage(image);
    updatePixmap();
}



void
ImageWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updatePixmap();
}



void
ImageWindow::updatePixmap()
{
    // error checking
    if(m_pixmap.isNull())
        return;

    // resize content of m_imageHolder
    int w = m_imageHolder->width();
    int h = m_imageHolder->height();
    if(w < h)
        m_imageHolder->setPixmap(m_pixmap.scaledToWidth(w));
    else	m_imageHolder->setPixmap(m_pixmap.scaledToHeight(h));
}











