//
// Created by phil on 4/7/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include <ui_mainwindow.h>

namespace Ui
{
    mainwindow::mainwindow(QWidget *parent) :
            QMainWindow(parent), ui(new Ui::mainwindow)
    {
        ui->setupUi(this);
        workspace *test = new workspace;
        setCentralWidget(test);
    }

    mainwindow::~mainwindow()
    {
        delete ui;
    }
} // Ui
