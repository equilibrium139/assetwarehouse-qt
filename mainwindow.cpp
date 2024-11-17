#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "assetviewer.h"
#include "thumbnailwidget.h"

#include <QDialog>
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
            galleryAssets.reserve(assetCount);
            const int columns = 3;
            for (int i = 0; i < assetCount; i++) {
                QJsonValue value = array[i];
                QJsonObject object = value.toObject();
                galleryAssets.push_back(object);
                ThumbnailWidget* tw = new ThumbnailWidget();
                tw->setThumbnailData(galleryAssets.back());
                connect(tw, &ThumbnailWidget::clicked, this, &MainWindow::onAssetClicked);
                int row = i / columns;
                int col = i % columns;
                scrollAreaLayout->addWidget(tw, row, col);
            }
        } else {
            qCritical() << "Error fetching assets: " << response->errorString();
        }
    });
}

void MainWindow::onAssetClicked(const Asset& asset) {
    QDialog* dialog = new QDialog(nullptr);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle("Asset Viewer");

    AssetViewer* viewer = new AssetViewer(dialog);

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(viewer);
    viewer->setFocusPolicy(Qt::StrongFocus);
    viewer->setFocus();

    dialog->resize(800, 600);
    dialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
