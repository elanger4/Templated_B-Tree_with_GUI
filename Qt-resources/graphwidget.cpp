/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <stack>
#include <math.h>
#include <bnode.h>

#include <QKeyEvent>

GraphWidget::GraphWidget(QWidget *parent, btree<int> *tree)
: QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("B-Tree"));

    /*
    std::stack<bnode<int>* > bstack;
    std::stack<Node*> gstack;
    bnode<int> *bcurrent = tree->getRoot();
    Node *gcurrent = new Node(this, bcurrent->getTooltip());
    scene->addItem(gcurrent);
    gcurrent->setPos(0,0);
    Node *gparent = gcurrent;
    bstack.push(bcurrent);
    gstack.push(gcurrent);
    //just make connections from current to all of currents children. 
    //std::cout <<"about to enter while stack!empty" <<std::endl;
    while(!bstack.empty() && !gstack.empty()) {
        bcurrent = bstack.top();
        gparent = gstack.top();
        bstack.pop();
        gstack.pop();
        for (int i = 0; i < bcurrent->getNumChildren(); i++) {
            //runs for each child
            if (!bcurrent->getChildren(i)->getLeaf()) {
                bnode<int> *temp = bcurrent->getChildren(i);
                gcurrent = new Node(this, temp->getTooltip());
                scene->addItem(gcurrent);
                scene->addItem(new Edge(gcurrent, gparent));
                gstack.push(gcurrent);
                bstack.push(temp);
            }
        }
    }

    */








   // /* 
    Node *root = new Node(this, "15");
    root->setPos(0, 0);
    Node *node4 = new Node(this, "10");
    Node *node6 = new Node(this, "20");
    Node *node7 = new Node(this, "3 5");
    Node *node8 = new Node(this, "13");
    Node *node9 = new Node(this, "1 2");
    Node *node10 = new Node(this, "4");
    Node *node11 = new Node(this, "6 7");
    Node *node12 = new Node(this, "11 12");
    Node *node13 = new Node(this, "14");
    Node *node14 = new Node(this, "18");
    Node *node15 = new Node(this, "16 17");
    Node *node16 = new Node(this, "19");
    Node *node17 = new Node(this, "24");
    Node *node18 = new Node(this, "21 22");
    Node *node19 = new Node(this, "25 26");

    scene->addItem(root);
    scene->addItem(node4);
    scene->addItem(node6);
    scene->addItem(node7);
    scene->addItem(node8);
    scene->addItem(node9);
    scene->addItem(node10);
    scene->addItem(node11);
    scene->addItem(node12);
    scene->addItem(node13);
    scene->addItem(node14);
    scene->addItem(node15);
    scene->addItem(node16);
    scene->addItem(node17);
    scene->addItem(node18);
    scene->addItem(node19);

    scene->addItem(new Edge(root, node4));
    scene->addItem(new Edge(root, node6));
    scene->addItem(new Edge(node4, node7));
    scene->addItem(new Edge(node4, node8));
    scene->addItem(new Edge(node7, node9));
    scene->addItem(new Edge(node7, node11));
    scene->addItem(new Edge(node7, node10));
    scene->addItem(new Edge(node8, node12));
    scene->addItem(new Edge(node13, node8));
    scene->addItem(new Edge(node6, node14));
    scene->addItem(new Edge(node14, node15));
    scene->addItem(new Edge(node14, node16));
    scene->addItem(new Edge(node17, node6));

    scene->addItem(new Edge(node17, node18));
    scene->addItem(new Edge(node17, node19));
    
  // */

}


void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}


void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            centerNode->moveBy(0, -20);
            break;
        case Qt::Key_Down:
            centerNode->moveBy(0, 20);
            break;
        case Qt::Key_Left:
            centerNode->moveBy(-20, 0);
            break;
        case Qt::Key_Right:
            centerNode->moveBy(20, 0);
            break;
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        case Qt::Key_Space:
        case Qt::Key_Enter:
            shuffle();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}


void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}


#ifndef QT_NO_WHEELEVENT

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif


void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{

}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
