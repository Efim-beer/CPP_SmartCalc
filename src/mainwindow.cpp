#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_lbr, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_rbr, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(arithmetic()));
  ui->pushButton_x->setCheckable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::arithmetic() {
  if (ui->label->text() == "Invalid argument" || ui->label->text() == "nan" ||
      ui->label->text() == "-inf" || ui->label->text() == "inf") {
    ui->label->setText("");
  }
  QPushButton *button = (QPushButton *)sender();
  QString oper;
  if (button->text() == "x^y") {
    oper = (ui->label->text() + "^");
  } else if (button->text() == "√x") {
    oper = (ui->label->text() + "sqrt(");
  } else if (button->text() == ".") {
    oper = (ui->label->text() + ".");
  } else if (button->text() == "x") {
    button->setChecked(true);
    oper = (ui->label->text() + "(x)");
  } else {
    oper = (ui->label->text() + button->text());
  }
  ui->label->setText(oper);
}

void MainWindow::functions() {
  if (ui->label->text() == "Invalid argument") {
    ui->label->setText("");
  }
  QPushButton *button = (QPushButton *)sender();
  QString oper;
  oper = (ui->label->text() + button->text() + "(");
  ui->label->setText(oper);
}

void MainWindow::on_pushButton_res_clicked() {
  if (ui->label->text() == "Invalid argument" || ui->label->text() == "") {
    ui->label->setText("");
  } else {
    QString res = ui->label->text();
    stringdigit = res.toLocal8Bit();
    if (ui->pushButton_x->isChecked()) {
      char var_x[250];
      double X = ui->doubleSpinBox_value->value();
      snprintf(var_x, 250, "%lf", X);
      stringdigit.replace("x", var_x);
    }
    calculate();
  }
}

void MainWindow::calculate() {
  const std::string str = stringdigit.data();
  char result_string[100] = {0};
  s21::Controller hello_model(str);
  std::pair<std::string, double> main_result = hello_model.Calcroller();
  if (main_result.first.size() == 0) {
    main_result.second = main_result.second == -0.0 ? 0.0 : main_result.second;
    sprintf(result_string, "%.15g", main_result.second);
    ui->label->setText(result_string);
  } else {
    QString error_text = QString::fromLocal8Bit(main_result.first.c_str());
    ui->label->setText(error_text);
  }
}

void MainWindow::on_pushButton_ac_clicked() { ui->label->setText(""); }

void MainWindow::on_pushButton_fx_clicked() {
  if (ui->label->text() == "Invalid argument" || ui->label->text() == "") {
    ui->label->setText("");
  } else {
    Graph window(nullptr, ui->label->text());
    window.setModal(true);
    window.exec();
  }
}
