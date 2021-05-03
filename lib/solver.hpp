#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QObject>

#include "parser.hpp"

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(Parser *parent = nullptr);
    QVector<QPair<QPoint, int>> solve();

signals:

};

#endif // SOLVER_HPP
