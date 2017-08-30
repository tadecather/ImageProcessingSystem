#-------------------------------------------------
#
# Project created by QtCreator 2017-08-09T09:47:22
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessingSystem
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
        Display/imagedisplay.cpp \
        Display/mytabwidget.cpp \
        Display/tabcontent.cpp \
        Utilities/fileoperation.cpp \
        Utilities/imagtranslate.cpp \
        Algorithms/imagetrans.cpp\
        Algorithms/imagegray.cpp \
        Display/commandlabel.cpp \
        ImageCommands/imagecommand.cpp \
        Algorithms/imgtransformdomainprocessing.cpp\
        ImageCommands/examplecommand.cpp \
        Display\historyarea.cpp \
        Algorithms/imageenhancement.cpp \
        Display/gnoiseargsdialog.cpp \
        ImageCommands/spnoisecommand.cpp \
        Display/spnoiseargsdialog.cpp \
        Algorithms/dct.cpp \
    	Algorithms/imagesegmentation.cpp \
    	Display/graydialog.cpp \
        Display/weightedsmoothargsdialog.cpp \
        Display/meansmoothargsdialog.cpp \
        Display/tdpdialog.cpp \
        Display/customedge.cpp \
        ImageCommands/segmentationcommand.cpp \
    	ImageCommands/tdpcommand.cpp \
        ImageCommands/grayscommand.cpp \
        Display/gradientsharpendialog.cpp \
        Display/laplaciansharpendialog.cpp \
    ImageCommands/enhancementcommand.cpp \
    ImageCommands/transcommand.cpp








HEADERS  += mainwindow.h \
        Display/imagedisplay.h \
        Display/mytabwidget.h \
        Display/tabcontent.h \
        Utilities/fileoperation.h \
        Utilities/imagtranslate.h \
        Algorithms/imagegray.h \
        Algorithms/imagetrans.h\
        Display/commandlabel.h \
        ImageCommands/imagecommand.h \
        Algorithms/imgtransformdomainprocessing.h\
        ImageCommands/examplecommand.h \
        Display/historyarea.h \
        Algorithms/imageenhancement.h \
        Display/gnoiseargsdialog.h \
        ImageCommands/spnoisecommand.h \
        Display/spnoiseargsdialog.h \
        Algorithms/dct.h \
        Algorithms/imagesegmentation.h \
        Display/graydialog.h \
        Display/weightedsmoothargsdialog.h \
        Display/meansmoothargsdialog.h \
    Display/tdpdialog.h \
    Display/customedge.h \
    ImageCommands/segmentationcommand.h \
    	ImageCommands/tdpcommand.h \
        ImageCommands/grayscommand.h \
        Display/gradientsharpendialog.h \
        Display/laplaciansharpendialog.h \
    ImageCommands/enhancementcommand.h \
    ImageCommands/transcommand.h


FORMS    += mainwindow.ui

INCLUDEPATH += Algorithms/
INCLUDEPATH += Display/
INCLUDEPATH += ImageCommands/
INCLUDEPATH += Utilities/


RC_FILE = Resource/IPS.rc


