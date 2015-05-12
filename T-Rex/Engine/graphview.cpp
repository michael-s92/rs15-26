#include <math.h>
#include "graphview.h"
#include <iostream>

GraphView::GraphView(const QString& filename, QWidget* parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    renderGraph(filename);
}


GraphView::GraphView(graph_t* graph, QWidget* parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    renderGraph(graph);
}

GraphView::~GraphView()
{
}


QPointF
GraphView::gToQ(const point& p, bool upside_down) const
{
    return upside_down ? QPointF(p.x, graphRect.height() - p.y) : QPointF(p.x, -p.y);
}

QPointF
GraphView::gToQ(const pointf& p, bool upside_down) const
{
    return upside_down ? QPointF(p.x, graphRect.height() - p.y) : QPointF(p.x, -p.y);
}


QString
GraphView::aggetToQString(void* obj, const char* name, const QString& fallback) const
{
    const char* tmp = agget(obj, const_cast<char*>(name));
    if (tmp == NULL || strlen(tmp) == 0)
    return fallback;
    return QString::fromUtf8(tmp);
}

QPainterPath
GraphView::makeBezier(const bezier& bezier) const
{
    QPainterPath path;
    path.moveTo(gToQ(bezier.list[0]));
    for (int i = 1; i < bezier.size - 1; i += 3)
    path.cubicTo(gToQ(bezier.list[i]), gToQ(bezier.list[i+1]), gToQ(bezier.list[i+2]));
    return path;
}


void
GraphView::drawArrow(const QLineF& line, const QColor& color, QPainter* painter) const
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
}


void
GraphView::renderGraph(const QString& filename)
{
    FILE* fp = fopen(filename.toUtf8().constData(), "r");
    if (fp)
    {
    GVC_t* gvc = gvContext();
    if (gvc != NULL)
    {
        graph_t* graph = agread(fp,0);
        if (graph != NULL)
        {
        if (gvLayout(gvc, graph, "dot") == 0)
        {
            renderGraph(graph);

            gvFreeLayout(gvc, graph);
        }
        else
        {
            qCritical("gvLayout() failed");
        }

        agclose(graph);
        }
        else
        {
        qCritical("agread() failed");
        }

        gvFreeContext(gvc);
    }
    else
    {
        qCritical("gvContext() failed");
    }

    fclose(fp);
    }
    else
    {
    qCritical("failed to open %s", filename.toUtf8().constData());
    }
}


QPolygonF GraphView::makeShapeHelper(node_t* node) const
{
    const polygon_t* poly = (polygon_t*) ND_shape_info(node);

    if (poly->peripheries != 1)
    {
  //  qWarning("unsupported number of peripheries %d", poly->peripheries);
    }

    const int sides = poly->sides;
    const pointf* vertices = poly->vertices;

    QPolygonF polygon;
    for (int side = 0; side < sides; side++)
    polygon.append(gToQ(vertices[side], false));
    return polygon;
}


QPainterPath GraphView::makeShape(node_t* node) const
{
    QPainterPath path;

    const char* name =ND_shape(node)->name;
    //std::cout << name << std::endl;

    if ((strcmp(name, "rectangle") == 0) ||
    (strcmp(name, "box") == 0) ||
    (strcmp(name, "hexagon") == 0) ||
    (strcmp(name, "polygon") == 0) ||
    (strcmp(name, "diamond") == 0))
    {
    QPolygonF polygon = makeShapeHelper(node);
    polygon.append(polygon[0]);
    path.addPolygon(polygon);
    }
    else if ((strcmp(name, "ellipse") == 0) ||
             (strcmp(name, "doublecircle") == 0) ||
         (strcmp(name, "circle") == 0))
    {
    QPolygonF polygon = makeShapeHelper(node);
    path.addEllipse(QRectF(polygon[0], polygon[1]));
    }
    else if(strcmp(name,"none")==0) {

        }
    else
    {
    qWarning("unsupported shape %s", name);
    }

    return path;
}


void
GraphView::drawLabel(const textlabel_t* textlabel, QPainter* painter) const
{
    painter->setPen(textlabel->fontcolor);

    // Since I always just take the points from graphviz and pass them to Qt
    // as pixel I also have to set the pixel size of the font.
    QFont font(textlabel->fontname, textlabel->fontsize);
    font.setPixelSize(textlabel->fontsize);
    painter->setFont(font);

    QString text(QString::fromUtf8(textlabel->text));
    QFontMetricsF fm(painter->fontMetrics());
    QRectF rect(fm.boundingRect(text));
    rect.moveCenter(gToQ(textlabel->pos, false));
    painter->drawText(rect.adjusted(-1, -1, +1, +1), Qt::AlignCenter, text);
}

void
GraphView::drawLabel2(const textlabel_t* textlabel, QPainter* painter) const
{
    painter->setPen(textlabel->fontcolor);

    // Since I always just take the points from graphviz and pass them to Qt
    // as pixel I also have to set the pixel size of the font.
    QFont font(textlabel->fontname, textlabel->fontsize);
    font.setPixelSize(textlabel->fontsize);
    painter->setFont(font);

    QString text(QString::fromUtf8(textlabel->text));
    QFontMetricsF fm(painter->fontMetrics());
    QRectF rect(fm.boundingRect(text));
    rect.moveCenter(gToQ(textlabel->pos, true));
    painter->drawText(rect.adjusted(-1, -1, +1, +1), Qt::AlignCenter, text);
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

    if (GD_charset(graph) != 0)
    {
    qWarning("unsupported charset");
    }

    // don't use here since it adjusts the values
    graphRect = QRectF(GD_bb(graph).LL.x, GD_bb(graph).LL.y, GD_bb(graph).UR.x, GD_bb(graph).UR.y);
    setSceneRect(graphRect);//.adjusted(-5, -5, +5, +5));


    setBackgroundBrush(Qt::white);

    for (node_t* node = agfstnode(graph); node != NULL; node = agnxtnode(graph, node))
    {
    QPicture pictureNode;
    QPainter painterNode;

    painterNode.begin(&pictureNode);
    drawLabel(ND_label(node), &painterNode);
    painterNode.end();

    GraphNode* item = new GraphNode(makeShape(node), pictureNode, "igor");

    item->setPos(gToQ(ND_coord(node)));

    QPen pen(Qt::black);
    pen.setWidthF(3.0);
    item->setPen(pen);

    QBrush brush(Qt::green);
    item->setBrush(brush);

    QString tooltip = aggetToQString(node, "tooltip", "igor");
    if (!tooltip.isEmpty())
    {
        tooltip.replace("\\n", "\n");
        item->setToolTip(tooltip);
    }

    addItem(item);

    for (edge_t* edge = agfstout(graph, node); edge != NULL; edge = agnxtout(graph, edge))
    {
        const splines* spl = ED_spl(edge);
        if (spl == NULL)
        continue;

        QPicture pictureLabel;
        QPainter painterLabel;

        if (ED_label(edge)==0)
            continue;
        //std::cout << ED_label(edge)->text << std::endl;

        QPicture pictureEdge;
        QPainter painterEdge;

       // painterLabel.begin(&pictureLabel);
       // drawLabel2(ED_label(edge),&painterLabel);
       // painterLabel.end();

        for (int i = 0; i < spl->size; ++i)
        {
        const bezier& bz = spl->list[i];

        QColor color(Qt::black);

        QPainterPath path(makeBezier(bz));

        painterEdge.begin(&pictureEdge);
        if (bz.sflag)
            drawArrow(QLineF(gToQ(bz.list[0]), gToQ(bz.sp)), color, &painterEdge);
        if (bz.eflag)
            drawArrow(QLineF(gToQ(bz.list[bz.size-1]), gToQ(bz.ep)), color, &painterEdge);
        painterEdge.end();

        GraphEdge* item = new GraphEdge(path, pictureEdge);

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


GraphNode::GraphNode(const QPainterPath& path, const QPicture& picture, const QString& name)
    : QGraphicsPathItem(path),
      picture(picture),
      name(name)
{
   // setFlag(QGraphicsItem::ItemIsMovable);
}


void
GraphNode::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    painter->save();
    QGraphicsPathItem::paint(painter, option, widget);
    painter->restore();
    picture.play(painter);
}


GraphEdge::GraphEdge(const QPainterPath& path, const QPicture& picture)
    : QGraphicsPathItem(path),
      picture(picture)
{
}


QRectF
GraphEdge::boundingRect() const
{
    return QGraphicsPathItem::boundingRect().united(picture.boundingRect());
}


void
GraphEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    QGraphicsPathItem::paint(painter, option, widget);
    painter->restore();

    picture.play(painter);
}

GraphLabel::GraphLabel(const QPainterPath& path,const QPicture& picture)
    : QGraphicsPathItem(path),
      picture(picture)
{
}

void
GraphLabel::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->save();
    QGraphicsPathItem::paint(painter, option, widget);
    painter->restore();

    picture.play(painter);
}

