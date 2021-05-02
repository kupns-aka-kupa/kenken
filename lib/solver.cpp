#include "solver.hpp"

Solver::Solver(QObject *parent) : QObject(parent) { }


QVector<QPair<QPoint, int>> Solver::solve(Parser *parser)
{
    foreach(auto b, parser->Blocks)
    {
        qDebug() << b.Indexes << b.Op << b.Total;

    }
    return QVector<QPair<QPoint, int>> ();
}
