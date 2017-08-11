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
    void resizeScene(int x, int y);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void setFocusBorder(bool b);
    void createMenuActions();
    void contextMenuEvent(QContextMenuEvent *event);

private:
    QImage* image;
    QGraphicsScene* scene;
    QTimer* timer;
    QMenu* menu;
    QAction* newTabAction;

signals:
    void newTabSignal();
    void focusOnSignal();
public slots:
    void emitNewTabSlot();
    void mouseClick();
};

#endif // IMAGEDISPLAY_H
