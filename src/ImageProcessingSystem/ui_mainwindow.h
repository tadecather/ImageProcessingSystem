/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionPrint;
    QAction *actionPrint_preview;
    QAction *actionRecent_file;
    QAction *actionExit;
    QAction *actionGraying;
    QAction *actionGray_to_Clolr;
    QAction *actionNegetive;
    QAction *actionBinaryzation;
    QAction *actionLinear_Stretch;
    QAction *actionExponential_Stretch;
    QAction *actionLogarithmic_Stretch;
    QAction *actionPlot_Histogram;
    QAction *actionBalance_Histogram;
    QAction *actionTranslation;
    QAction *actionTranspose;
    QAction *actionHorizontal_Inversion;
    QAction *actionVertical_Inversion;
    QAction *actionZoom;
    QAction *actionClockwise_Rotation;
    QAction *actionAnticlockwise_Rotation;
    QAction *actionFourier_transform;
    QAction *actionWavelet_Transform;
    QAction *actionDiscrete_Cosine_Transform;
    QAction *actionOtsu_Law_Threshold_Segmentation;
    QAction *actionInteractive_Threshold_Segmentation;
    QAction *actionRobert_Operator;
    QAction *actionSobel_Operator;
    QAction *actionPrewitt_Operator;
    QAction *actionLaplacian_Operator;
    QAction *actionGauss_Laplacian_Operator;
    QAction *actionKrisch_Operator;
    QAction *actionCustom_Edges;
    QAction *actionRegion_Grow;
    QAction *actionContour_Extraction;
    QAction *actionBoundary_Tracking;
    QAction *actionHough_Transformation;
    QAction *actionHough_Transformation_Line_Detection;
    QAction *actionGaussian_Noise;
    QAction *actionSalt_and_Pepper_Noise;
    QAction *actionMean_Smoothing;
    QAction *actionMedian_Smoothing;
    QAction *actionWeighted_Smoothing;
    QAction *actionChoose_Mask_Smoothing;
    QAction *actionGradient_Sharpening;
    QAction *actionLaplacian_Sharpening;
    QAction *actionImage_Quality_Assessment;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuGrey;
    QMenu *menuTransformation;
    QMenu *menuTdp;
    QMenu *menuDivision;
    QMenu *menuEnhancement;
    QMenu *menuANN;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        actionPrint_preview = new QAction(MainWindow);
        actionPrint_preview->setObjectName(QStringLiteral("actionPrint_preview"));
        actionRecent_file = new QAction(MainWindow);
        actionRecent_file->setObjectName(QStringLiteral("actionRecent_file"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionGraying = new QAction(MainWindow);
        actionGraying->setObjectName(QStringLiteral("actionGraying"));
        actionGray_to_Clolr = new QAction(MainWindow);
        actionGray_to_Clolr->setObjectName(QStringLiteral("actionGray_to_Clolr"));
        actionNegetive = new QAction(MainWindow);
        actionNegetive->setObjectName(QStringLiteral("actionNegetive"));
        actionBinaryzation = new QAction(MainWindow);
        actionBinaryzation->setObjectName(QStringLiteral("actionBinaryzation"));
        actionLinear_Stretch = new QAction(MainWindow);
        actionLinear_Stretch->setObjectName(QStringLiteral("actionLinear_Stretch"));
        actionExponential_Stretch = new QAction(MainWindow);
        actionExponential_Stretch->setObjectName(QStringLiteral("actionExponential_Stretch"));
        actionLogarithmic_Stretch = new QAction(MainWindow);
        actionLogarithmic_Stretch->setObjectName(QStringLiteral("actionLogarithmic_Stretch"));
        actionPlot_Histogram = new QAction(MainWindow);
        actionPlot_Histogram->setObjectName(QStringLiteral("actionPlot_Histogram"));
        actionBalance_Histogram = new QAction(MainWindow);
        actionBalance_Histogram->setObjectName(QStringLiteral("actionBalance_Histogram"));
        actionTranslation = new QAction(MainWindow);
        actionTranslation->setObjectName(QStringLiteral("actionTranslation"));
        actionTranspose = new QAction(MainWindow);
        actionTranspose->setObjectName(QStringLiteral("actionTranspose"));
        actionHorizontal_Inversion = new QAction(MainWindow);
        actionHorizontal_Inversion->setObjectName(QStringLiteral("actionHorizontal_Inversion"));
        actionVertical_Inversion = new QAction(MainWindow);
        actionVertical_Inversion->setObjectName(QStringLiteral("actionVertical_Inversion"));
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionClockwise_Rotation = new QAction(MainWindow);
        actionClockwise_Rotation->setObjectName(QStringLiteral("actionClockwise_Rotation"));
        actionAnticlockwise_Rotation = new QAction(MainWindow);
        actionAnticlockwise_Rotation->setObjectName(QStringLiteral("actionAnticlockwise_Rotation"));
        actionFourier_transform = new QAction(MainWindow);
        actionFourier_transform->setObjectName(QStringLiteral("actionFourier_transform"));
        actionWavelet_Transform = new QAction(MainWindow);
        actionWavelet_Transform->setObjectName(QStringLiteral("actionWavelet_Transform"));
        actionDiscrete_Cosine_Transform = new QAction(MainWindow);
        actionDiscrete_Cosine_Transform->setObjectName(QStringLiteral("actionDiscrete_Cosine_Transform"));
        actionOtsu_Law_Threshold_Segmentation = new QAction(MainWindow);
        actionOtsu_Law_Threshold_Segmentation->setObjectName(QStringLiteral("actionOtsu_Law_Threshold_Segmentation"));
        actionInteractive_Threshold_Segmentation = new QAction(MainWindow);
        actionInteractive_Threshold_Segmentation->setObjectName(QStringLiteral("actionInteractive_Threshold_Segmentation"));
        actionRobert_Operator = new QAction(MainWindow);
        actionRobert_Operator->setObjectName(QStringLiteral("actionRobert_Operator"));
        actionSobel_Operator = new QAction(MainWindow);
        actionSobel_Operator->setObjectName(QStringLiteral("actionSobel_Operator"));
        actionPrewitt_Operator = new QAction(MainWindow);
        actionPrewitt_Operator->setObjectName(QStringLiteral("actionPrewitt_Operator"));
        actionLaplacian_Operator = new QAction(MainWindow);
        actionLaplacian_Operator->setObjectName(QStringLiteral("actionLaplacian_Operator"));
        actionGauss_Laplacian_Operator = new QAction(MainWindow);
        actionGauss_Laplacian_Operator->setObjectName(QStringLiteral("actionGauss_Laplacian_Operator"));
        actionKrisch_Operator = new QAction(MainWindow);
        actionKrisch_Operator->setObjectName(QStringLiteral("actionKrisch_Operator"));
        actionCustom_Edges = new QAction(MainWindow);
        actionCustom_Edges->setObjectName(QStringLiteral("actionCustom_Edges"));
        actionRegion_Grow = new QAction(MainWindow);
        actionRegion_Grow->setObjectName(QStringLiteral("actionRegion_Grow"));
        actionContour_Extraction = new QAction(MainWindow);
        actionContour_Extraction->setObjectName(QStringLiteral("actionContour_Extraction"));
        actionBoundary_Tracking = new QAction(MainWindow);
        actionBoundary_Tracking->setObjectName(QStringLiteral("actionBoundary_Tracking"));
        actionHough_Transformation = new QAction(MainWindow);
        actionHough_Transformation->setObjectName(QStringLiteral("actionHough_Transformation"));
        actionHough_Transformation_Line_Detection = new QAction(MainWindow);
        actionHough_Transformation_Line_Detection->setObjectName(QStringLiteral("actionHough_Transformation_Line_Detection"));
        actionGaussian_Noise = new QAction(MainWindow);
        actionGaussian_Noise->setObjectName(QStringLiteral("actionGaussian_Noise"));
        actionSalt_and_Pepper_Noise = new QAction(MainWindow);
        actionSalt_and_Pepper_Noise->setObjectName(QStringLiteral("actionSalt_and_Pepper_Noise"));
        actionMean_Smoothing = new QAction(MainWindow);
        actionMean_Smoothing->setObjectName(QStringLiteral("actionMean_Smoothing"));
        actionMedian_Smoothing = new QAction(MainWindow);
        actionMedian_Smoothing->setObjectName(QStringLiteral("actionMedian_Smoothing"));
        actionWeighted_Smoothing = new QAction(MainWindow);
        actionWeighted_Smoothing->setObjectName(QStringLiteral("actionWeighted_Smoothing"));
        actionChoose_Mask_Smoothing = new QAction(MainWindow);
        actionChoose_Mask_Smoothing->setObjectName(QStringLiteral("actionChoose_Mask_Smoothing"));
        actionGradient_Sharpening = new QAction(MainWindow);
        actionGradient_Sharpening->setObjectName(QStringLiteral("actionGradient_Sharpening"));
        actionLaplacian_Sharpening = new QAction(MainWindow);
        actionLaplacian_Sharpening->setObjectName(QStringLiteral("actionLaplacian_Sharpening"));
        actionImage_Quality_Assessment = new QAction(MainWindow);
        actionImage_Quality_Assessment->setObjectName(QStringLiteral("actionImage_Quality_Assessment"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuGrey = new QMenu(menubar);
        menuGrey->setObjectName(QStringLiteral("menuGrey"));
        menuTransformation = new QMenu(menubar);
        menuTransformation->setObjectName(QStringLiteral("menuTransformation"));
        menuTdp = new QMenu(menubar);
        menuTdp->setObjectName(QStringLiteral("menuTdp"));
        menuDivision = new QMenu(menubar);
        menuDivision->setObjectName(QStringLiteral("menuDivision"));
        menuEnhancement = new QMenu(menubar);
        menuEnhancement->setObjectName(QStringLiteral("menuEnhancement"));
        menuANN = new QMenu(menubar);
        menuANN->setObjectName(QStringLiteral("menuANN"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuGrey->menuAction());
        menubar->addAction(menuTransformation->menuAction());
        menubar->addAction(menuTdp->menuAction());
        menubar->addAction(menuDivision->menuAction());
        menubar->addAction(menuEnhancement->menuAction());
        menubar->addAction(menuANN->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addAction(actionPrint_preview);
        menuFile->addSeparator();
        menuFile->addAction(actionRecent_file);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuGrey->addAction(actionGraying);
        menuGrey->addAction(actionGray_to_Clolr);
        menuGrey->addSeparator();
        menuGrey->addAction(actionNegetive);
        menuGrey->addAction(actionBinaryzation);
        menuGrey->addSeparator();
        menuGrey->addAction(actionLinear_Stretch);
        menuGrey->addAction(actionExponential_Stretch);
        menuGrey->addAction(actionLogarithmic_Stretch);
        menuGrey->addSeparator();
        menuGrey->addAction(actionPlot_Histogram);
        menuGrey->addAction(actionBalance_Histogram);
        menuTransformation->addAction(actionTranslation);
        menuTransformation->addAction(actionTranspose);
        menuTransformation->addSeparator();
        menuTransformation->addAction(actionHorizontal_Inversion);
        menuTransformation->addAction(actionVertical_Inversion);
        menuTransformation->addSeparator();
        menuTransformation->addAction(actionZoom);
        menuTransformation->addSeparator();
        menuTransformation->addAction(actionClockwise_Rotation);
        menuTransformation->addAction(actionAnticlockwise_Rotation);
        menuTdp->addAction(actionFourier_transform);
        menuTdp->addAction(actionWavelet_Transform);
        menuTdp->addAction(actionDiscrete_Cosine_Transform);
        menuDivision->addAction(actionOtsu_Law_Threshold_Segmentation);
        menuDivision->addAction(actionInteractive_Threshold_Segmentation);
        menuDivision->addSeparator();
        menuDivision->addAction(actionRobert_Operator);
        menuDivision->addAction(actionSobel_Operator);
        menuDivision->addAction(actionPrewitt_Operator);
        menuDivision->addAction(actionLaplacian_Operator);
        menuDivision->addAction(actionGauss_Laplacian_Operator);
        menuDivision->addAction(actionKrisch_Operator);
        menuDivision->addAction(actionCustom_Edges);
        menuDivision->addSeparator();
        menuDivision->addAction(actionRegion_Grow);
        menuDivision->addAction(actionContour_Extraction);
        menuDivision->addAction(actionBoundary_Tracking);
        menuDivision->addSeparator();
        menuDivision->addAction(actionHough_Transformation);
        menuDivision->addAction(actionHough_Transformation_Line_Detection);
        menuEnhancement->addAction(actionGaussian_Noise);
        menuEnhancement->addAction(actionSalt_and_Pepper_Noise);
        menuEnhancement->addSeparator();
        menuEnhancement->addAction(actionMean_Smoothing);
        menuEnhancement->addAction(actionMedian_Smoothing);
        menuEnhancement->addAction(actionWeighted_Smoothing);
        menuEnhancement->addAction(actionChoose_Mask_Smoothing);
        menuEnhancement->addSeparator();
        menuEnhancement->addAction(actionGradient_Sharpening);
        menuEnhancement->addAction(actionLaplacian_Sharpening);
        menuEnhancement->addSeparator();
        menuEnhancement->addAction(actionImage_Quality_Assessment);

        retranslateUi(MainWindow);



        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as", 0));
        actionPrint->setText(QApplication::translate("MainWindow", "Print", 0));
        actionPrint_preview->setText(QApplication::translate("MainWindow", "Print Preview", 0));
        actionRecent_file->setText(QApplication::translate("MainWindow", "Open Recent", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionGraying->setText(QApplication::translate("MainWindow", "Color to Gray", 0));
        actionGray_to_Clolr->setText(QApplication::translate("MainWindow", "Gray to Color", 0));
        actionNegetive->setText(QApplication::translate("MainWindow", "Negetive", 0));
        actionBinaryzation->setText(QApplication::translate("MainWindow", "Binaryzation", 0));
        actionLinear_Stretch->setText(QApplication::translate("MainWindow", "Linear Stretch", 0));
        actionExponential_Stretch->setText(QApplication::translate("MainWindow", "Exponential Stretch", 0));
        actionLogarithmic_Stretch->setText(QApplication::translate("MainWindow", "Logarithmic Stretch", 0));
        actionPlot_Histogram->setText(QApplication::translate("MainWindow", "Plot Histogram", 0));
        actionBalance_Histogram->setText(QApplication::translate("MainWindow", "Balance Histogram", 0));
        actionTranslation->setText(QApplication::translate("MainWindow", "Translation", 0));
        actionTranspose->setText(QApplication::translate("MainWindow", "Transpose", 0));
        actionHorizontal_Inversion->setText(QApplication::translate("MainWindow", "Horizontal Inversion", 0));
        actionVertical_Inversion->setText(QApplication::translate("MainWindow", "Vertical Inversion", 0));
        actionZoom->setText(QApplication::translate("MainWindow", "Zoom", 0));
        actionClockwise_Rotation->setText(QApplication::translate("MainWindow", "Clockwise Rotation", 0));
        actionAnticlockwise_Rotation->setText(QApplication::translate("MainWindow", "Anticlockwise Rotation", 0));
        actionFourier_transform->setText(QApplication::translate("MainWindow", "Fourier Transform", 0));
        actionWavelet_Transform->setText(QApplication::translate("MainWindow", "Wavelet Transform", 0));
        actionDiscrete_Cosine_Transform->setText(QApplication::translate("MainWindow", "Discrete Cosine Transform", 0));
        actionOtsu_Law_Threshold_Segmentation->setText(QApplication::translate("MainWindow", "Otsu Law Threshold Segmentation", 0));
        actionInteractive_Threshold_Segmentation->setText(QApplication::translate("MainWindow", "Interactive Threshold Segmentation", 0));
        actionRobert_Operator->setText(QApplication::translate("MainWindow", "Robert Operator", 0));
        actionSobel_Operator->setText(QApplication::translate("MainWindow", "Sobel Operator", 0));
        actionPrewitt_Operator->setText(QApplication::translate("MainWindow", "Prewitt Operator", 0));
        actionLaplacian_Operator->setText(QApplication::translate("MainWindow", "Laplacian Operator", 0));
        actionGauss_Laplacian_Operator->setText(QApplication::translate("MainWindow", "Gauss-Laplacian Operator", 0));
        actionKrisch_Operator->setText(QApplication::translate("MainWindow", "Krisch Operator", 0));
        actionCustom_Edges->setText(QApplication::translate("MainWindow", "Custom Edges", 0));
        actionRegion_Grow->setText(QApplication::translate("MainWindow", "Region Growing", 0));
        actionContour_Extraction->setText(QApplication::translate("MainWindow", "Contour Extraction", 0));
        actionBoundary_Tracking->setText(QApplication::translate("MainWindow", "Boundary Tracking", 0));
        actionHough_Transformation->setText(QApplication::translate("MainWindow", "Hough Transformation", 0));
        actionHough_Transformation_Line_Detection->setText(QApplication::translate("MainWindow", "Hough Transformation Line Detection", 0));
        actionGaussian_Noise->setText(QApplication::translate("MainWindow", "Gaussian Noise", 0));
        actionSalt_and_Pepper_Noise->setText(QApplication::translate("MainWindow", "Salt-and-Pepper Noise", 0));
        actionMean_Smoothing->setText(QApplication::translate("MainWindow", "Mean Smoothing", 0));
        actionMedian_Smoothing->setText(QApplication::translate("MainWindow", "Median Smoothing", 0));
        actionWeighted_Smoothing->setText(QApplication::translate("MainWindow", "Weighted Smoothing", 0));
        actionChoose_Mask_Smoothing->setText(QApplication::translate("MainWindow", "Choose Mask Smoothing", 0));
        actionGradient_Sharpening->setText(QApplication::translate("MainWindow", "Gradient Sharpening", 0));
        actionLaplacian_Sharpening->setText(QApplication::translate("MainWindow", "Laplacian Sharpening", 0));
        actionImage_Quality_Assessment->setText(QApplication::translate("MainWindow", "Image Quality Assessment", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuGrey->setTitle(QApplication::translate("MainWindow", "Gray", 0));
        menuTransformation->setTitle(QApplication::translate("MainWindow", "Transformation", 0));
        menuTdp->setTitle(QApplication::translate("MainWindow", "TDP", 0));
        menuDivision->setTitle(QApplication::translate("MainWindow", "Segmentation", 0));
        menuEnhancement->setTitle(QApplication::translate("MainWindow", "Enhancement", 0));
        menuANN->setTitle(QApplication::translate("MainWindow", "ANN", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
