#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QDateTime>
#include <QPixmap>
#include <QString>
#include <QWidget>

#include "networkmanager.h"

namespace Ui {
class ThumbnailWidget;
}

struct ThumbnailData {
    QString imageUrl;
    QString name;
    QString description;
    QString creator;
    QDateTime date;
};

class ThumbnailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThumbnailWidget(QWidget *parent = nullptr);
    ~ThumbnailWidget();

    void setThumbnailData(const ThumbnailData& data);

private:
    Ui::ThumbnailWidget *ui;
    QNetworkAccessManager* networkManager = NetworkManager::instance();
};

#endif // THUMBNAILWIDGET_H
