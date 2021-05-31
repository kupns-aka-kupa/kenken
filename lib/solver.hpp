#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QObject>

#include <functional>

#include <combinations.hpp>

#include "parser.hpp"

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
        {'*', std::multiplies()},
    };

public:
    explicit Solver(Parser *parent = nullptr);
    ~Solver() = default;

    QVector<QPair<QPoint, int>> solve();

private:
    QSet<int> variantsPerBlock(const QVector<int> &range, const Block &b);

};

#endif // SOLVER_HPP
