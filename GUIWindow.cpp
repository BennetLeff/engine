//
// Created by bennet on 5/14/16.
//

#include "GUIWindow.h"
#include "ui_GUIWindow.h"

GUIWindow::GUIWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUIWindow) 
{
	ui->setupUi(this);
}

GUIWindow::~GUIWindow()
{
	delete ui;
}
