#include "thumbnailwidget.h"
#include "ui_thumbnailwidget.h"

ThumbnailWidget::ThumbnailWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThumbnailWidget)
{
    ui->setupUi(this);
}

void ThumbnailWidget::setThumbnailData(const ThumbnailData& data) {
    ui->thumbnailLabel->setPixmap(data.image);
    ui->nameLabel->setText(data.name);
    ui->descriptionLabel->setText(data.description);
    ui->dateLabel->setText(data.date.toString("yyyy-MM-dd"));
    ui->creatorLabel->setText(data.creator);
}

ThumbnailWidget::~ThumbnailWidget()
{
    delete ui;
}
