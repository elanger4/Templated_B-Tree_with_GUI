#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "btree.h"

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



    /* The fact that this builds blows my mind */
    btree<int> t(3);
    t.insert(1);
    t.insert(3);
    t.insert(7);
    t.insert(10);
    t.insert(11);
    t.insert(100);
    t.insert(200);
    t.insert(250);
    t.insert(5);
    /* "Be assertive!! Not INsertive" */
    std::vector<int*>* temp = t.convertToJack();

    /* Graph Widget */
    //GraphWidget *widget = new GraphWidget();
    //GraphWidget *widget = new GraphWidget(this);
    GraphWidget *widget = new GraphWidget(this, temp);



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
