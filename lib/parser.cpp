#include "parser.hpp"

Parser::Parser(QObject *parent)
    : QObject(parent)
{
    _options =
    {
        .IndexSeparator = ',',
        .StatementSeparator = ';'
    };
}

QVector<Block> Parser::parse(QFile &file)
{
    if (!file.open(QIODevice::ReadOnly)) throw ParserException();
    QVector<Block> result;

    while (!file.atEnd())
    {
        auto line = QString(file.readLine()).simplified();
        result.push_back(parseLine(line));
    }
    return result;
}

Block Parser::parseLine(QString &line)
{
    QRegExp separator(QString("(%0| )").arg(_options.StatementSeparator));
    auto statements = line.split(separator);
    statements.removeAll("");

    QVector<QPoint> indexes;

    foreach(auto item, QStringList(statements.begin(), statements.end() - 1))
    {
        auto separated = item.split(_options.IndexSeparator);
        QVector<int> i;

        bool ok;
        std::transform(separated.begin(), separated.end(), std::back_inserter(i),
        [&](const QString& s) -> int
        {
            int r = s.toInt(&ok);
            if(!ok) throw ParserException();
            return r;
        });

        indexes.push_back({i.front(), i.back()});
    }

    auto constraint = statements.back();
    char operation = constraint.right(1).front().toLatin1();
    constraint.truncate(constraint.lastIndexOf(operation));

    return Block(indexes, operation, constraint.toInt());
}

