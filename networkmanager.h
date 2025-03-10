#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>

#include "asset.h"

class NetworkManager {
public:
    static QNetworkAccessManager* instance();
    static QNetworkReply* getThumbnail(const Asset& asset);
    static QNetworkReply* getModel(const Asset& asset);


private:
    static const QString& spacesUrl();
    NetworkManager() = default;
    ~NetworkManager() = default;
};

#endif // NETWORKMANAGER_H
