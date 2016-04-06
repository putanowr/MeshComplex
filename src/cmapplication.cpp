#include <QMessageBox>
#include "cmapplication.h"
#include "meshcomplex.h"

CMApplication::CMApplication(int &argc, char *argv[]) : QApplication(argc, argv)
{
  myComplex =  new MeshComplex(this);
}

void CMApplication::Warn(const char *message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

void CMApplication::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    auto detail = QString("%1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
    switch (type) {
    case QtDebugMsg:
        emit message(QString("Debug %1").arg(detail));
        break;
    case QtWarningMsg:
        emit message(QString("Warning %1").arg(detail));
        break;
    case QtCriticalMsg:
        emit message(QString("Critical %1").arg(detail));
        break;
    case QtFatalMsg:
        emit message(QString("Fatal %1").arg(detail));
        abort();
    }
}
