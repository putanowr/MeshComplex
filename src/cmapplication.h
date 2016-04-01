#ifndef CMAPPLICATION_H
#define CMAPPLICATION_H

#include <QObject>
#include <QString>
#include <QApplication>

class CMApplication : public QApplication
{
  Q_OBJECT

public:
    CMApplication(int &argc, char *argv[]);

    static void Warn(const char *msg);

signals:

public slots:
};

#endif // CMAPPLICATION_H
