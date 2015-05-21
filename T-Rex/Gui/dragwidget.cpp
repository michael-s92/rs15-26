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

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag1.ico", "slovo", 40, false);
    tmp->setText("Slovo");
    layout->addWidget(tmp);

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag2.ico", "konkatenacija", 40, false);
    tmp->setText("Nadovezi");
    layout->addWidget(tmp);

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag3.ico", "disjunkcija", 40, false);
    tmp->setText("ili");
    layout->addWidget(tmp);

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag4.ico", "jednom ili ni jednom prikazi", 40, false);
    tmp->setText("Jednom ili nijednom");
    layout->addWidget(tmp);

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag5.ico", "jedan ili vise puta", 40, false);
    tmp->setText("Jedan ili vise");
    layout->addWidget(tmp);

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag6.ico", "nula ili vise puta prikazi", 40, false);
    tmp->setText("Nula ili vise");
    layout->addWidget(tmp);

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag7.ico", "Tacno toliko", 40, false);
    tmp->setText("Tacno toliko puta");
    layout->addWidget(tmp);

    tmp = GuiBuilder::createIconButton(":/toolBox/images/diag8.ico", "Karakterna klasa", 40, false);
    tmp->setText("Jedno od");
    layout->addWidget(tmp);

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
