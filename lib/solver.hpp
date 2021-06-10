#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QObject>
#include <QMultiMap>
#include <QThread>

#include <functional>

#include <combinations.hpp>
#include <product.hpp>

#include "parser.hpp"
#include "utils.hpp"

struct Solves
{
    QSet<int> Combinations;

    explicit Solves(QSet<int> &&c)
    {
        Combinations = c;
    }
};

class Solver : public QObject
{
    Q_OBJECT

    const QMap<char, std::function<int(int, int)>> Ops =
    {
        {'+', std::plus()},
        {'-', std::minus()},
        {'/', std::divides()},
        {':', std::divides()},
        {'*', std::multiplies()},
    };
    using Solution = QHash<QPoint, int>;

public:
    explicit Solver(Parser *parent = nullptr);
    ~Solver() = default;

    Solution solve();

private:
    static QSet<QPoint> cross(const QVector<int> &range,
                              const QPoint &index);

    QSet<int> variantsPerBlock(const QVector<int> &range, const Block *b, Solution &solution);

};

#endif // SOLVER_HPP
