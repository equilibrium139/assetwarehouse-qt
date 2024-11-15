#include "thumbnailwidget.h"
#include "ui_thumbnailwidget.h"

#include <QNetworkReply>
#include <QImage>
#include <QPixmap>

ThumbnailWidget::ThumbnailWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThumbnailWidget)
{
    ui->setupUi(this);
}

void ThumbnailWidget::setThumbnailData(const Asset& asset) {
    ui->nameLabel->setText(asset.name);
    ui->descriptionLabel->setText(asset.description);
    ui->dateLabel->setText(asset.createdAt.toString("yyyy-MM-dd"));
    ui->creatorLabel->setText(asset.username);
    QNetworkReply* response = NetworkManager::getThumbnail(asset);
    connect(response, &QNetworkReply::finished, this, [response, this]() {
        if (response->error() == QNetworkReply::NoError) {
            QByteArray data = response->readAll();
            QImage image = QImage::fromData(data);
            ui->thumbnailLabel->setPixmap(QPixmap::fromImage(image));
        }
    });
}

ThumbnailWidget::~ThumbnailWidget()
{
    delete ui;
}
