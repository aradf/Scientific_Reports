#include <QCoreApplication>
#include <QDebug>

#include <../include/first.h>
#include <../include/tcp_server.h>

/** Self documenting code using Doxygen.
 * @brief main The starting point
 * @param argc The argument count
 * @param argv The argument
 * @return int The exist value of the application
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CServer server;
    server.start();

    /*
        Use a tcp client application 
        telnet 127.0.0.1 2020
     */

    return a.exec();
}
