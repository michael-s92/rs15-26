#ifndef QGRAPH_H
#define QGRAPH_H

#include <QtWidgets>
#include <graphviz/gvc.h>


//nesto

class GraphNode;
class GraphEdge;

class GraphView : public QGraphicsScene
{
    Q_OBJECT

public:

    GraphView();
    GraphView(const QString& filename,QWidget* parent = 0);
    GraphView(graph_t* graph, QWidget* parent = 0);
    virtual ~GraphView();

    virtual void renderGraph(const QString& filename);
    virtual void renderGraph(graph_t* graph);

    void setNodeColor(QColor color);

    void clearGraph();

private:

    void init();

    QRectF graphRect;
    QVector<GraphNode *> nodes;
    QVector<GraphEdge *> edges;

    QColor nodeColor;

    QPointF transliraj(const point& p, bool up_down) const;
    QPointF transliraj(const pointf& p, bool up_down = true) const;

    void make_ellipse_helper(node_t *node, QPainterPath &path) const;
    QPainterPath make_shape(node_t *node) const;

    QPainterPath makeBezier(const bezier& bezier) const;

    void drawNodeDetails(const textlabel_t* textlabel, QPainter* painter) const;
    void drawEdgeDetails(const QLineF& line,const textlabel_t* textlabel, const QColor& color, QPainter* painter) const;

};

class GraphItem : public QGraphicsPathItem
{
public:
    GraphItem(const QPainterPath& path, const QPicture& picture);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    virtual int ind() = 0;

protected:
    QPicture picture;

};

class GraphNode : public QObject, public GraphItem
{
    Q_OBJECT

public:
    GraphNode(int state, const QPainterPath& path, const QPicture& picture);

public:
    int state;
    int ind();

};


class GraphEdge : public GraphItem
{
public:
    GraphEdge(int state1, int state2,char c, const QPainterPath& path, const QPicture& picture);
    QRectF boundingRect() const;

public:
    int state1;
    int state2;
    char c;

    int ind();
};


#endif
