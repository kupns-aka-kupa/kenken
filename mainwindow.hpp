#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QGraphicsScene>
#include <QDebug>

#include "parser.hpp"
#include "solver.hpp"
#include "kenkengraphicsrectitem.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadPushButton_clicked();
    void on_solvePushButton_clicked();

private:
    Ui::MainWindow *_ui;
    QGraphicsScene *_scene;
    Parser *_parser;
    Solver *_solver;
};
#endif // MAINWINDOW_HPP
