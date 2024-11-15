#include "asset.h"

#include <QJsonArray>

Asset::Asset(const QJsonObject& object)
    : name(object.value("name").toString()), description(object.value("description").toString()), fileUrl(object.value("file_url").toString()),
    thumbnailUrl(object.value("thumbnail_url").toString()), username(object.value("username").toString()), id(object.value("id").toInt()),
    createdBy(object.value("created_by").toInt()), downloads(object.value("downloads").toInt()), views(object.value("views").toInt())
{
    QJsonArray tagsJson = object.value("tags").toArray();
    int tagCount = tagsJson.count();
    tags.reserve(tagCount);
    for (int i = 0; i < tagCount; i++) {
        tags.push_back(tagsJson[i].toString());
    }

    QString createdAtStr = object.value("created_at").toString();
    createdAt = QDateTime::fromString(createdAtStr, Qt::ISODateWithMs).toLocalTime();

    QString updatedAtStr = object.value("updated_at").toString();
    updatedAt = QDateTime::fromString(updatedAtStr, Qt::ISODateWithMs).toLocalTime();
}
