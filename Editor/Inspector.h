//
// Created by bennet on 5/28/16.
//

#pragma once

#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>

#include "Core/GameObject.h"

class LabeledLineEdit : public QWidget
{
Q_OBJECT
public:
    LabeledLineEdit(std::string labelText, std::string lineText="")
    {
        label = new QLabel(labelText.data());
        lineEdit = new QLineEdit(lineText.data());

        auto labeledLineEditLayout = new QHBoxLayout();
        labeledLineEditLayout->addWidget(label);
        labeledLineEditLayout->addWidget(lineEdit);

        this->setMaximumWidth(150);
        this->setMaximumHeight(80);

        this->setLayout(labeledLineEditLayout);
    }
private:
    QLineEdit* lineEdit;
    QLabel* label;
};

class Inspector : public QWidget
{
    Q_OBJECT
public:
    Inspector();
    QVBoxLayout* getLayout();
    QLabel* getName() { return inspectorObjectName; }
    void insertRow(std::string label, std::string formData);
    void updateLayout();
    void clearLayout();
    /*
     * In the future createWidgets should use
     * introspection to dynamically generate a Inspector
     * menu for any GameObject.
     */
    void createWidgets(GameObject gameObject);
private:
    QVBoxLayout* inspectorLayout;
    QLabel* inspectorLabel;
    QLabel* inspectorObjectName;
    std::vector<LabeledLineEdit*> rows;
};
