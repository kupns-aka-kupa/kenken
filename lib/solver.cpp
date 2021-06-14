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
        variants.insert(block, variantsPerBlock(range, block.data()));

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

    QHashIterator<QSharedPointer<Block>, QSet<int>> it(variants);
    while (it.hasNext())
    {
        it.next();
        qDebug() << *it.key() << ": " << it.value();
    }
    for (const auto&& [x, y] : iter::product<2>(range))
    {
        QPoint point{x, y};
        auto current = variants.value(groups.value(point));

        qDebug() << point;
        QSet<int> v;
        for (int i = 1; i < range.size() + 1; ++i)
        {
            QPoint item{i, y};
            v |= variants.value(groups.value(item));
            qDebug() << item << v;
        }

        qDebug() << current << v - current << Qt::endl;
    }

    return solution;
}

QSet<int> Solver::variantsPerBlock(const QVector<int> &range,
                                   const Block *b)
{
    if(!Ops.contains(b->Op))
    {
        Q_ASSERT(b->Indexes.count() < 2);

        return {b->Total};
    }

    QSet<int> combinations;

    for (auto&& i : iter::combinations(range, b->Indexes.size()))
    {
        Q_ASSERT(std::is_sorted(i.begin(), i.end()));
        Q_ASSERT(std::distance(i.begin(), i.end()) == b->Indexes.size());

        auto v = std::accumulate(std::next(i.rbegin()),
                                 i.rend(),
                                 *i.rbegin(),
                                 Ops[b->Op]);

        if (v == b->Total)
        {
            combinations += {i.begin(), i.end()};
            qDebug() << QVector<int>(i.begin(), i.end()) << b->Op << v;
        }
    }

    return combinations;
}
