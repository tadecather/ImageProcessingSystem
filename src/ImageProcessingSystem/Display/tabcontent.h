#ifndef TABCONTENT_H
#define TABCONTENT_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QUndoStack>
#include "imagedisplay.h"
#include "commandlabel.h"
#include "imagecommand.h"
#include "historyarea.h"

//包含在每个Tab标签页内，作为内容的类，计划中包含两个ImageDisplay对象和一个CommandHistory对象
class TabContent : public QWidget
{
    Q_OBJECT
public:
    TabContent(QWidget *parent, QImage *image);
    ~TabContent();
    ImageDisplay* getImageDisplayL();
    ImageDisplay* getImageDisplayR();
    void setImage(int LR, QImage* image);
    ImageDisplay* getFocusedImageDisplay();
    QImage* getFocusedImage();
    int getFocus();
    QUndoStack* getStack();
    void addLabel(CommandLabel* label);
    void popLabel();
    void redoLabel();
    void removeLabelAfterIndex(int index);
    std::vector<CommandLabel*> getLabels();

signals:

public slots:
    void changeFocusImageDisplaySlot();
private:
    ImageDisplay *imageDisplayL;
    ImageDisplay *imageDisplayR;
    QUndoStack* commandStack;
    QWidget* commandHistory;
    HistoryArea* historyArea;
    std::vector<CommandLabel*> labels;
    QHBoxLayout* historyLayout;
    //正在聚焦的imagedisplay对象，0左1右
    int focusOn;
};

#endif // TABCONTENT_H
