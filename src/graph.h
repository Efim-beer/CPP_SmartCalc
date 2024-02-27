#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>
#include "controller.h"
#include "ui_graph.h"


namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent, QString stringlabel);
  ~Graph();

 private slots:
  void on_pushButton_build_clicked();

 private:
  Ui::Graph *ui;
  double xMin, xMax, yMin, yMax, h, X;
  int N;
  void xbegin();
  void xend();
  void ybegin();
  void yend();
  double calculate();
  QVector<double> x, y;
  QString strlabel;
};

#endif  // GRAPH_H
