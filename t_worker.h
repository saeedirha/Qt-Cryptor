#ifndef T_WORKER_H
#define T_WORKER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>

using namespace std;

class t_worker : public QThread
{
    Q_OBJECT
public:
    explicit t_worker(QObject *parent = 0 , const QString& file = "Unknown", const QString &Keyfile = "Unknown");
    void run();


signals:


private slots:

private:
    QString filename;
    QString Keyfile;


};

#endif // T_WORKER_H
