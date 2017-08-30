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
        ImageCommands/gnoisecommand.cpp \
        Display/gnoiseargsdialog.cpp \
        ImageCommands/spnoisecommand.cpp \
        Display/spnoiseargsdialog.cpp \
        Algorithms/dct.cpp \
    	Algorithms/imagesegmentation.cpp \
    	Display/graydialog.cpp \
        ImageCommands/mediansmoothcommand.cpp \
        ImageCommands/meansmoothcommand.cpp \
        Display/weightedsmoothargsdialog.cpp \
        ImageCommands/weightedsmoothcommand.cpp \
        Display/meansmoothargsdialog.cpp \
        ImageCommands/selectivemasksmooothcommand.cpp \
        Display/tdpdialog.cpp \
        Display/customedge.cpp \
        ImageCommands/segmentationcommand.cpp \
    	ImageCommands/tdpcommand.cpp \
        ImageCommands/grayscommand.cpp \
        ImageCommands/gradientsharpencommand.cpp \
        Display/gradientsharpendialog.cpp \
        ImageCommands/laplaciansharpencommand.cpp \
        Display/laplaciansharpendialog.cpp \
        ImageCommands/boundarytrackcommand.cpp \
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
        ImageCommands/gnoisecommand.h \
        Display/gnoiseargsdialog.h \
        ImageCommands/spnoisecommand.h \
        Display/spnoiseargsdialog.h \
        Algorithms/dct.h \
        Algorithms/imagesegmentation.h \
        Display/graydialog.h \
        ImageCommands/mediansmoothcommand.h \
        ImageCommands/meansmoothcommand.h \
        Display/weightedsmoothargsdialog.h \
        ImageCommands/weightedsmoothcommand.h \
        Display/meansmoothargsdialog.h \
        ImageCommands/selectivemasksmooothcommand.h \
    Display/tdpdialog.h \
    Display/customedge.h \
    ImageCommands/segmentationcommand.h \
    	ImageCommands/tdpcommand.h \
        ImageCommands/grayscommand.h \
        ImageCommands/gradientsharpencommand.h \
        Display/gradientsharpendialog.h \
        ImageCommands/laplaciansharpencommand.h \
        Display/laplaciansharpendialog.h \
        ImageCommands/boundarytrackcommand.h \
    ImageCommands/transcommand.h


FORMS    += mainwindow.ui

INCLUDEPATH += Algorithms/
INCLUDEPATH += Display/
INCLUDEPATH += ImageCommands/
INCLUDEPATH += Utilities/


RC_FILE = Resource/IPS.rc


