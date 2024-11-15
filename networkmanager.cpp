#include "networkmanager.h"

QNetworkAccessManager* NetworkManager::instance() {
    static QNetworkAccessManager manager;
    return &manager;
}
