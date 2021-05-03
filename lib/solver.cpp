#include "solver.hpp"

Solver::Solver(Parser *parent) : QObject(parent) { }

QVector<QPair<QPoint, int>> Solver::solve()
{
    auto p = static_cast<Parser *>(parent());
    auto b = p->Blocks;
    int s = p->size();

    foreach(auto b, p->Blocks)
    {
        qDebug() << b.Indexes << b.Op << b.Total;
        try
        {
            qDebug() << std::invoke(Ops[b.Op], 1, 2);
        }
        catch(const std::bad_function_call& e)
        { /* ignore */ }

    }
    return QVector<QPair<QPoint, int>> ();
}
