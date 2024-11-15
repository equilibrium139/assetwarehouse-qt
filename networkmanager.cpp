#include "networkmanager.h"

QNetworkAccessManager* NetworkManager::instance() {
    static QNetworkAccessManager manager;
    return &manager;
}


QNetworkReply* NetworkManager::getThumbnail(const Asset& asset) {
    QUrl thumbnailUrl = spacesUrl() + "/thumbnails/" + QString::number(asset.createdBy) + "/" + asset.thumbnailUrl;
    QNetworkRequest request{thumbnailUrl};
    return instance()->get(request);
}

const QString& NetworkManager::spacesUrl() {
    static QString url = "https://assetwarehouse.nyc3.digitaloceanspaces.com";
    return url;
}
