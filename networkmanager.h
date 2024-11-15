#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>

class NetworkManager {
public:
    static QNetworkAccessManager* instance();

private:
    NetworkManager() = default;
    ~NetworkManager() = default;
};

#endif // NETWORKMANAGER_H
