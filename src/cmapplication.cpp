#include <QMessageBox>
#include "cmapplication.h"

CMApplication::CMApplication(int &argc, char *argv[]) : QApplication(argc, argv)
{

}

void CMApplication::Warn(const char *message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}
