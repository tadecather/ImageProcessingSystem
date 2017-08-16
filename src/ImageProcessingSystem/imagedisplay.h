#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QWheelEvent>

//展示图片用的ImageDisplay类
class ImageDisplay : public QGraphicsView
{
    Q_OBJECT
public:
    ImageDisplay(QWidget * parent);
    ImageDisplay(QWidget * parent, QImage *image);
    ~ImageDisplay();
    void updateImage();
    void showNULL();
    QImage* getImage();
    void setImage(QImage* image);
    void newTab();
    void resize(double x, double y);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void setFocusBorder(bool b);
    void scaleToView(int viewWidth, int viewHeight);
    void createMenuActions();
    void contextMenuEvent(QContextMenuEvent *event);
    void wheelEvent(QWheelEvent* event);
    double getScaleRatio();
    void setScaleRatio(double s);

private:
    QImage* image;
    QGraphicsScene* scene;
    QTimer* timer;
    QMenu* menu;
    QAction* newTabAction;
    double scaleRatio;

signals:
    void newTabSignal();
    void focusOnSignal();
public slots:
    void emitNewTabSlot();
    void mouseClick();
};

#endif // IMAGEDISPLAY_H
