#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Elements
    QWidget *mainWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *hCore = new QHBoxLayout();
    QHBoxLayout *hControls = new QHBoxLayout();
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *gview = new QGraphicsView();
    QPushButton *button = new QPushButton();
    QTextEdit *edit = new QTextEdit();

    GraphWidget *widget = new GraphWidget();


    //Sizing
    edit->setMaximumWidth(100);
    edit->setMaximumHeight(28);
    button->setMaximumWidth(65);

    //Setup
    gview->setScene(scene);
    scene->addText("Hello CS240!");
    button->setText("Add");
    edit->setPlaceholderText("Value");
    //view->show();


    //Layout
    //hCore->addWidget(gview);
    hCore->addWidget(widget);

    mainLayout->addLayout(hControls);
    mainLayout->addLayout(hCore);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    hControls->addWidget(button);
    hControls->addWidget(edit);

}

MainWindow::~MainWindow()
{
    delete ui;
}
