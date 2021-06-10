#include "solver.hpp"

Solver::Solver(Parser *parent) : QObject(parent) { }

Solver::Solution Solver::solve()
{
    using Variants = QHash<QSharedPointer<Block>, QSet<int>>;
    using Groups = QHash<QPoint, QSharedPointer<Block>>;

    auto p = dynamic_cast<Parser *>(parent());

    Groups groups;
    Variants variants;
    Solution solution;

    QVector<int> range(p->size());
    std::iota(range.begin(), range.end(), 1);

    foreach(auto block, p->Blocks)
    {
        variants.insert(block, variantsPerBlock(range, block.data(), solution));

#ifdef USESTD
        std::for_each(std::cbegin(block->Indexes),
                      std::cend(block->Indexes),
                      std::bind(&Groups::insert, std::ref(groups),
                                std::placeholders::_1, block));
#else
        foreach(const auto &index, block->Indexes)
            groups.insert(index, block);
#endif
    }

    for (const auto&& [x, y] : iter::product<2>(range))
    {
        QPoint point{x, y};

        qDebug() << point;
        foreach(const auto &item, cross(range, point))
        {
            qDebug() << item << variants.value(groups.value(item));

        }
        qDebug() << endl;
    }

    return solution;
}

QSet<QPoint> Solver::cross(const QVector<int> &range,
                           const QPoint &index
                           )
{
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
                                   const Block *b,
                                   Solution &solution)
{
    if(!Ops.contains(b->Op))
    {
        Q_ASSERT(b->Indexes.count() < 2);

        solution.insert(b->Indexes.first(), b->Total);
        return QSet<int>();
    }

    QSet<int> combinations;

    for (auto&& i : iter::combinations(range, 2))
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

    return combinations;
}
