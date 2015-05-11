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
    btree<int> *t = new btree<int>(3);
    t->insert(1);
    t->insert(3);
    t->insert(7);
    t->insert(10);
    t->insert(11);
    t->insert(13);
    t->insert(14);
    t->insert(15);
    t->insert(18);
    t->insert(16);
    t->insert(19);
    t->insert(24);
    t->insert(25);
    t->insert(26);
    t->insert(21);
    t->insert(4);
    t->insert(5);
    t->insert(20);
    t->insert(22);
    t->insert(2);
    t->insert(17);
    t->insert(12);
    t->insert(6);

    /*
    t->insert(1);
    t->insert(3);
    t->insert(7);
    t->insert(10);
    t->insert(11);
    t->insert(100);
    t->insert(200);
    t->insert(250);
    t->insert(5);
    t->insert(2);
    t->insert(6);
    t->insert(21); */
    /* "Be assertive!! Not INsertive" */
    //std::vector<int*>* temp = t->convertToJack();

    /* Graph Widget */
    //GraphWidget *widget = new GraphWidget();
    //GraphWidget *widget = new GraphWidget(this);
    GraphWidget *widget = new GraphWidget(this, t);



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
