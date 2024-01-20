#include "window.h"
#include "qapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window *win = new window();
    return a.exec();
}
