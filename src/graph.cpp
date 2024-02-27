#include "graph.h"

Graph::Graph(QWidget *parent, QString stringlabel)
    : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  strlabel = stringlabel;
}

Graph::~Graph() { delete ui; }

void Graph::on_pushButton_build_clicked() {
  xMin = ui->xmin->value();
  xMax = ui->xmax->value();
  yMin = ui->ymin->value();
  yMax = ui->ymax->value();
  h = 0.001;
  int err = 0;
  int *error = &err;
  ui->label_graph->setText(strlabel);
  if (xMin >= xMax || yMin >= yMax) {
    *error = 1;
  }
  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);
  for (X = xMin; X <= xMax && *error == 0; X += h) {
    x.push_back(X);
    char var_x[255];
    snprintf(var_x, 250, "%lf", X);
    QByteArray stringdigit = strlabel.toLocal8Bit();
    stringdigit.replace("x", var_x);
    const std::string str = stringdigit.data();
    s21::Controller graph_model(str);
    std::pair<std::string, double> main_result = graph_model.Calcroller();
    if (main_result.first.size() == 0) {
      main_result.second =
          main_result.second == -0.0 ? 0.0 : main_result.second;
      y.push_back(main_result.second);
    } else {
      *error = 1;
    }
  }
  if (*error == 0) {
    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  } else {
    ui->label_graph->setText("Invalid argument");
  }
}
