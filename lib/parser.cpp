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

void Parser::parse(QFile &file)
{
    Blocks.clear();

    if (!file.open(QIODevice::ReadOnly)) throw ParserException();

    while (!file.atEnd())
    {
        auto line = QString(file.readLine()).simplified();
        Blocks.push_back(parseLine(line));
    }
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

    auto s = statements.back();
    auto op = s.back();

    if(op.isDigit()) return Block(indexes, '\0', s.toInt());
    else return Block(indexes, op.toLatin1(), s.left(s.length() - 1).toInt());
}
