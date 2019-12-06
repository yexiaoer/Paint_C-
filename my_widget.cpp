#include <iostream>
using namespace std;

#include "my_widget.h"

#include <qfiledialog.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <QMenuBar>


MyMainWindow::MyMainWindow(QWidget* parent, const char* name)
:QMainWindow(parent)
{

    this->setFixedSize(1000, 1000);
    QMenu* file = new QMenu("File", this);
    file->addAction("New Image", this, SLOT(newImage()));
    file->addAction("Load Image", this, SLOT(loadImage()));
    file->addAction("Save Image", this, SLOT(saveImage()));
    file->addAction("Exit", this, SLOT(exit()));

    menuBar()->addMenu(file);

    QMenu* edit = new QMenu("Edit", this);
    edit->addAction("Undo", this, SLOT(undoAction()));
    edit->addAction("Redo", this, SLOT(redoAction()));
    edit->addAction("Foreground Color", this, SLOT(setForegroundColor()));
    edit->addAction("Background Color", this, SLOT(setBackgroundColor()));
    menuBar()->addMenu(edit);

    QMenu* tools = new QMenu("Tools", this);
    tools->addAction("Line", this, SLOT(line()));
    tools->addAction("Pen", this, SLOT(pen()));
    tools->addAction("Rectangle", this, SLOT(rect()));
    menuBar()->addMenu(tools);

    QPixmap newpix("/home/wenxiu/bitmap/icon/new_icon.bmp");
    QPixmap openpix("/home/wenxiu/bitmap/icon/open_icon.bmp");
    QPixmap savepix("/home/wenxiu/bitmap/icon/save_icon.bmp");
    QPixmap undopix("/home/wenxiu/bitmap/icon/undo_icon.bmp");
    QPixmap redopix("/home/wenxiu/bitmap/icon/redo_icon.bmp");
    QPixmap clearallpix("/home/wenxiu/bitmap/icon/clearall_icon.bmp");
    QPixmap resizepix("/home/wenxiu/bitmap/icon/resize_icon.bmp");
    QPixmap fcolorpix("/home/wenxiu/bitmap/icon/fcolor_icon.bmp");
    QPixmap bcolorpix("/home/wenxiu/bitmap/icon/bcolor_icon.bmp");
    QPixmap penpix("/home/wenxiu/bitmap/icon/pen_icon.bmp");
    QPixmap linepix("/home/wenxiu/bitmap/icon/line_icon.bmp");
    QPixmap eraserpix("/home/wenxiu/bitmap/icon/eraser_icon.bmp");
    QPixmap rectpix("/home/wenxiu/bitmap/icon/rect_icon.bmp");
    //QPixmap quitpix("quit.png");

    QToolBar *toolbar = addToolBar("main toolbar");

    newFile = new QAction(QIcon(newpix), tr("New File"), this);
    toolbar->addAction(newFile);
    connect(newFile, SIGNAL(triggered()), SLOT(newImage()));

    openFile = new QAction(QIcon(openpix), tr("Open File"), this);
    toolbar->addAction(openFile);
    connect(openFile, SIGNAL(triggered()), SLOT(loadImage()));

    saveFile = new QAction(QIcon(savepix), tr("Save File"), this);
    toolbar->addAction(saveFile);
    connect(saveFile, SIGNAL(triggered()), SLOT(saveImage()));

    undo = new QAction(QIcon(undopix), tr("Undo"), this);
    toolbar->addAction(undo);
    connect(undo, SIGNAL(triggered()), SLOT(undoAction()));

    redo = new QAction(QIcon(redopix), tr("Redo"), this);
    toolbar->addAction(redo);
    connect(redo, SIGNAL(triggered()), SLOT(redoAction()));

    clear = new QAction(QIcon(clearallpix), tr("Clear"), this);
    toolbar->addAction(clear);
    connect(clear, SIGNAL(triggered()), SLOT(clearImage()));

    resize = new QAction(QIcon(resizepix), tr("Resize"), this);
    toolbar->addAction(resize);
    connect(resize, SIGNAL(triggered()), SLOT(resizeImage()));

    fcolor = new QAction(QIcon(fcolorpix), tr("Foreground Color"), this);
    toolbar->addAction(fcolor);
    connect(fcolor, SIGNAL(triggered()), SLOT(setForegroundColor()));

    bcolor = new QAction(QIcon(bcolorpix), tr("Background Color"), this);
    toolbar->addAction(bcolor);
    connect(bcolor, SIGNAL(triggered()), SLOT(setBackgroundColor()));

    penAction = new QAction(QIcon(penpix), tr("Pen"), this);
    toolbar->addAction(penAction);
    connect(penAction, SIGNAL(triggered()), SLOT(pen()));

    lineAction = new QAction(QIcon(linepix), tr("Line"), this);
    toolbar->addAction(lineAction);
    connect(lineAction, SIGNAL(triggered()), SLOT(line()));

    eraserAction = new QAction(QIcon(eraserpix), tr("Eraser"), this);
    toolbar->addAction(eraserAction);
    connect(eraserAction, SIGNAL(triggered()), SLOT(eraser()));

    rectAction = new QAction(QIcon(rectpix), tr("Rectangle"), this);
    toolbar->addAction(rectAction);
    connect(rectAction, SIGNAL(triggered()), SLOT(rect()));
    //toolbar->addSeparator();
    this->setContextMenuPolicy(Qt::NoContextMenu);

    //image = new QImage(1000,700,QImage::Format_ARGB32);
    image = new QPixmap(1000, 1000);

    image->fill(Qt::white);
    initial();
}

MyMainWindow::~MyMainWindow()
{
    delete image;
    delete painter;
    delete redoImage;
    delete undoImage;
    delete temp;
    delete tempResize;

    delete newFile;
    delete openFile;
    delete saveFile;
    delete undo;
    delete redo;
    delete clear;
    delete resize;
    delete fcolor;
    delete bcolor;
    delete penAction;
    delete lineAction;
    delete eraserAction;
    delete rectAction;

    delete eraserDialog;
    delete penDialog;
    delete lineDialog;
    delete rectDialog;
    delete slider1;
    delete slider2;
    delete slider3;
    delete slider4;
    delete text1;
    delete text2;
    delete text3;
    delete text4;
    delete text5;
    delete text6;

    delete flat;
    delete square;
    delete round;
    delete solid;
    delete dashed;
    delete dotted;
    delete dashDotted;
    delete dashDotDotted;
    delete single;
    delete poly;
    delete rectangle;
    delete roundedRect;
    delete elipse;
    delete foreground;
    delete background;
    delete nofill;
    delete miterJ;
    delete bevelJ;
    delete roundJ;
    delete penButton;
    delete lineButton;
    delete typeButton;
    delete styleRect;
    delete shapeRect;
    delete fillRect;
    delete typeRect;

}

void  MyMainWindow::initial()
{
    roundedSize = 0;
    //numPoints = 0;
    //vector = new QVector<QPoint>();
    redoImage = new QPixmap(image->width(), image->height());
    undoImage = new QPixmap(image->width(), image->height());
    temp = new QPixmap(image->width(), image->height());
    tempResize = new QPixmap(image->width(), image->height());
    eraserDialog = new QDialog(this);
    lineDialog = new QDialog(this);
    penDialog = new QDialog(this);
    rectDialog = new QDialog(this);
    //polygon = new QPolygon();

    pEnabled = false;
    painter = new QPainter(image);

    penQ.setColor(Qt::black);
    penQ.setCapStyle(Qt::FlatCap);
    penQ.setWidth(5);

    eraserQ.setColor(Qt::white);
    eraserQ.setWidth(5);

    rectQ.setColor(Qt::black);
    rectQ.setCapStyle(Qt::FlatCap);
    rectQ.setJoinStyle(Qt::MiterJoin);
    rectQ.setWidth(5);

    lineQ.setColor(Qt::black);
    lineQ.setCapStyle(Qt::FlatCap);
    lineQ.setStyle(Qt::SolidLine);
    lineQ.setWidth(5);

    penClick = true;

    eraserClick = false;
    rectClick = false;
    lineClick = false;

    rectNoFillClick = true;
    rectForeClick = false;
    rectBackClick = false;

    rectangleClick = true;
    roundedRectClick = false;
    ellipseClick = false;

    backgroundColor = Qt::white;
    foregroundColor = Qt::black;

    rectSolid = true;
    rectDashed = false;
    rectDotted = false;
    rectDashDotted = false;
    rectDashDotDotted = false;

    rectMJ = true;
    rectBJ = false;
    rectRJ = false;

    lineSolid = true;
    lineDashed = false;
    lineDotted = false;
    lineDashDotted = false;
    lineDashDotDotted = false;

    lineFlat = true;
    lineSquare = false;
    lineRound = false;

    lineSingle = true;
    linePoly = false;

    penFlat = true;
    penSquare = false;
    penRound = false;
    polyMode = false;
}

void MyMainWindow::clearImage()
{

    *undoImage = image->copy(0,0,image->width(), image->height());
    image->fill(Qt::white);
    *redoImage = image->copy(0,0,image->width(),image->height());
    polyMode = false;
    update();
}

void MyMainWindow::newImage()
{
    *undoImage = image->copy(0,0,image->width(), image->height());
    width = QInputDialog::getInt(this, "Width of the Image", "enter width", 5, 1);
    height = QInputDialog::getInt(this, "Height of the Image", "enter height", 5, 1);
    image = new QPixmap(width, height);
    image->fill(backgroundColor);
    painter = new QPainter(image);
    update();
    //initial();
    *redoImage = image->copy(0,0,image->width(),image->height());
}

void MyMainWindow::loadImage()
{
    QString s = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("Images (*.bmp)"));

    if (! s.isNull())
    {
        temp->load(s);
           // image->load(s);
     }
    image = new QPixmap(temp->width(), temp->height());
    *image = temp->copy(0,0, temp->width(), temp->height());
    pEnabled = false;
    painter = new QPainter(image);
    update();
}

void MyMainWindow::saveImage()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                        "/home",
                                                        tr("Images (*.bmp)"));
    image->save(path,"bmp");


}

void MyMainWindow::resizeImage()
{
    width = QInputDialog::getInt(this, "Width of the Image", "enter width", 5, 1);
    height = QInputDialog::getInt(this, "Height of the Image", "enter height", 5, 1);
    *tempResize = image->copy(0,0,image->width(), image->height());

    //*tempResize->scaled(width,height);
    image = new QPixmap(tempResize->width(), tempResize->height());
    *image = tempResize->scaled(width,height);
    //*imag =  tempResize->copy(0,0, tempResize->width(), tempResize->height());
    //image = new QPixmap(undoImage->width(), undoImage->height());
    //*image = redoImage->copy(0,0,redoImage->width(), redoImage->height());
   // image->.->scaled(width,height);
    pEnabled = false;

    painter = new QPainter(image);
    update();
}


void MyMainWindow::undoAction()
{
    image = new QPixmap(undoImage->width(), undoImage->height());
    *image = undoImage->copy(0,0, undoImage->width(), undoImage->height());
    pEnabled = false;
    painter = new QPainter(image);
    update();
}

void MyMainWindow::redoAction()
{
    image = new QPixmap(redoImage->width(), redoImage->height());
    *image = redoImage->copy(0,0,redoImage->width(), redoImage->height());
    pEnabled = false;
    painter = new QPainter(image);
    update();
}

void MyMainWindow::exit()
{
    this->close();
}

void MyMainWindow::line()
{
    lineClick = true;
    penClick = false;
    rectClick = false;
    eraserClick = false;
}

void MyMainWindow::eraser()
{
    lineClick = false;
    penClick = false;
    rectClick = false;
    eraserClick = true;
}

void MyMainWindow::pen()
{
    lineClick = false;
    penClick = true;
    rectClick = false;
    eraserClick = false;
}

void MyMainWindow::rect()
{
    lineClick = false;
    penClick = false;
    rectClick = true;
    eraserClick = false;
}

void MyMainWindow::setBackgroundColor()
{
    backgroundColor = QColorDialog::getColor(Qt::black, this, "Background Color");
}

void MyMainWindow::setForegroundColor()
{
    foregroundColor = QColorDialog::getColor(Qt::black, this, "Foreground Color");
    penQ.setColor(foregroundColor);
    lineQ.setColor(foregroundColor);
    rectQ.setColor(foregroundColor);
}

void MyMainWindow::setPen()
{
    penDialog = new QDialog(this);
    penDialog->setWindowTitle("Pen Diaolg");
    penDialog->resize(300, 150);

    text1 = new QLabel(penDialog);
    text1->setText("Cap Style");
    text1->setGeometry(10, 10, 100, 30);
    flat = new QRadioButton("Flat", penDialog);
    flat->setGeometry(10, 50, 100, 25);
    square = new QRadioButton("Square", penDialog);
    square->setGeometry(70, 50, 100, 25);
    round = new QRadioButton("Round", penDialog);
    round->setGeometry(150, 50, 100, 25);

    penButton = new QButtonGroup(penDialog);
    penButton->addButton(flat, 0);
    penButton->addButton(square, 1);
    penButton->addButton(round, 2);

    if(penFlat)
        flat->setChecked(true);
    else if(penSquare)
        square->setChecked(true);
    else if(penRound)
        round->setChecked(true);

    text2 = new QLabel(penDialog);
    text2->setText("Pen Size");
    text2->setGeometry(10, 75, 200, 30);

    slider1 = new QSlider(penDialog);
    slider1->setOrientation(Qt::Horizontal);
    slider1->setRange(0, 50);
    slider1->setValue(penQ.width());
    slider1->setGeometry(10, 100, 180, 30);

    penDialog->show();

    connect(penButton, SIGNAL(buttonClicked(int)), this, SLOT(setPenStyle(int)));
    connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(setPenSize(int)));
}

void MyMainWindow::setEraser()
{
    eraserDialog = new QDialog(this);
    eraserDialog->setWindowTitle("Eraser Diaolg");
    eraserDialog->resize(250,100);

    text1 = new QLabel(eraserDialog);
    text1->setText("Eraser Thickness");
    text1->setGeometry(10, 10, 200, 30);

    slider1 = new QSlider(eraserDialog);
    slider1->setOrientation(Qt::Horizontal);
    slider1->setRange(0, 50);
    slider1->setValue(eraserQ.width());
    slider1->setGeometry(10, 40, 200, 30);

    eraserDialog->show();
    connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(setEraserSize(int)));
}

void MyMainWindow::setEraserSize(int k)
{
    eraserQ.setWidth(k);
}

void MyMainWindow::setPenSize(int k)
{
    penQ.setWidth(k);
}

void MyMainWindow::setPenStyle(int k)
{
    if(k == 0){
        penQ.setCapStyle(Qt::FlatCap);
        penFlat = true;
        penSquare = false;
        penRound = false;
    }
    else if (k == 1){
        penQ.setCapStyle(Qt::SquareCap);
        penFlat = false;
        penSquare = true;
        penRound = false;
    }
    else if (k==2){
        penQ.setCapStyle(Qt::RoundCap);
        penFlat = false;
        penSquare = false;
        penRound = true;
    }
}

void MyMainWindow::setLine()
{
    lineDialog = new QDialog(this);
    lineDialog->setWindowTitle("Line Diaolg");
    lineDialog->resize(350,300);

    text1 = new QLabel(lineDialog);
    text1->setText("Line Style");
    text1->setGeometry(10, 10, 200, 30);

    solid = new QRadioButton("Solid", lineDialog);
    solid->setGeometry(15, 40, 200, 30);
    dashed = new QRadioButton("Dashed", lineDialog);
    dashed->setGeometry(15, 70, 200, 30);
    dotted = new QRadioButton("Dotted", lineDialog);
    dotted->setGeometry(15, 100, 200, 30);
    dashDotted = new QRadioButton("Dash-Dotted", lineDialog);
    dashDotted->setGeometry(15, 130, 200, 30);
    dashDotDotted = new QRadioButton("Dash Dot Dotted", lineDialog);
    dashDotDotted->setGeometry(15, 160, 200, 30);

    text2 = new QLabel(lineDialog);
    text2->setText("Cap Style");
    text2->setGeometry(200, 10, 100, 30);

    flat = new QRadioButton("Flat", lineDialog);
    flat->setGeometry(210, 50, 100, 25);
    square = new QRadioButton("Square", lineDialog);
    square->setGeometry(210, 75, 100, 25);
    round = new QRadioButton("Round", lineDialog);
    round->setGeometry(210, 100, 100, 25);

    text3 = new QLabel(lineDialog);
    text3->setText("Draw Type");
    text3->setGeometry(200, 130, 100, 30);

    single = new QRadioButton("Single", lineDialog);
    single->setGeometry(210, 170, 100, 25);
    poly = new QRadioButton("Ploy", lineDialog);
    poly->setGeometry(210, 200, 100, 25);


    penButton = new QButtonGroup(lineDialog);
    penButton->addButton(flat, 0);
    penButton->addButton(square, 1);
    penButton->addButton(round, 2);
    if(lineFlat)
        flat->setChecked(true);
    else if(lineSquare)
        square->setChecked(true);
    else if(lineRound)
        round->setChecked(true);



    lineButton = new QButtonGroup(lineDialog);
    lineButton->addButton(solid, 0);
    lineButton->addButton(dashed, 1);
    lineButton->addButton(dotted, 2);
    lineButton->addButton(dashDotted, 3);
    lineButton->addButton(dashDotDotted, 4);

    if(lineSolid)
        solid->setChecked(true);
    else if(lineDashed)
        dashed->setChecked(true);
    else if(lineDotted)
        dotted->setChecked(true);
    else if(lineDashDotted)
        dashDotted->setChecked(true);
    else if(lineDashDotDotted)
        dashDotDotted->setChecked(true);

    typeButton = new QButtonGroup(lineDialog);
    typeButton->addButton(single, 0);
    typeButton->addButton(poly, 1);

    if (lineSingle)
        single->setChecked(true);
    else if(linePoly)
        poly->setChecked(true);


    text4 = new QLabel(lineDialog);
    text4->setText("Line Thickness");
    text4->setGeometry(10, 210, 200, 30);

    slider1 = new QSlider(lineDialog);
    slider1->setOrientation(Qt::Horizontal);
    slider1->setRange(0, 50);
    slider1->setValue(lineQ.width());
    slider1->setGeometry(10, 250, 250, 30);
        //pSize = slider->value();
        //QMessageBox::about(this,"bitmap", " "+penButton->checkedId())
    lineDialog->show();
    connect(penButton, SIGNAL(buttonClicked(int)), this, SLOT(setLineCapStyle(int)));
    connect(lineButton, SIGNAL(buttonClicked(int)), this, SLOT(setLineStyle(int)));
    connect(typeButton, SIGNAL(buttonClicked(int)), this, SLOT(setLineType(int)));
    connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(setLineSize(int)));
}

void MyMainWindow::setLineCapStyle(int k)
{
    if(k == 0){
        lineQ.setCapStyle(Qt::FlatCap);
        lineFlat = true;
        lineSquare = false;
        lineRound = false;
    }
    else if (k == 1){
        lineQ.setCapStyle(Qt::SquareCap);
        lineFlat = false;
        lineSquare = true;
        lineRound = false;
    }
    else if (k==2){
        lineQ.setCapStyle(Qt::RoundCap);
        lineFlat = false;
        lineSquare = false;
        lineRound = true;
    }
}

void MyMainWindow::setLineStyle(int k)
{
    if(k == 0){
        lineQ.setStyle(Qt::SolidLine);
        lineSolid = true;
        lineDashed = false;
        lineDotted = false;
        lineDashDotted = false;
        lineDashDotDotted = false;
    }
    else if (k == 1){
        lineQ.setStyle(Qt::DashLine);
        lineSolid = false;
        lineDashed = true;
        lineDotted = false;
        lineDashDotted = false;
        lineDashDotDotted = false;
    }
    else if (k == 2){
        lineQ.setStyle(Qt::DotLine);
        lineSolid = false;
        lineDashed = false;
        lineDotted = true;
        lineDashDotted = false;
        lineDashDotDotted = false;
    }
    else if (k == 3){
        lineQ.setStyle(Qt::DashDotLine);
        lineSolid = false;
        lineDashed = false;
        lineDotted = false;
        lineDashDotted = true;
        lineDashDotDotted = false;
    }
    else if (k == 4){
        lineQ.setStyle(Qt::DashDotDotLine);
        lineSolid = false;
        lineDashed = false;
        lineDotted = false;
        lineDashDotted = false;
        lineDashDotDotted = true;

    }
}

void MyMainWindow::setLineType(int k)
{   
    if(k == 0){
        lineSingle = true;
        linePoly = false;
        polyMode = false;
        //list.clear();
    }
    else if (k == 1){
        lineSingle = false;
        linePoly = true;
        //list.clear();
        polyMode = false;
    }
}

void MyMainWindow::setLineSize(int k)
{
    lineQ.setWidth(k);
}

void MyMainWindow::setRect()
{
    rectDialog->resize(375, 440);
    rectDialog->setWindowTitle("Rectangle Dialog");

    text1 = new QLabel(rectDialog);
    text1->setText("Line Style");
        //text->setFont(QFont::Bold);
    text1->setGeometry(10, 10, 200, 30);

    solid = new QRadioButton("Solid", rectDialog);
    solid->setGeometry(15, 50, 200, 30);
    dashed = new QRadioButton("Dashed", rectDialog);
    dashed->setGeometry(15, 100, 200, 30);
    dotted = new QRadioButton("Dotted", rectDialog);
    dotted->setGeometry(15, 150, 200, 30);
    dashDotted = new QRadioButton("Dash-Dotted", rectDialog);
    dashDotted->setGeometry(15, 200, 200, 30);
    dashDotDotted = new QRadioButton("Dash Dot Dotted", rectDialog);
    dashDotDotted->setGeometry(15, 250, 200, 30);

    text2 = new QLabel(rectDialog);
    text2->setText("Shape Style");
        //text->setFont(QFont::Bold);
    text2->setGeometry(200, 10, 100, 30);

    rectangle = new QRadioButton("Rectangle",rectDialog);
    rectangle->setGeometry(210, 40, 100, 25);
    roundedRect = new QRadioButton("Rounded Rectangle", rectDialog);
    roundedRect->setGeometry(210, 65, 200, 35);
    elipse = new QRadioButton("Elipe", rectDialog);
    elipse->setGeometry(210, 100, 100, 25);


    text3 = new QLabel(rectDialog);
    text3->setText("Fill Color");
    text3->setGeometry(200, 130, 100, 30);

    foreground = new QRadioButton("Foreground", rectDialog);
    foreground->setGeometry(210, 160, 100, 25);
    background = new QRadioButton("BackGround", rectDialog);
    background->setGeometry(210, 180, 150, 30);
    nofill = new QRadioButton("No fill", rectDialog);
    nofill->setGeometry(210, 210, 100, 25);


    text4 = new QLabel(rectDialog);
    text4->setText("Boundry Type");
    text4->setGeometry(200, 230, 100, 30);

    miterJ = new QRadioButton("Miter Join", rectDialog);
    miterJ->setGeometry(210, 260, 100, 25);
    bevelJ = new QRadioButton("Bevel Join", rectDialog);
    bevelJ->setGeometry(210, 290, 100, 25);
    roundJ = new QRadioButton("Round Join", rectDialog);
    roundJ->setGeometry(210, 320, 100, 25);

    styleRect = new QButtonGroup(rectDialog);
    styleRect->addButton(solid, 0);
    styleRect->addButton(dashed, 1);
    styleRect->addButton(dotted, 2);
    styleRect->addButton(dashDotted, 3);
    styleRect->addButton(dashDotDotted, 4);

    if(rectSolid)
        solid->setChecked(true);
    else if (rectDashed)
        dashed->setChecked(true);
    else if(rectDotted)
        dotted->setChecked(true);
    else if (rectDashDotted)
        dashDotted->setChecked(true);
    else if(rectDashDotDotted)
        dashDotDotted->setChecked(true);


    shapeRect = new QButtonGroup(rectDialog);
    shapeRect->addButton(rectangle, 0);
    shapeRect->addButton(roundedRect, 1);
    shapeRect->addButton(elipse, 2);

    if(rectangleClick)
        rectangle->setChecked(true);
    else if(roundedRectClick)
        roundedRect->setChecked(true);
    else if(ellipseClick)
        elipse->setChecked(true);

    typeRect = new QButtonGroup(rectDialog);
    typeRect->addButton(miterJ, 0);
    typeRect->addButton(bevelJ, 1);
    typeRect->addButton(roundJ, 2);

    if(rectMJ)
        miterJ->setChecked(true);
    else if(rectBJ)
        bevelJ->setChecked(true);
    else if(rectRJ)
        roundJ->setChecked(true);

    fillRect = new QButtonGroup(rectDialog);
    fillRect->addButton(foreground, 0);
    fillRect->addButton(background, 1);
    fillRect->addButton(nofill, 2);

    if(rectNoFillClick)
        nofill->setChecked(true);
    else if(rectForeClick)
        foreground->setChecked(true);
    else if(rectBackClick)
        background->setChecked(true);

    text5 = new QLabel(rectDialog);
    text5->setText("Line Thickness");
    text5->setGeometry(10, 320, 200, 30);

    slider3 = new QSlider(rectDialog);
    slider3->setOrientation(Qt::Horizontal);
    slider3->setRange(0, 50);
    slider3->setValue(rectQ.width());
    slider3->setGeometry(10, 350, 250, 30);

    text6 = new QLabel(rectDialog);
    text6->setText("Rounded Rectangle Curve");
    text6->setGeometry(10, 370, 200, 30);

    slider4 = new QSlider(rectDialog);
    slider4->setOrientation(Qt::Horizontal);
    slider4->setRange(0, 50);
    slider4->setValue(roundedSize);
    slider4->setGeometry(10, 390, 250, 30);

        //pSize = slider->value();
        //QMessageBox::about(this,"bitmap", " "+penButton->checkedId());
    rectDialog->show();
    connect(styleRect, SIGNAL(buttonClicked(int)), this, SLOT(rectStyle(int)));
    connect(shapeRect, SIGNAL(buttonClicked(int)), this, SLOT(rectShapeType(int)));
    connect(typeRect, SIGNAL(buttonClicked(int)), this, SLOT(rectType(int)));
    connect(fillRect, SIGNAL(buttonClicked(int)), this, SLOT(rectFillColor(int)));
    connect(slider3, SIGNAL(valueChanged(int)), this, SLOT(lineRect(int)));
    connect(slider4, SIGNAL(valueChanged(int)), this, SLOT(curveRect(int)));

}

void MyMainWindow::rectStyle(int k)
{
    if(k == 0){
        rectQ.setStyle(Qt::SolidLine);
        rectSolid = true;
        rectDashed = false;
        rectDotted = false;
        rectDashDotted = false;
        rectDashDotDotted = false;
    }
    else if (k == 1){
        rectQ.setStyle(Qt::DashLine);
        rectSolid = false;
        rectDashed = true;
        rectDotted = false;
        rectDashDotted = false;
        rectDashDotDotted = false;
    }
    else if (k == 2){
        rectQ.setStyle(Qt::DotLine);
        rectSolid = false;
        rectDashed = false;
        rectDotted = true;
        rectDashDotted = false;
        rectDashDotDotted = false;
    }
    else if (k == 3){
        rectQ.setStyle(Qt::DashDotLine);
        rectSolid = false;
        rectDashed = false;
        rectDotted = false;
        rectDashDotted = true;
        rectDashDotDotted = false;
    }
    else if (k == 4){
        rectQ.setStyle(Qt::DashDotDotLine);
        rectSolid = false;
        rectDashed = false;
        rectDotted = false;
        rectDashDotted = false;
        rectDashDotDotted =true;
    }
}

void MyMainWindow::rectShapeType(int k)
{
    if(k == 0){
        rectangleClick = true;
        roundedRectClick = false;
        ellipseClick = false;
    }
    else if (k == 1){
        rectangleClick = false;
        roundedRectClick = true;
        ellipseClick = false;
    }
    else if (k == 2){
        rectangleClick = false;
        ellipseClick = true;
        roundedRectClick =false;
    }
}

void MyMainWindow::rectFillColor(int k)
{
    if(k == 0){
        rectNoFillClick = false;
        rectForeClick = true;
        rectBackClick = false;
    }
    else if (k == 1){
        rectNoFillClick = false;
        rectForeClick = false;
        rectBackClick = true;
    }
    else if (k == 2){
        rectNoFillClick = true;
        rectForeClick = false;
        rectBackClick = false;
    }
}


void MyMainWindow::rectType(int k)
{
    if(k == 0){
        rectQ.setJoinStyle(Qt::MiterJoin);
        rectMJ = true;
        rectBJ = false;
        rectRJ = false;
    }
    else if (k == 1){
        rectQ.setJoinStyle(Qt::BevelJoin);
        rectMJ = false;
        rectBJ = true;
        rectRJ = false;
    }
    else if (k == 2){
        rectQ.setJoinStyle(Qt::RoundJoin);
        rectMJ = false;
        rectBJ = false;
        rectRJ = true;
    }
}

void MyMainWindow::lineRect(int k)
{
    rectQ.setWidth(k);
}

void MyMainWindow::curveRect(int k)
{
    roundedSize = k;
}

void MyMainWindow::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    paint.fillRect(image->rect(), Qt::white);
    paint.drawPixmap(0, 0, *image);
    e->accept();
}

void MyMainWindow::mousePressEvent(QMouseEvent *e)
{
    *undoImage = image->copy(0,0,image->width(), image->height());

    if(e->button() == Qt::LeftButton)
    {

        pEnabled = true;
        pBegin = e->pos();
        e->accept();
        if (lineClick){
            if(linePoly&&!polyMode){
                polyMode = true;
                pBegin = e->pos();
                //list.push_back(pBegin);
                //painter->setPen(rectQ);
                //painter->drawPoint(pBegin);
            }
            else if (polyMode){
                pBegin = pEnd;
            }
        }

        if(eraserDialog->isVisible())
            eraserDialog->close();
        if(penDialog->isVisible())
            penDialog->close();
        if(lineDialog->isVisible())
            lineDialog->close();
        if(rectDialog->isVisible())
            rectDialog->close();
    }
    else if (e->button() == Qt::RightButton){
        if(rectClick){
            setRect();
        }
        else if (eraserClick){
            setEraser();
        }
        else if (penClick){
            setPen();
        }
        else if (lineClick){
            setLine();
        }
    }
}
void MyMainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (!pEnabled){
        e->accept();
        return;
    }
    if(penClick){
        pEnd = e->pos();
        painter->setPen(penQ);
        painter->drawLine(pBegin, pEnd);
        
        pBegin = pEnd;
        update();
        e->accept();
    }
    else if (eraserClick){
        pEnd = e->pos();
        painter->setPen(eraserQ);
        painter->drawLine(pBegin, pEnd);
        pBegin = pEnd;
        update();
        e->accept();

    }
    else if(rectClick){
    }
}
void MyMainWindow::mouseReleaseEvent(QMouseEvent * e)
{
    if (lineClick&&lineSingle&& e->button() != Qt::RightButton){
        pEnd = e->pos();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(lineQ);
        painter->drawLine(pBegin,pEnd);
    }
    else if(lineClick&&linePoly&& e->button() != Qt::RightButton){
        pEnd = e->pos();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(lineQ);
        painter->drawLine(pBegin,pEnd);
    }
    else if(rectClick && e->button() != Qt::RightButton){
        pEnd = e->pos();
        painter->setPen(rectQ);
        painter->setRenderHint(QPainter::Antialiasing);

        if(rectangleClick){
            painter->setRenderHint(QPainter::Antialiasing);
            if(rectBackClick){
                painter->setBrush(backgroundColor);
                painter->drawRect(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y());
                painter->setBrush(Qt::transparent);
            }
            else if(rectForeClick){
                rectQ.setColor(Qt::white);
                painter->drawRect(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y());
                painter->fillRect(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y(), backgroundColor);
                rectQ.setColor(backgroundColor);
            }
            else{
                painter->drawRect(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y());
            }
        }
        else if(roundedRectClick){
            painter->setRenderHint(QPainter::Antialiasing);
            if(rectBackClick){
                painter->setBrush(backgroundColor);
                painter->drawRoundedRect(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y(),
                                        roundedSize,roundedSize, Qt::AbsoluteSize);
                painter->setBrush(Qt::transparent);
            }
            else{
                painter->drawRoundedRect(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y(),
                                        roundedSize,roundedSize, Qt::AbsoluteSize);
            }
        }
        else if(ellipseClick){
            painter->setRenderHint(QPainter::Antialiasing);
            if(rectBackClick){
                painter->setBrush(backgroundColor);
            }
            painter->drawEllipse(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y());
            painter->setBrush(Qt::transparent);
        }     
        else{
            painter->setRenderHint(QPainter::Antialiasing);
            painter->drawRect(pBegin.x(), pBegin.y(), pEnd.x()-pBegin.x(), pEnd.y()-pBegin.y());
        }
    }
    pEnabled = false;
    update();
    e->accept();
    *redoImage = image->copy(0,0,image->width(),image->height());
}

void MyMainWindow::mouseDoubleClickEvent(QMouseEvent * e)
{
    polyMode = false;
    //polygon = new QPolygon(list);
    //painter->drawPolygon(*polygon);
    //list.clear();
}
