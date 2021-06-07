#include <QtTest>

#include "parser.hpp"

class ParserTestCase : public QObject
{
    Q_OBJECT

    Parser *_parser;
    QString _data;
public:
    ParserTestCase() = default;
    ~ParserTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();
    void init();
    void validTestCase_data();
    void validTestCase();
    void invalidTestCase_data();
    void invalidTestCase();
    void fileTestCase_data();
    void fileTestCase();
    void cleanupTestCase();
};

void ParserTestCase::initTestCase()
{
    _parser = new Parser(this);
}

void ParserTestCase::initTestCase_data()
{
    Q_INIT_RESOURCE(data);
}

void ParserTestCase::init()
{
    QFETCH(QString, data);
    _data = data;
}

void ParserTestCase::validTestCase_data()
{
    QTest::addColumn<QString>("data");

    QDirIterator it(":valid", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        auto file = QFile(it.next());
        file.open(QIODevice::ReadOnly);
        QTest::newRow(it.fileName().toLocal8Bit()) << QString(file.readAll());
    }
}

void ParserTestCase::validTestCase()
{
    QString line;
    QTextStream stream(&_data);

    QBENCHMARK
    {
        while (stream.readLineInto(&line))
        {
            _parser->parseLine(line);
        }
    }
}

void ParserTestCase::invalidTestCase_data()
{
    QTest::addColumn<QString>("data");

    QDirIterator it(":invalid", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        auto file = QFile(it.next());
        file.open(QIODevice::ReadOnly);
        QTest::newRow(it.fileName().toLocal8Bit()) << QString(file.readAll());
    }

}

void ParserTestCase::invalidTestCase()
{
    QString line;
    QTextStream stream(&_data);

    QVERIFY_EXCEPTION_THROWN(
    while (stream.readLineInto(&line))
    {
        _parser->parseLine(line);
    }, ParserException);

}

void ParserTestCase::fileTestCase_data()
{
    QTest::addColumn<QString>("data");

    QDirIterator it(":valid", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QTest::newRow(it.fileName().toLocal8Bit()) << it.next();
    }
}

void ParserTestCase::fileTestCase()
{
    QDir dir(":valid");

    QFileInfo info(dir, _data);

    QFile file(info.filePath());

    QBENCHMARK
    {
        _parser->parse(file);
    }
}

void ParserTestCase::cleanupTestCase() { }

QTEST_APPLESS_MAIN(ParserTestCase)

#include "tst_parsertestcase.moc"
