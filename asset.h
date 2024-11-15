#ifndef ASSET_H
#define ASSET_H

#include <QDateTime>
#include <QString>
#include <QVector>
#include <QJsonObject>

struct Asset
{
    QString name;
    QString description;
    QString fileUrl;
    QString thumbnailUrl;
    QString username;
    QVector<QString> tags;
    QDateTime createdAt;
    QDateTime updatedAt;
    int id;
    int createdBy;
    int downloads;
    int views;

    Asset(const QJsonObject& json);
};

#endif // ASSET_H
