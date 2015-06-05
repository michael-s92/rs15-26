#include <math.h>
#include "graphview.h"
#include <iostream>

#include <iostream>
using namespace std;

//nesto sam ubacio

GraphView::GraphView()
 :QGraphicsScene()
{

}

GraphView::GraphView(const QString& filename, QWidget* parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    nodeColor = Qt::green;
    renderGraph(filename);
}


GraphView::GraphView(graph_t* graph, QWidget* parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    nodeColor = Qt::green;
    renderGraph(graph);
}

GraphView::~GraphView()
{
    clearGraph();
}


QPointF GraphView::transliraj(const point& p, bool up_down) const
{
    if (up_down)
        return QPointF(p.x, graphRect.height() - p.y);
    else
        return QPointF(p.x, -p.y);
}

QPointF GraphView::transliraj(const pointf& p, bool up_down) const
{
    if (up_down)
        return QPointF(p.x, graphRect.height() - p.y);
    else
        return QPointF(p.x, -p.y);
}


QPainterPath
GraphView::makeBezier(const bezier& bezier) const
{
    QPainterPath path;
    path.moveTo(transliraj(bezier.list[0]));
    for (int i = 1; i < bezier.size - 1; i += 3)
    path.cubicTo(transliraj(bezier.list[i]), transliraj(bezier.list[i+1]), transliraj(bezier.list[i+2]));
    return path;
}


void
GraphView::drawEdgeDetails(const QLineF& line, const textlabel_t* textlabel, const QColor& color, QPainter* painter) const
{
    QLineF n(line.normalVector());

    QPointF o(n.dx() / 3.0, n.dy() / 3.0);

    QPolygonF polygon;
    polygon.append(line.p1() + o);
    polygon.append(line.p2());
    polygon.append(line.p1() - o);

    QPen pen(color);
    pen.setWidthF(1.0);
    painter->setPen(pen);

    QBrush brush(color);
    painter->setBrush(brush);

    painter->drawPolygon(polygon);

    painter->setPen(textlabel->fontcolor);

    QFont font(textlabel->fontname, textlabel->fontsize);
    font.setPixelSize(textlabel->fontsize);
    painter->setFont(font);

    QString text(QString::fromUtf8(textlabel->text));
    QFontMetricsF fm(painter->fontMetrics());
    QRectF rect(fm.boundingRect(text));
    rect.moveCenter(transliraj(textlabel->pos, true));
    painter->drawText(rect.adjusted(-1, -1, +1, +1), Qt::AlignCenter, text);

}


void
GraphView::renderGraph(const QString& filename)
{
    FILE* fp = fopen(filename.toUtf8().constData(), "r");
    if (fp)
    {
    GVC_t* gvc = gvContext();
    graph_t* graph = agread(fp,0);
    gvLayout(gvc, graph, "dot");
    renderGraph(graph);
    gvFreeLayout(gvc, graph);
    agclose(graph);
    gvFreeContext(gvc);
    fclose(fp);
    }
    else
     std::cerr << "Greska prilikom otvaranja datoteke " << filename.toStdString() << std::endl;
}


void GraphView::make_ellipse_helper(node_t *node, QPainterPath &path) const {
    const polygon_t *const poly = static_cast<polygon_t *>(ND_shape_info(node));

    const int sides = poly->sides;
    const pointf* vertices = poly->vertices;

    QPolygonF polygon;
    for (int side = 0; side < sides; side++) {
        polygon.append(transliraj(vertices[side], false));
    }

    QRectF ellipse_bounds(polygon[0], polygon[1]);

    for (int i = 0; i < poly->peripheries; ++i) {
        path.addEllipse(ellipse_bounds.adjusted(-2 * i, 2 * i, 2 * i, -2 * i));
    }
}


QPainterPath GraphView::make_shape(node_t *node) const {
    QPainterPath path;

    const QString name = QString::fromUtf8(ND_shape(node)->name);


    if(name=="doublecircle" || name == "circle" || name == "point" || name == "Mcircle") {
        make_ellipse_helper(node, path);
    } else if(name == "none") {

    }

    return path;
}


void
GraphView::drawNodeDetails(const textlabel_t* textlabel, QPainter* painter) const
{
    painter->setPen(Qt::black);

    QFont font(textlabel->fontname, textlabel->fontsize);
    font.setPixelSize(textlabel->fontsize);
    painter->setFont(font);

    QString text(QString::fromUtf8(textlabel->text));
    QFontMetricsF fm(painter->fontMetrics());
    QRectF rect(fm.boundingRect(text));
    rect.moveCenter(QPointF(0,0));
    painter->drawText(rect,Qt::AlignCenter, text);
}


void
GraphView::clearGraph()
{
    QList<QGraphicsItem*> items(this->items());

    while (!items.isEmpty())
    delete items.takeFirst();
}


void
GraphView::renderGraph(graph_t* graph)
{
    clearGraph();

    graphRect = QRectF(GD_bb(graph).LL.x, GD_bb(graph).LL.y, GD_bb(graph).UR.x, GD_bb(graph).UR.y);
    setSceneRect(graphRect);

    setBackgroundBrush(Qt::white);

    for (node_t* node = agfstnode(graph); node != NULL; node = agnxtnode(graph, node))
        {
        QPicture picture;
        QPainter painter;

        painter.begin(&picture);
        drawNodeDetails(ND_label(node), &painter);
        painter.end();

        QString tekst(ND_label(node)->text);
        GraphNode * item;
        if (tekst=="")
            item = new GraphNode(-1, make_shape(node), picture);
        else
            item = new GraphNode(QString(ND_label(node)->text).toInt(), make_shape(node), picture);

        item->setPos(transliraj(ND_coord(node)));

        QPen pen(Qt::black);
        pen.setWidthF(1.0);
        item->setPen(pen);

        cout << nodeColor.name().toStdString() << endl;
        QBrush brush(nodeColor);
        item->setBrush(brush);

        addItem(item);


        for (edge_t* edge = agfstout(graph, node); edge != NULL; edge = agnxtout(graph, edge))
        {
            const splines* spl = ED_spl(edge);
            if (spl == NULL)
            continue;

            QPicture picture1;
            QPainter painter1;

            if (ED_label(edge)==0)
                continue;
            painter1.begin(&picture1);

            for (int i = 0; i < spl->size; ++i)
            {
            const bezier& bz = spl->list[i];

            QColor color(Qt::black);

            QPainterPath path(makeBezier(bz));

            if (bz.sflag)
                drawEdgeDetails(QLineF(transliraj(bz.list[0]), transliraj(bz.sp)),ED_label(edge),color, &painter1);
            if (bz.eflag)
                drawEdgeDetails(QLineF(transliraj(bz.list[bz.size-1]), transliraj(bz.ep)),ED_label(edge), color, &painter1);
             painter1.end();

            QString text1(ND_label(node)->text);
            QString text2(ND_label(edge->node)->text);
            int state1;
            int state2;
            if (text1 == "")
              state1 = -1;
            else
              state1 = text1.toInt();
            if (text2 == "")
                state2 = -1;
            else
               state2 = text2.toInt();
            char c = ED_label(edge)->text[0];

            GraphEdge* item = new GraphEdge(state1,state2,c,path, picture1);

            QPen pen(color);
            pen.setStyle(Qt::SolidLine);
            pen.setWidthF(1.0);
            item->setPen(pen);

            item->setZValue(-1.0);

            addItem(item);
            }
        }
    }
}

void GraphView::setNodeColor(QColor color)
{
   nodeColor = color;
   QListIterator<QGraphicsItem *> i(items());
   while (i.hasNext())
   {
       QGraphicsItem* item = i.next();
       GraphItem * j = (GraphItem*)(item);
       if (j->ind()==0)
       {
          j->setBrush(QBrush(nodeColor));
       }
   }
}



GraphItem::GraphItem(const QPainterPath& path, const QPicture& picture)
    : QGraphicsPathItem(path),
      picture(picture)
{
}



GraphNode::GraphNode(int state, const QPainterPath& path, const QPicture& picture)
    : GraphItem(path,picture),
      state(state)
{
}

int GraphNode::ind()
{
    return 0;
}


void
GraphItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    painter->save();
    QGraphicsPathItem::paint(painter, option, widget);
    painter->restore();
    picture.play(painter);
}


GraphEdge::GraphEdge(int state1, int state2, char c, const QPainterPath& path, const QPicture& picture)
    : GraphItem(path,picture),
      state1(state1),
      state2(state2),
      c(c)
{
}


QRectF
GraphEdge::boundingRect() const
{
    return QGraphicsPathItem::boundingRect().united(picture.boundingRect());
}

int GraphEdge::ind()
{
    return 1;
}

