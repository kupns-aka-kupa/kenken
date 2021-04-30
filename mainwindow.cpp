#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _parser(new Parser(this))
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    auto name = QFileDialog::getOpenFileName(this, "Select file", DATA_DIR);
    QFile file(name);
    _parser->parse(file);
}
