#include <QtTest>

#include "parser.hpp"
#include "solver.hpp"

class SolverTestCase : public QObject
{
    Q_OBJECT

    Parser *_parser;
    Solver *_solver;
    QString _fileName;
public:
    SolverTestCase() = default;
    ~SolverTestCase() = default;

private slots:
    void initTestCase_data();
    void initTestCase();
    void init();
    void kupnsTestCase();
    void cleanupTestCase();
};

void SolverTestCase::initTestCase()
{
    _parser = new Parser(this);
    _solver = new Solver(_parser);
}

void SolverTestCase::initTestCase_data()
{
    Q_INIT_RESOURCE(data);

    QTest::addColumn<QString>("fileName");

    QDirIterator it(":valid", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        auto file = it.next();
        QTest::newRow(it.fileName().toLocal8Bit()) << file;
    }
}

void SolverTestCase::init()
{
    QFETCH_GLOBAL(QString, fileName);

    _fileName = fileName;
}

void SolverTestCase::kupnsTestCase()
{
    QDir dir(":valid");

    QFileInfo info(dir, _fileName);

    QFile file(info.filePath());

    _parser->parse(file);

    QBENCHMARK
    {
        auto solution = _solver->solve();
        QVERIFY(!solution.empty());
    }
}

void SolverTestCase::cleanupTestCase() { }

QTEST_APPLESS_MAIN(SolverTestCase)

#include "tst_solvertestcase.moc"
