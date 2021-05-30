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

#ifndef QT_DEBUG
    QDir dir(DATA_DIR);
    auto name = QFileDialog::getOpenFileName(this, "Select file", dir.path());
#else
    QDir dir(":valid");
    auto name = dir.entryList().first();
#endif

    QFileInfo info(dir, name);

    QFile file(info.filePath());
    _parser->parse(file);

    foreach(auto block, _parser->Blocks)
    {
        _scene->addItem(new KenkenGraphicsRectItem(block));
    }

#ifdef QT_DEBUG
    _solver->solve();
#endif
}

void MainWindow::on_solvePushButton_clicked()
{
    _solver->solve();
}
