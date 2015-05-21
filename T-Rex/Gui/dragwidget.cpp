#include <QtWidgets>

#include "dragwidget.h"
#include "guibuilder.h"

#include <QVBoxLayout>

//! [0]
DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(100, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    //setAcceptDrops(true);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *tmp;

    QImage image(":/toolBox/images/diag1.ico");
    QPainter* painter1 = new QPainter(&image);
    painter1->setPen(Qt::blue);
    painter1->setFont(QFont("Arial", 30));
    painter1->drawText(image.rect(), Qt::AlignBaseline, "slovo");

    QLabel* imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setToolTip("slovo");
    layout->addWidget(imageLabel);

    QImage image1(":/toolBox/images/diag2.ico");
    QPainter* painter2 = new QPainter(&image1);
    painter2->setPen(Qt::blue);
    painter2->setFont(QFont("Arial", 30));
    painter2->drawText(image.rect(), Qt::AlignBaseline, "Nadovezi");

    QLabel* imageLabel1 = new QLabel();
    imageLabel1->setPixmap(QPixmap::fromImage(image1));
    imageLabel1->setAlignment(Qt::AlignCenter);
    imageLabel1->setToolTip("konkatenacija");
    layout->addWidget(imageLabel1);

    QImage image2(":/toolBox/images/diag3.ico");
    QPainter* painter3 = new QPainter(&image2);
    painter3->setPen(Qt::blue);
    painter3->setFont(QFont("Arial", 30));
    painter3->drawText(image.rect(), Qt::AlignBaseline, "ili");

    QLabel* imageLabel2 = new QLabel();
    imageLabel2->setPixmap(QPixmap::fromImage(image2));
    imageLabel2->setAlignment(Qt::AlignCenter);
    imageLabel2->setToolTip("disjunkcija");
    layout->addWidget(imageLabel2);

    QImage image3(":/toolBox/images/diag4.ico");
    QPainter* painter4 = new QPainter(&image3);
    painter4->setPen(Qt::blue);
    painter4->setFont(QFont("Arial", 30));
    painter4->drawText(image.rect(), Qt::AlignBaseline, "Jednom ili nijednom");

    QLabel* imageLabel3 = new QLabel();
    imageLabel3->setPixmap(QPixmap::fromImage(image3));
    imageLabel3->setAlignment(Qt::AlignCenter);
    imageLabel3->setToolTip("jednom ili ni jednom prikazi");
    layout->addWidget(imageLabel3);

    QImage image4(":/toolBox/images/diag5.ico");
    QPainter* painter5 = new QPainter(&image4);
    painter5->setPen(Qt::blue);
    painter5->setFont(QFont("Arial", 30));
    painter5->drawText(image.rect(), Qt::AlignBaseline, "jedan ili vise");

    QLabel* imageLabel4 = new QLabel();
    imageLabel4->setPixmap(QPixmap::fromImage(image4));
    imageLabel4->setAlignment(Qt::AlignCenter);
    imageLabel4->setToolTip("jedan ili vise puta");
    layout->addWidget(imageLabel4);

    QImage image6(":/toolBox/images/diag6.ico");
    QPainter* painter6 = new QPainter(&image6);
    painter6->setPen(Qt::blue);
    painter6->setFont(QFont("Arial", 30));
    painter6->drawText(image.rect(), Qt::AlignBaseline, "Nula ili vise");

    QLabel* imageLabel6 = new QLabel();
    imageLabel6->setPixmap(QPixmap::fromImage(image6));
    imageLabel6->setAlignment(Qt::AlignCenter);
    imageLabel6->setToolTip("nula ili vise puta prikazi");
    layout->addWidget(imageLabel6);

    QImage image7(":/toolBox/images/diag7.ico");
    QPainter* painter7 = new QPainter(&image7);
    painter7->setPen(Qt::blue);
    painter7->setFont(QFont("Arial", 30));
    painter7->drawText(image.rect(), Qt::AlignBaseline, "Tacno toliko puta");

    QLabel* imageLabel7 = new QLabel();
    imageLabel7->setPixmap(QPixmap::fromImage(image7));
    imageLabel7->setAlignment(Qt::AlignCenter);
    imageLabel7->setToolTip("Tacno toliko");
    layout->addWidget(imageLabel7);

    QImage image8(":/toolBox/images/diag8.ico");
    QPainter* painter8 = new QPainter(&image8);
    painter8->setPen(Qt::blue);
    painter8->setFont(QFont("Arial", 30));
    painter8->drawText(image.rect(), Qt::AlignBaseline, "jedno od");

    QLabel* imageLabel8 = new QLabel();
    imageLabel8->setPixmap(QPixmap::fromImage(image8));
    imageLabel8->setAlignment(Qt::AlignCenter);
    imageLabel8->setToolTip("Karakterska klasa");
    layout->addWidget(imageLabel8);



    /*
    QLabel *boatIcon = new QLabel(this);
    boatIcon->setPixmap(QPixmap(":images/DragDrop/dino3.png"));
    boatIcon->move(10, 10);
    boatIcon->show();
    boatIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *carIcon = new QLabel(this);
    carIcon->setPixmap(QPixmap(":images/DragDrop/dino4.png"));
    carIcon->move(100, 10);
    carIcon->show();
    carIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *houseIcon = new QLabel(this);
    houseIcon->setPixmap(QPixmap(":images/DragDrop/dino5.png"));
    houseIcon->move(10, 80);
    houseIcon->show();
    houseIcon->setAttribute(Qt::WA_DeleteOnClose);
    */
}
//! [0]

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-acceptdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-acceptdata")) {
        if (event->source() == this) {
            //event->setDropAction(Qt::MoveAction);
            //event->accept();
            event->ignore();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-acceptdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-acceptdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *boatIcon = new QLabel(this);
        boatIcon->setPixmap(QPixmap(":images/DragDrop/dino3.png"));
        boatIcon->move(event->pos() - offset);
        boatIcon->show();
        boatIcon->setAttribute(Qt::WA_DeleteOnClose);

       // QLabel *newIcon = new QLabel(this);
       // newIcon->setPixmap(pixmap);
       // newIcon->move(event->pos() - offset);
       // newIcon->show();
       // newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            //event->setDropAction(Qt::MoveAction);
            //event->accept();
            event->ignore();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

//! [1]
void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
//! [1]

//! [2]
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-acceptdata", itemData);
//! [2]

//! [3]
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());
//! [3]

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
