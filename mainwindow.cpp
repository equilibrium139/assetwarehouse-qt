#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGridLayout>
#include <QNetworkReply>
#include <QScrollArea>
#include "thumbnailwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), networkManager(new QNetworkAccessManager)
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
    qInfo() << scrollWidget->size();

    QNetworkRequest request(QUrl("https://assetwarehouse-backend-delta.vercel.app/api/assets/popular/50"));
    QNetworkReply* response = networkManager->get(request);
    connect(response, &QNetworkReply::finished, this, [=]() {
        if (response->error() == QNetworkReply::NoError) {
            QByteArray data = response->readAll();
            qInfo() << data;
        } else {
            qCritical() << "Error fetching assets: " << response->errorString();
        }
    });
    qInfo() << response->isFinished();

    std::vector<ThumbnailData> dummyData;
    dummyData.push_back({
        QPixmap("C:/dev/gltf-models/ABeautifulGame/screenshot/screenshot.jpg"),
        "Chess",
        "a beautiful game",
        "Equilibrium",
        QDateTime::currentDateTime()
    });
    dummyData.push_back({
        QPixmap("C:/dev/gltf-models/AlphaBlendModeTest/screenshot/BlendFail.jpg"),
        "Chess",
        "a beautiful game",
        "Equilibrium",
        QDateTime::currentDateTime()
    });
    dummyData.push_back({
        QPixmap("C:/dev/gltf-models/AlphaBlendModeTest/screenshot/BlendFail.jpg"),
        "Chess",
        "a beautiful game",
        "Equilibrium",
        QDateTime::currentDateTime()
    });
    dummyData.push_back({
        QPixmap("C:/dev/gltf-models/AlphaBlendModeTest/screenshot/BlendFail.jpg"),
        "Chess",
        "a beautiful game",
        "Equilibrium",
        QDateTime::currentDateTime()
    });
    dummyData.push_back({
        QPixmap("C:/dev/gltf-models/AlphaBlendModeTest/screenshot/BlendFail.jpg"),
        "Chess",
        "a beautiful game",
        "Equilibrium",
        QDateTime::currentDateTime()
    });
    dummyData.push_back({
        QPixmap("C:/dev/gltf-models/AlphaBlendModeTest/screenshot/BlendFail.jpg"),
        "Chess",
        "a beautiful game",
        "Equilibrium",
        QDateTime::currentDateTime()
    });

    const int columns = 3;
    for (int i = 0; i < dummyData.size(); i++) {
        ThumbnailWidget* tw = new ThumbnailWidget();
        tw->setThumbnailData(dummyData[i]);
        int row = i / columns;
        int col = i % columns;
        scrollAreaLayout->addWidget(tw, row, col);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
