#include "Ring0Calculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    a.setWindowIcon(QIcon(":/Ring0Calculator/img/kernel_10042426.png"));
    Ring0Calculator w;
    w.setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    w.show();
    return a.exec();
}
