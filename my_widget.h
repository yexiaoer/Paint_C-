#include <qmainwindow.h>
#include <qmessagebox.h>
//#include <qpopupmenu.h>
#include <QMenu>
#include <qmenubar.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <QToolBar>
#include <QAction>
#include <QPen>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QImage>
#include <QInputDialog>
#include <QColorDialog>
//#include <QDialogButtonBox>
#include <QSlider>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPixmap>
#include <Qt>
#include <QPolygon>
#include <QBrush>
#include <QPainterPath>
#include <QVector>
#include <QPoint>


#ifndef _MY_WIDGET_H
#define _MY_WIDGET_H

class MyMainWindow: public QMainWindow {
	// All classes that contain signals or slots
	// must mention Q_OBJECT in their declaration.
	Q_OBJECT

	public:
	MyMainWindow(QWidget* parent = 0, const char* name = 0);
	~MyMainWindow();

	/** mouse event handler */
    void mousePressEvent (QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);
    void mouseReleaseEvent (QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent * e);


	/** paint handler */
	void paintEvent(QPaintEvent *);

    public slots:
    void initial();
    void clearImage();
    void newImage();
    void loadImage();
    void saveImage();
    void resizeImage();
    void undoAction();
    void redoAction();
    void line();
    void eraser();
    void pen();
    void rect();
    void exit();

    void setBackgroundColor();
    void setForegroundColor();

    void setPen();
    void setEraser();
    void setLine();

    void setEraserSize(int);
    void setPenSize(int);
    void setPenStyle(int);



    void setLineSize(int);
    void setLineCapStyle(int);
    void setLineStyle(int);
    void setLineType(int);

    void rectStyle(int);
    void rectShapeType(int);
    void rectType(int);
    void rectFillColor(int);
    void lineRect(int);
    void curveRect(int);

    void setRect();

	private:
   // QPixmap* image;
    QPainter *painter;

    //QImage *image;
    QPixmap *image;
    QPixmap *redoImage;
    QPixmap *undoImage;
    QPixmap *temp;
    QPixmap *tempResize;

    QPoint pBegin;
    QPoint pEnd;

    bool pEnabled;
    bool polyMode;

    bool rectSolid;
    bool rectDashed;
    bool rectDotted;
    bool rectDashDotted;
    bool rectDashDotDotted;

    bool rectMJ;
    bool rectBJ;
    bool rectRJ;
    bool rectNoFillClick;
    bool rectForeClick;
    bool rectBackClick;
    bool roundedRectClick;
    bool rectangleClick;
    bool ellipseClick;

    bool lineSolid;
    bool lineDashed;
    bool lineDotted;
    bool lineDashDotted;
    bool lineDashDotDotted;

    bool lineFlat;
    bool lineSquare;
    bool lineRound;

    bool lineSingle;
    bool linePoly;

    bool penFlat;
    bool penSquare;
    bool penRound;



    QPen penQ;
    QPen eraserQ;
    QPen rectQ;
    QPen lineQ;
    bool penClick;
    bool eraserClick;
    bool rectClick;
    bool lineClick;
    int width;
    int height;
    int roundedSize;
    int numPoints;

    QAction *newFile;
    QAction *openFile;
    QAction *saveFile;
    QAction *undo;
    QAction *redo;
    QAction *clear;
    QAction *resize;
    QAction *fcolor;
    QAction *bcolor;
    QAction *penAction;
    QAction *lineAction;
    QAction *eraserAction;
    QAction *rectAction;

    QDialog *eraserDialog;
    QDialog *penDialog;
    QDialog *lineDialog;
    QDialog *rectDialog;

    QSlider *slider1;
    QSlider *slider2;
    QSlider *slider3;
    QSlider *slider4;

    QLabel *text1;
    QLabel *text2;
    QLabel *text3;
    QLabel *text4;
    QLabel *text5;
    QLabel *text6;

    QRadioButton *flat;
    QRadioButton *square;
    QRadioButton *round;

    QRadioButton *solid;
    QRadioButton *dashed;
    QRadioButton *dotted;
    QRadioButton *dashDotted;
    QRadioButton *dashDotDotted;

    QRadioButton *single;
    QRadioButton *poly;

    QRadioButton *rectangle;
    QRadioButton *roundedRect;
    QRadioButton *elipse;

    QRadioButton *foreground;
    QRadioButton *background;
    QRadioButton *nofill;

    QRadioButton *miterJ;
    QRadioButton *bevelJ;
    QRadioButton *roundJ;

    QButtonGroup *penButton;
    QButtonGroup *lineButton;
    QButtonGroup *typeButton;

    QButtonGroup *styleRect;
    QButtonGroup *shapeRect;
    QButtonGroup *fillRect;
    QButtonGroup *typeRect;


    QColor backgroundColor;
    QColor foregroundColor;
    //QPolygon *polygon;
    //QVector<QPoint> list;

};

#endif
