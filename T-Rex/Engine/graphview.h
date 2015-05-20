#ifndef QGRAPH_H
#define QGRAPH_H

#include <QtWidgets>
#include <graphviz/gvc.h>

class GraphView : public QGraphicsScene
{
    Q_OBJECT

public:

    GraphView(const QString& filename,QWidget* parent = 0);
    GraphView(graph_t* graph, QWidget* parent = 0);
    virtual ~GraphView();

    virtual void renderGraph(const QString& filename);
    virtual void renderGraph(graph_t* graph);

    void clearGraph();

private:

    void init();

    QRectF graphRect;

    QPointF gToQ(const point& p, bool upside_down = true) const;
    QPointF gToQ(const pointf& p, bool upside_down = true) const;

    QString aggetToQString(void* obj, const char* name, const QString& fallback) const;

//    QPainterPath makeShape(node_t* node) const;
//    QPolygonF makeShapeHelper(node_t* node) const;


    void make_polygon_helper(node_t *node, QPainterPath &path) const;
    void make_ellipse_helper(node_t *node, QPainterPath &path) const;
    QPainterPath make_shape(node_t *node) const;

    QPainterPath makeBezier(const bezier& bezier) const;

    void drawLabel(const textlabel_t* textlabel, QPainter* painter) const;
    void drawLabel2(const textlabel_t* textlabel, QPainter* painter) const;

    void drawArrow(const QLineF& line, const QColor& color, QPainter* painter) const;

};


class GraphNode : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:

    GraphNode(const QPainterPath& path, const QPicture& picture, const QString& name);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:

    QPicture picture;

public:

    QString name;

};


class GraphEdge : public QGraphicsPathItem
{

public:

    GraphEdge(const QPainterPath& path, const QPicture& picture);

    QRectF boundingRect() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QPicture picture;
};

class GraphLabel : public QGraphicsPathItem
{

public:

    GraphLabel(const QPainterPath& path,const QPicture& picture);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    QPicture picture;
};




#endif
