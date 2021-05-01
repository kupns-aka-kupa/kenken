#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _parser(new Parser(this))
    , _scene(new QGraphicsScene(this))
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->graphicsView->setBackgroundBrush(Qt::white);
    _ui->graphicsView->setScene(_scene);
    _ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    _scene->clear();

    auto name = QFileDialog::getOpenFileName(this, "Select file", DATA_DIR);
    QFile file(name);
    auto blocks = _parser->parse(file);

    foreach(auto block, blocks)
    {
        _scene->addItem(new KenkenGraphicsRectItem(block));
    }
}
