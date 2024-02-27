#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "controller.h"
#include "graph.h"
#include "mymodel.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QByteArray stringdigit;

 private:
  Ui::MainWindow *ui;

 private slots:
  void arithmetic();
  void functions();
  void on_pushButton_res_clicked();
  void calculate();
  void on_pushButton_ac_clicked();
  void on_pushButton_fx_clicked();
};
#endif  // MAINWINDOW_H
