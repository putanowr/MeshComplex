#include "mainwindow.h"
#include "cmapplication.h"


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (nullptr != qApp) {
      ((CMApplication*)qApp)->myMessageOutput(type, context, msg);
    } else {
       QByteArray localMsg = msg.toLocal8Bit();
       switch (type) {
       case QtDebugMsg:
           fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       case QtWarningMsg:
           fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       case QtCriticalMsg:
           fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       case QtFatalMsg:
           fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           abort();
       }
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    CMApplication a(argc, argv);
    MainWindow w;
    auto mc = a.getMeshComplex();
    w.setMeshComplex(a.getMeshComplex());
    w.show();
    return a.exec();
}
