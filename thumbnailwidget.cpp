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
    thumbnailLabel = ui->thumbnailLabel;
    connect(thumbnailLabel, &ClickableLabel::clicked, this, &ThumbnailWidget::onThumbnailClicked);
}

void ThumbnailWidget::setThumbnailData(const Asset& asset) {
    this->asset = &asset;
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

void ThumbnailWidget::onThumbnailClicked() {
    assert(asset);
    emit clicked(*asset);
}

ThumbnailWidget::~ThumbnailWidget()
{
    delete ui;
}
