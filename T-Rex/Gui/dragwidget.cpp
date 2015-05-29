#include <QtWidgets>

#include "dragwidget.h"
#include "guibuilder.h"

#include <QVBoxLayout>

//! [0]
DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(75, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    //setAcceptDrops(true);

    //staviti scroll?!

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->setAlignment(Qt::AlignCenter);

    layout->addWidget(makeToolIcon(":/toolBox/images/diag1.ico", "slovo", "slovo",1, ""));
    layout->addWidget(makeToolIcon(":/toolBox/images/diag2.ico", "Nadovezi", "konkatenacija",2,"."));
    layout->addWidget(makeToolIcon(":/toolBox/images/diag3.ico", "ili", "disjunkcija",3,"|"));
    layout->addWidget(makeToolIcon(":/toolBox/images/diag4.ico", "Jednom ili nijednom", "jednom ili ni jednom prikazi",4,"?"));
    layout->addWidget(makeToolIcon(":/toolBox/images/diag5.ico", "jedan ili vise", "jedan ili vise puta",5,"+"));
    layout->addWidget(makeToolIcon(":/toolBox/images/diag6.ico", "Nula ili vise", "nula ili vise puta prikazi",6,"*"));
    layout->addWidget(makeToolIcon(":/toolBox/images/diag7.ico", "Tacno toliko", "Tacno toliko puta",7,"{a,b}"));
    layout->addWidget(makeToolIcon(":/toolBox/images/diag8.ico", "jedno od", "Karakterska klasa",8,"[]"));

}
//! [0]

QLabel* DragWidget::makeToolIcon(const QString& path, const QString& write, const QString& toolTip, int i, const QString& text){

    QImage *image = new QImage(path);

    QPainter* painter = new QPainter(image);
    painter->setPen(Qt::blue);
    painter->setFont(QFont("Arial", 35));
    painter->drawText(image->rect(), Qt::AlignBaseline, write);

    imageLabels[i] = new QLabel();
    imageLabels[i]->setText(text);
    imageLabels[i]->setPixmap(QPixmap::fromImage(*image));
    imageLabels[i]->setAlignment(Qt::AlignCenter);
    imageLabels[i]->setToolTip(toolTip);
    imageLabels[i]->setAttribute(Qt::WA_DeleteOnClose);
    imageLabels[i]->setScaledContents(true);
    imageLabels[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    imageLabels[i]->setFixedSize(90, 70);

    return imageLabels[i];
}

QString DragWidget::getLabelName(int i) const
{
    return imageLabels[i]->text();
}

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
    if (event->mimeData()->hasFormat("application/x-acceptdata1")) {
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
    int i,j,k,pom;
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();
    qDebug() << event->pos();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
//! [1]

//! [2]
    QMimeData *mimeData = new QMimeData;
    QString s;
    //s. childAt(event->pos());

    j = 10;
    k = 80;
    for(i = 1; i <= 8; i++)
    {
        if((event->pos().ry() >= j) && (event->pos().ry() <= k))
            pom = i;
        j+=75;
        k+=75;

    }
    s.append(QString::number(pom));
    qDebug() << s;
    mimeData->setData(s , itemData);
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
