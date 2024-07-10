#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QHostAddress>            // Gives access to IPV4 and IPV6
#include <QNetworkInterface>       // Gives acesss to networking card.
#include <QAbstractSocket>         // Gives access to socket communication.

#include <../include/first.h>
#include <../include/tcp_client.h>

/** Self documenting code using Doxygen.
 * @brief main The starting point
 * @param argc The argument count
 * @param argv The argument
 * @return int The exist value of the application
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        qInfo() << "App Thread: " << a.thread();
        qInfo() << "Current Thread: " << QThread::currentThread();

        Q_ASSERT(a.thread() == QThread::currentThread());

        qInfo() << "Running: " << QThread::currentThread()->isRunning();
        qInfo() << "loopLevel: " << QThread::currentThread()->loopLevel();
        qInfo() << "stackSize: " << QThread::currentThread()->stackSize();
        qInfo() << "isFinished: " << QThread::currentThread()->isFinished();
        qInfo() << "Before: " << QDateTime::currentDateTime().toString();
        QThread::sleep(2);
        qInfo() << "After: " << QDateTime::currentDateTime().toString();

        qInfo() << "got it...";       
    }


    {
        /**
         * Seven Layers of the OSI Model:
         * Application
         * Presentation
         * Session
         * Transport
         * Network
         * Data Link
         * Physical
         */

        // Get a list of address;  Qt's Qlist is a templated class holding 'QHostAddress'
        // allAddresses function member returns all of the IP address.
        QList< QHostAddress > list_hostAddress = QNetworkInterface::allAddresses();

        foreach(QHostAddress item, list_hostAddress)
            qInfo() << item;

        for (int iCnt = 0; iCnt < list_hostAddress.count(); iCnt++)
        {
            QHostAddress single_address = list_hostAddress.at(iCnt);
            qInfo() << single_address.toString();

            // https://doc.qt.io/qt-6/qhostaddress.html
            qInfo() << "\t Loopback: " << single_address.isLoopback();
            qInfo() << "\t Multicast: " << single_address.isMulticast();
            switch(single_address.protocol())
            {
                case QAbstractSocket::UnknownNetworkLayerProtocol:
                    qInfo() << "\t Protocal: unknown";
                break;
                case QAbstractSocket::AnyIPProtocol:
                    qInfo() << "\t Protocal: AnyIPProtocol";
                break;
                case QAbstractSocket::IPv4Protocol:
                    qInfo() << "\t Protocal: IKPv4Protocol";
                break;
                case QAbstractSocket::IPv6Protocol:
                    qInfo() << "\t Protocal: IKPv6Protocol";
                break;
            }
        }
    }

    /**
     * Forward Proxy; 
     * Hypertext Transfer Protocal: HTTP
     * https://spys.one/en/http-proxy-list/
     * Performing the three way hand shake; connecting to 'httpbin.org' on port 80
     * through the proxy; the proxy will be sending our message (GET /get HTTP/1.1\r\n).
     * 
     *       Connecting to:  "httpbin.org"  on port  80
     *       State:  HostLookupState
     *       State:  ConnectingState
     *       State:  ConnectedState
     *       Connected!
     *       Sending
     *       Error: QAbstractSocket::RemoteHostClosedError   "Remote host closed"
     *       State:  ClosingState
     *       State:  UnconnectedState
     *       Disconnected     
     * 
     */
    CClient client;
    client.connectToHost("httpbin.org", 80);


    return a.exec();
}
