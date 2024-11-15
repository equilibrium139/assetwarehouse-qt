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

void ThumbnailWidget::setThumbnailData(const ThumbnailData& data) {
    QNetworkRequest request{QUrl(data.imageUrl)};
    QNetworkReply* response = networkManager->get(request);
    connect(response, &QNetworkReply::finished, this, [response, this]() {
        if (response->error() == QNetworkReply::NoError) {
            QByteArray data = response->readAll();
            QImage image = QImage::fromData(data);
            ui->thumbnailLabel->setPixmap(QPixmap::fromImage(image));
        }
    });
    ui->nameLabel->setText(data.name);
    ui->descriptionLabel->setText(data.description);
    ui->dateLabel->setText(data.date.toString("yyyy-MM-dd"));
    ui->creatorLabel->setText(data.creator);
}

ThumbnailWidget::~ThumbnailWidget()
{
    delete ui;
}
