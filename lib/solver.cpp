#include <iostream>
#include "solver.hpp"

Solver::Solver(Parser *parent) : QObject(parent) { }

QVector<QPair<QPoint, int>> Solver::solve()
{
    auto p = dynamic_cast<Parser *>(parent());
    QVector<int> range(p->size());
    std::iota(range.begin(), range.end(), 1);

    foreach(auto b, p->Blocks)
    {
        qDebug() << variantsPerBlock(range, b);
    }


    return QVector<QPair<QPoint, int>> ();
}

QSet<int> Solver::variantsPerBlock(const QVector<int> &range,
                                   const Block &b)
{
    QSet<int> combinations;

    for (auto&& i : iter::combinations(range, 2))
    {
        try
        {
            auto l = *i.rbegin();
            auto r = *i.begin();

            Q_ASSERT(l > r);

            auto v = std::invoke(Ops[b.Op], l, r);

            if (v == b.Total)
            {
                combinations += {l, r};
                qDebug("%d %c %d = %d", l, b.Op, r, v);
            }
        }
        catch(const std::bad_function_call& e)
        {
            combinations.insert(b.Total);
        }
    }

    return combinations;
}
