#include "solver.hpp"

Solver::Solver(Parser *parent) : QObject(parent) { }

QVector<QPair<QPoint, int>> Solver::solve()
{
    auto p = static_cast<Parser *>(parent());
    auto b = p->Blocks;
    int s = p->size();
    QVector<int> v(s);

    foreach(auto b, p->Blocks)
    {
        std::iota(v.begin(), v.end(), 1);

        for (auto&& i : iter::combinations(v, 2))
        {
            try
            {
                auto l = *i.rbegin();
                auto r = *i.begin();
                qDebug("%d %c %d = %d", l, b.Op, r,
                       std::invoke(Ops[b.Op], l, r));
            }
            catch(const std::bad_function_call& e)
            {
                continue;
            }
        }

    }
    return QVector<QPair<QPoint, int>> ();
}
