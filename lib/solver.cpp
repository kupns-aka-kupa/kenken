#include "solver.hpp"

Solver::Solver(Parser *parent) : QObject(parent) { }

QVector<QPair<QPoint, int>> Solver::solve()
{
    auto p = static_cast<Parser *>(parent());
    auto b = p->Blocks;
    int s = p->size();

    qDebug() << s;
    foreach(auto b, p->Blocks)
    {
        qDebug() << b.Indexes << b.Op << b.Total;

    }
    return QVector<QPair<QPoint, int>> ();
}
