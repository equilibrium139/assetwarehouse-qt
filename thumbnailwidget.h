#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QDateTime>
#include <QPixmap>
#include <QString>
#include <QWidget>

namespace Ui {
class ThumbnailWidget;
}

struct ThumbnailData {
    QPixmap image;
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

protected:

private:
    Ui::ThumbnailWidget *ui;
};

#endif // THUMBNAILWIDGET_H
