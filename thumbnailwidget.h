#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QDateTime>
#include <QPixmap>
#include <QString>
#include <QWidget>

#include "asset.h"
#include "clickablelabel.h"
#include "networkmanager.h"

namespace Ui {
class ThumbnailWidget;
}

class ThumbnailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThumbnailWidget(QWidget *parent = nullptr);
    ~ThumbnailWidget();
    void setThumbnailData(const Asset& asset);

private slots:
    void onThumbnailClicked();

private:
    Ui::ThumbnailWidget *ui;
    QNetworkAccessManager* networkManager = NetworkManager::instance();
    ClickableLabel* thumbnailLabel;
    const Asset* asset = nullptr;
};

#endif // THUMBNAILWIDGET_H
