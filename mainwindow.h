#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <QTextStream>

#include "t_worker.h"
#include "cryptor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_rdbtn_mode_file_clicked();

    void on_rdbtn_mode_pass_clicked();

    void on_rdbtn_encrypt_clicked();

    void on_rdbtn_decrypt_clicked();

    void on_btnSelectXORFile_clicked();

    void on_btnXORKeySelect_clicked();

    void on_btnSelectRSAFile_clicked();

    void on_btnRSAPrivKey_clicked();

    void on_btnRSAPubKey_clicked();

    void on_btnGenRSAKeys_clicked();

    void on_btnClearRSAPage_clicked();

    void on_btnExportKeysToFile_clicked();

    void on_btnSelectFileForHex_clicked();

    void on_btnFileToHex_clicked();

    void on_btnHexValuesExport_clicked();

    void on_btnClearXORSection_clicked();

    void on_btnXOR_clicked();

    void Worker_Finished();

    void on_btnDecryptRSA_clicked();

    void on_btnEncryptRSA_clicked();

    void on_btnClearRSA_crypt_page_clicked();

    void on_btnXORtoHex_clicked();

private:

    QString getFile();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
