#include <QApplication>
#include <QTest>

#include "test_ScreenController.cpp"
#include "test_MindMap.cpp"
#include "test_SessionUsersList.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new test_ScreenController, argc, argv);
    QTest::qExec(new test_MindMap, argc, argv);
    QTest::qExec(new test_SessionUsersList, argc, argv);

    return EXIT_SUCCESS;
}
