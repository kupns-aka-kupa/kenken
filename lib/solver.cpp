#include "solver.hpp"

Solver::Solver(Parser *parent) : QObject(parent) { }

QHash<QPoint, int> Solver::solve()
{
    auto p = dynamic_cast<Parser *>(parent());

    QMultiHash<QPoint, QSharedPointer<Block>> groups;
    QHash<QSharedPointer<Block>, QSet<int>> variants;

    QVector<int> range(p->size());
    std::iota(range.begin(), range.end(), 1);

    foreach(auto block, p->Blocks)
    {
        variants.insert(block, variantsPerBlock(range, block.data()));

        foreach(const auto &index, block->Indexes)
            foreach(const auto &point, cross(range, index))
                groups.insert(point, block);
    }

    QHash<QPoint, int> solution;

    for (const auto&& [x, y] : iter::product<2>(range))
    {
        QPoint point{x, y};
        auto values = groups.values(point);
        values.erase(std::unique(values.begin(), values.end()), values.end());

        foreach(const auto &value, values)
        {
            qDebug() << *value;
            foreach(const auto &index, value->Indexes)
            {
                auto &vars = variants[value];

                if (!vars.empty())
                {
                    auto i = vars.begin();
                    solution.insert(index, *i);

                    qDebug() << *i;
                    Q_ASSERT(vars.remove(*i));
                    qDebug() << vars;
                }
            }
        }
    }

    return solution;
}

QSet<QPoint> Solver::cross(const QVector<int> &range,
                           const QPoint &index)
{
    // TODO: replace `Solver::cross(const QVector<int> &, const QPoint &)`
    //  by `iter::product`

    // NOTE: `iter::product` generate incorrect positional args
    /*
    QVector<int> coords {index.x(), index.y()};

    for (const auto&& [a, b] : iter::product(coords, range))
    {
        points.insert({a, b});
    }
    */

    QSet<QPoint> points;

    foreach(auto r, range)
    {
        points.insert({r, index.y()});
        points.insert({index.x(), r});
    }

    return points;
}

QSet<int> Solver::variantsPerBlock(const QVector<int> &range,
                                   const Block *b)
{
    QSet<int> combinations;

    for (auto&& i : iter::combinations(range, 2))
    {
        try
        {
            auto l = *i.rbegin();
            auto r = *i.begin();

            Q_ASSERT(l > r);

            auto v = std::invoke(Ops[b->Op], l, r);

            if (v == b->Total)
            {
                combinations += {l, r};
                qDebug("%d %c %d = %d", l, b->Op, r, v);
            }
        }
        catch(const std::bad_function_call& e)
        {
            combinations.insert(b->Total);
        }
    }

    return combinations;
}
