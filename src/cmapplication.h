#ifndef CMAPPLICATION_H
#define CMAPPLICATION_H

#include <QObject>
#include <QString>
#include <QApplication>
#include <QtMsgHandler>

#include "meshcomplex.h"

class MeshComplex;

class CMApplication : public QApplication
{
  Q_OBJECT

public:
    CMApplication(int &argc, char *argv[]);

    static void Warn(const char *msg);
    MeshComplex *getMeshComplex() { return myComplex; }
    void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
   void message(const QString &msg);

public slots:

private:
   MeshComplex *myComplex;
};

#endif // CMAPPLICATION_H
