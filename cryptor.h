#ifndef CRYPTOR_H
#define CRYPTOR_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>

using namespace std;

class MyCryptor : public QThread
{
    Q_OBJECT
public:
    explicit MyCryptor(QObject *parent = 0 , const QString& file = "Unknown", const QString &passphrase = "Unknown");
    void run();


signals:


private slots:

private:
    QString filename;
    QString passphrase;


};


#endif // CRYPTOR_H
