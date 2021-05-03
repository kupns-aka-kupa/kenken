#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
    , _scene(new QGraphicsScene(this))
    , _parser(new Parser(this))
    , _solver(new Solver(_parser))
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
    _parser->parse(file);

    foreach(auto block, _parser->Blocks)
    {
        _scene->addItem(new KenkenGraphicsRectItem(block));
    }
}

void MainWindow::on_solvePushButton_clicked()
{
    _solver->solve();
}
