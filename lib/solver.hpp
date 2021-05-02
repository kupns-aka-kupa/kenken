#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QObject>

#include "parser.hpp"

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = nullptr);
    QVector<QPair<QPoint, int>> solve(Parser *);

signals:

};

#endif // SOLVER_HPP
