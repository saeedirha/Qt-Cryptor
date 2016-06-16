#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab->setAutoFillBackground(true);
    ui->tab_2->setAutoFillBackground(true);
    ui->tab_3->setAutoFillBackground(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rdbtn_mode_file_clicked()
{
    ui->txtPassphrase->setEnabled(false);
    ui->txtXORKeyFile->setEnabled(true);
    ui->btnXORKeySelect->setEnabled(true);
}

void MainWindow::on_rdbtn_mode_pass_clicked()
{
    ui->txtPassphrase->setEnabled(true);
    ui->txtXORKeyFile->setEnabled(false);
    ui->btnXORKeySelect->setEnabled(false);
}

void MainWindow::on_rdbtn_encrypt_clicked()
{
    ui->txtRSAPrivKey->setEnabled(false);
    ui->btnRSAPrivKey->setEnabled(false);
    ui->btnDecryptRSA->setEnabled(false);
    ui->btnEncryptRSA->setEnabled(true);

    ui->txtRSAPubKey->setEnabled(true);
    ui->btnRSAPubKey->setEnabled(true);
}

void MainWindow::on_rdbtn_decrypt_clicked()
{
    ui->txtRSAPrivKey->setEnabled(true);
    ui->btnRSAPrivKey->setEnabled(true);
    ui->btnDecryptRSA->setEnabled(true);
    ui->btnEncryptRSA->setEnabled(false);
    ui->txtRSAPubKey->setEnabled(false);
    ui->btnRSAPubKey->setEnabled(false);
}

QString MainWindow::getFile()
{
    QString Filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), ".", tr("All Files (*.*)"));
    return Filename;
}

void MainWindow::on_btnSelectXORFile_clicked()
{
    ui->txtXORFilename->setText(getFile());
}

void MainWindow::on_btnXORKeySelect_clicked()
{
    ui->txtXORKeyFile->setText(getFile());
}

void MainWindow::on_btnSelectRSAFile_clicked()
{
    ui->txtRSAFilename->setText(getFile());
}

void MainWindow::on_btnRSAPrivKey_clicked()
{
    ui->txtRSAPrivKey->setText(getFile());
}

void MainWindow::on_btnRSAPubKey_clicked()
{
    ui->txtRSAPubKey->setText(getFile());
}
void MainWindow::on_btnSelectFileForHex_clicked()
{
   ui->txtFileToHex->setText(getFile());
}
//Generate RSA Keys
void MainWindow::on_btnGenRSAKeys_clicked()
{
    QByteArray PrivateKey;
    QByteArray PublicKey;

    QProcess *process = new QProcess(this);
    process->start("openssl.exe genrsa 2048");
    process->waitForFinished(30000);
    PrivateKey = process->readAll();
    process->close();
    QFile file("tmp-prvkey.pem");
    file.open(QIODevice::WriteOnly);
    file.write(PrivateKey);
    file.close();

    process->start("openssl.exe rsa -in tmp-prvkey.pem -pubout -outform PEM");
    process->waitForFinished(30000);
    PublicKey = process->readAll();

    QFile::remove("tmp-prvkey.pem");

    ui->txtRSAPrivateKey->setPlainText(PrivateKey);
    ui->txtRSAPublicKey->setPlainText(PublicKey);
    qDebug() << QString(PrivateKey);

}

void MainWindow::on_btnClearRSAPage_clicked()
{
    ui->txtRSAPrivateKey->setPlainText("");
    ui->txtRSAPublicKey->setPlainText("");
}

void MainWindow::on_btnExportKeysToFile_clicked()
{
    qDebug() << ui->txtRSAPrivateKey->toPlainText();
    QFile PrivateKeyfile("PrivateKey.pem");
    QFile PublicKeyFile("PublicKey.pem");

    if(PrivateKeyfile.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&PrivateKeyfile);
        stream << ui->txtRSAPrivateKey->toPlainText();
        PrivateKeyfile.flush();

    }else{
        ui->statusBar->showMessage("Cannot write to file!" , 100);
    }

    if(PublicKeyFile.open(QIODevice::WriteOnly))
    {
        QTextStream stream2(&PublicKeyFile);
        stream2 << ui->txtRSAPublicKey->toPlainText();
        PublicKeyFile.flush();

    }else{
        ui->statusBar->showMessage("Cannot write to file!" , 100);
    }

    ui->statusBar->showMessage("PrivateKey.pem and PublicKey.pem Saved to current directory!" , 5000);
    PrivateKeyfile.close();
    PublicKeyFile.close();

    QProcess *process = new QProcess(this);
    process->start("openssl req -x509 -new -days 100000 -key PrivateKey.pem -out SigCert.pem -subj \"/\"");
    process->waitForFinished(30000);

    process->close();

}



void MainWindow::on_btnFileToHex_clicked()
{
    QFile file(ui->txtFileToHex->text());
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray input;
        QString output = "\"";
        int line=0;
        input = file.readAll();

        for(int i=0; i < input.length(); i++)
        {
            if(line ==16)
            {
                output += "\"\n\"";
                line=0;
            }
            output += "\\x" + QString::number( ( (unsigned int)input.at(i) &0xFFU ), 16 ).toUpper().rightJustified(2,'0');
            line++;
        }
        output += "\"";
        ui->txtHexFile->setPlainText(output);


    }else{
        ui->statusBar->showMessage("Cannot open the file :(" , 5000);
    }

    file.close();

}

void MainWindow::on_btnHexValuesExport_clicked()
{
    QFile file("Hex.txt");

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << ui->txtHexFile->toPlainText();
        file.flush();

    }else{
        ui->statusBar->showMessage("Cannot write to file!" , 100);
    }
    ui->statusBar->showMessage("Hex.txt File Created" , 5000);
    file.close();
}

void MainWindow::on_btnClearXORSection_clicked()
{
    ui->txtXORFilename->setText("");
    ui->txtXORKeyFile->setText("");
    ui->txtPassphrase->setText("");
}
//XOR funtionality
void MainWindow::on_btnXOR_clicked()
{
    if(ui->rdbtn_mode_pass->isChecked() == true)
    {
        ui->statusBar->showMessage("XORing based on Passphrase Key" , 5000);
        MyCryptor *m_cryptor = new MyCryptor(this,  ui->txtXORFilename->text() ,ui->txtPassphrase->text());

        connect(m_cryptor,SIGNAL(finished()), this, SLOT(Worker_Finished()));
        m_cryptor->start();


    }else if(ui->rdbtn_mode_file->isChecked() == true)
    {
        ui->statusBar->showMessage("XORing based on File Key" , 5000);

        t_worker *worker = new t_worker(this, ui->txtXORFilename->text() , ui->txtXORKeyFile->text());
        connect(worker,SIGNAL(finished()), this, SLOT(Worker_Finished()));

        worker->start();
    }
ui->btnXORtoHex->setEnabled(true);
}

void MainWindow::Worker_Finished()
{
    ui->statusBar->showMessage("Finished En/Decryption :)" , 5000);
    qDebug() << "Thread Finished!";
}

void MainWindow::on_btnDecryptRSA_clicked()
{
    QString input = QString("openssl.exe smime -decrypt -in %1 -inform PEM -out %2-dec -inkey %3").arg(ui->txtRSAFilename->text()).
            arg(ui->txtRSAFilename->text()).arg(ui->txtRSAPrivKey->text());
    qDebug()  << input;
    QProcess *process = new QProcess(this);
    process->start(input);
    process->waitForFinished(-1);
    qDebug() << process->readAll();
    process->close();
}

void MainWindow::on_btnEncryptRSA_clicked()
{
    QString input = QString("openssl.exe smime -encrypt -binary -aes-256-cbc -in %1 -out %2.enc -outform PEM %3").arg(ui->txtRSAFilename->text()).
            arg(ui->txtRSAFilename->text()).arg(ui->txtRSAPubKey->text());
    qDebug()  << input;
    QProcess *process = new QProcess(this);
    process->start(input);
    process->waitForFinished(-1);
    qDebug() << process->readAll();
    process->close();
}

void MainWindow::on_btnClearRSA_crypt_page_clicked()
{
    ui->txtRSAFilename->setText("");
    ui->txtRSAPubKey->setText("");
    ui->txtRSAPrivKey->setText("");

}

void MainWindow::on_btnXORtoHex_clicked()
{
ui->txtFileToHex->setText(ui->txtXORFilename->text() + "-Xored");
ui->btnFileToHex->click();
}
