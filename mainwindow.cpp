#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGridLayout>
#include <QScrollArea>
#include "thumbnailwidget.h"

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
    qInfo() << scrollWidget->size();

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
