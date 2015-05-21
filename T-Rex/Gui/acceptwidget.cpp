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
