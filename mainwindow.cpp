#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGridLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkReply>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(ui->centralwidget);

    QScrollArea* scrollArea = new QScrollArea(ui->centralwidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    QWidget* scrollWidget = new QWidget();
    scrollWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scrollArea->setWidget(scrollWidget);

    QGridLayout* scrollAreaLayout = new QGridLayout(scrollWidget);
    scrollAreaLayout->setHorizontalSpacing(0);

    QNetworkRequest request(QUrl("https://assetwarehouse-backend-delta.vercel.app/api/assets/popular/50"));
    QNetworkReply* response = networkManager->get(request);
    connect(response, &QNetworkReply::finished, this, [=]() {
        if (response->error() == QNetworkReply::NoError) {
            QByteArray data = response->readAll();
            QJsonDocument json = QJsonDocument::fromJson(data);
            QJsonArray array = json.array();
            int assetCount = array.count();
            thumbnailData.reserve(assetCount);
            for (int i = 0; i < assetCount; i++) {
                QJsonValue value = array[i];
                QJsonObject object = value.toObject();
                QString name = object.value("name").toString();
                QString description = object.value("description").toString();
                QString creator = object.value("username").toString();
                QString dateStr = object.value("created_at").toString();
                QDateTime date = QDateTime::fromString(dateStr, Qt::ISODateWithMs);
                QDateTime localDate = date.toLocalTime();
                QString thumbnailUrl = object.value("thumbnail_url").toString();
                int creatorID = object.value("created_by").toInt();
                QString creatorIDStr = QString::number(creatorID);
                thumbnailUrl = "https://assetwarehouse.nyc3.digitaloceanspaces.com/thumbnails/" + creatorIDStr + "/" + thumbnailUrl;
                qInfo() << thumbnailUrl;
                const int columns = 3;
                thumbnailData.push_back({
                    thumbnailUrl,
                    name,
                    description,
                    creator,
                    localDate
                });
                ThumbnailWidget* tw = new ThumbnailWidget();
                tw->setThumbnailData(thumbnailData.back());
                int row = i / columns;
                int col = i % columns;
                scrollAreaLayout->addWidget(tw, row, col);
            }
        } else {
            qCritical() << "Error fetching assets: " << response->errorString();
        }
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
