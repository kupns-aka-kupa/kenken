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

QDebug operator<<(QDebug dbg, const Block &block)
{
    if (block.Indexes.isEmpty())
        dbg.nospace() << "Block() ";
    else
        dbg.nospace() << "Block(" << block.Total << ", " << QString(block.Op) << ") ";
    return dbg.maybeSpace();
}

void Parser::parse(QFile &file)
{
    Blocks.clear();

    if (!file.open(QIODevice::ReadOnly)) throw ParserException();

    while (!file.atEnd())
    {
        auto line = QString(file.readLine()).simplified();
        Blocks.push_back(QSharedPointer<Block>(parseLine(line)));
    }
    file.close();
}

Block *Parser::parseLine(QString &line)
{
    QRegExp separator(QString("(%0| )").arg(_options.StatementSeparator));
    auto statements = line.split(separator);
    statements.removeAll("");

    auto s = statements.back();
    auto op = s.back();

    statements.removeLast();
    auto indexes = parseIndexes(statements);

    if(op.isDigit()) return new Block(indexes, '\0', s.toInt());
    else return new Block(indexes, op.toLatin1(), s.leftRef(s.length() - 1).toInt());
}

QVector<QPoint> Parser::parseIndexes(const QStringList &statements) const
{
    QVector<QPoint> indexes;

    foreach(auto item, statements)
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

    return std::move(indexes);
}

int Parser::size() const
{
    QSet<int> i;

    foreach(auto block, Blocks)
    {
        foreach(auto index, block->Indexes)
        {
            i.insert(std::max(index.x(), index.y()));
        }
    }

    return *std::max_element(i.begin(), i.end());
}
