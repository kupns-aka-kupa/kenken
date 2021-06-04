#ifndef PARSER_HPP
#define PARSER_HPP

#include <QObject>
#include <QPoint>
#include <QDebug>
#include <QDataStream>
#include <QException>
#include <QFile>

class ParserException : public QException
{
public:
    void raise() const override { throw *this; }
    ParserException *clone() const override
    {
        return new ParserException(*this);
    }
};

struct ParserOptions
{
    char IndexSeparator;
    char StatementSeparator;
};

struct Block
        {
    QVector<QPoint> Indexes;
    char Op;
    int Total;

    Block() = default;
    explicit Block(const QVector<QPoint> &indexes, char op, int total)
    {
        Indexes = indexes;
        Op = op;
        Total = total;
    }

    friend QDebug operator<<(QDebug dbg, const Block &block);
};

class Parser : public QObject
{
Q_OBJECT

public:
    explicit Parser(QObject *parent = nullptr);
    ~Parser() = default;

    void parse(QFile &);
    Block *parseLine(QString &);
    int size();

private:
     Q_REQUIRED_RESULT QVector<QPoint> parseIndexes(const QStringList &statements) const;

public:
    QVector<QSharedPointer<Block>> Blocks;
private:
    ParserOptions _options;

};

#endif // PARSER_HPP
