#include <QtWidgets>

#include "acceptwidget.h"
#include "dragwidget.h"

//! [0]
AcceptWidget::AcceptWidget(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

}
//! [0]

void AcceptWidget::dragEnterEvent(QDragEnterEvent *event)
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

void AcceptWidget::dragMoveEvent(QDragMoveEvent *event)
{

}

void AcceptWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-acceptdata") && event->source() != this) {
        QByteArray itemData = event->mimeData()->data("application/x-acceptdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon1 = new QLabel(this);
        QLabel *newIcon2 = new QLabel(this);



        newIcon1->setFrameStyle(3);
        newIcon2->setFrameStyle(3);
        newIcon1->setFixedSize(100,30);
        newIcon2->setFixedSize(100,30);


        newIcon1->move(mapToGlobal(rect().topLeft()));
        newIcon2->move(mapToGlobal(rect().topLeft() + QPoint(110,0)));
        newIcon1->show();
        newIcon2->show();
        newIcon1->setAttribute(Qt::WA_DeleteOnClose);
        newIcon2->setAttribute(Qt::WA_DeleteOnClose);


        //Treba dodati posebno ponasanje za svaku sliku

        //takodje ako se nalazimo unutar neke labele, treba u njoj postavljati

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
void AcceptWidget::mousePressEvent(QMouseEvent *event)
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
