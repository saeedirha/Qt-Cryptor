#include "t_worker.h"

t_worker::t_worker(QObject *parent, const QString& file ,const QString& Keyfile ):
    QThread(parent), filename(file), Keyfile(Keyfile)
{

}

void t_worker::run()
{
   qDebug() << "Running";
   std::ifstream m_input, key;
   std::ofstream m_output;

   m_input.open(filename.toStdString(), ios::in | ios::binary);
   key.open(Keyfile.toStdString(), ios::in | ios::binary);
   m_output.open(filename.toStdString() + "-Xored", ios::out | ios::binary);


       //read the file
       char ch;
       char ch2;
       key.seekg(0, ios_base::end);
       unsigned int size = key.tellg();
       key.seekg(0);
       int counter = 0;

       cout << "[+]Key File size is: " << size << " bytes" << "\n----[Key Hex Contents]----" << endl;

       while (counter !=size)
       {
           key.read((&ch), 1);
           cout << "0x" << hex << setfill('0') << setw(2) << ((int)ch & 0xffU) << " ";
           counter++;
       }
       counter = 0;
       cout << "\n---------------------------------------" << endl;
       key.seekg(0);

       int byte1, byte2;

       while (!m_input.eof())
       {
           if (counter == size)
           {
               counter = 0;
               key.seekg(0);
           }

           m_input.read((&ch), 1);
           key.read((&ch2), 1);

           byte1 = (int)ch;
           byte2 = (int)ch2;
           unsigned char x = byte1 ^ byte2;
           m_output << x;
           counter++;
       }

       m_input.close();
       key.close();
       m_output.close();

       cout << "[!]DONE :)" << endl;
}
