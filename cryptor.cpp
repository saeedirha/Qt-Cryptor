#include "cryptor.h"

MyCryptor::MyCryptor(QObject *parent, const QString& file ,const QString& passphrase ):
    QThread(parent), filename(file), passphrase(passphrase)
{

}

void MyCryptor::run()
{
    qDebug() << "Running";
    std::ifstream m_input;
    std::ofstream m_output;

    m_input.open(filename.toStdString(), ios::in | ios::binary);
    m_output.open(filename.toStdString() + "-Xored", ios::out | ios::binary);


        //read the file
        char ch;
        char ch2;
        unsigned int size = passphrase.length();

        int counter = 0;

        cout << "[+]Key File size is: " << size << " bytes" << "\n----[Key Hex Contents]----" << endl;

        while (counter !=size)
        {
            ch = passphrase.at(counter).toLatin1();
            cout << "0x" << hex << setfill('0') << setw(2) << ((int)ch & 0xffU) << " ";
            counter++;
        }
        counter = 0;
        cout << "\n---------------------------------------" << endl;


        int byte1, byte2;

        while (!m_input.eof())
        {
            if (counter == size)
            {
                counter = 0;
            }

            m_input.read((&ch), 1);
            ch2 = passphrase.at(counter).toLatin1();

            byte1 = (int)ch;
            byte2 = (int)ch2;
            unsigned char x = byte1 ^ byte2;
            m_output << x;
            counter++;
        }

        m_input.close();
        m_output.close();

        cout << "[!]DONE :)" << endl;
}
