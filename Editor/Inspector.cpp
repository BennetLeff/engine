//
// Created by bennet on 5/28/16.
//

#include "Inspector.h"

Inspector::Inspector()
{
    // Set up the main inspector label
    inspectorLabel = new QLabel();
    inspectorLabel->setText("Inspector");
    inspectorLabel->setAlignment(Qt::AlignLeft);

    // Set up the name label to signify a GameObject's name.
    name = new QLabel();
    name->setAlignment(Qt::AlignCenter);

    inspectorLayout = new QVBoxLayout();
    inspectorLayout->addWidget(inspectorLabel);
    inspectorLayout->addWidget(name);

    // init();
}

QVBoxLayout* Inspector::getLayout()
{
    return this->inspectorLayout;
}

QTableWidget* Inspector::getTable()
{
    return this->inspectorTable;
}

void Inspector::createWidgets(GameObject gameObject)
{
    inspectorWidgets.push_back(new LabeledLineEdit("Pos x: ", std::to_string(gameObject.getPosition().x)));

    for (int i = 0; i < inspectorWidgets.size(); i++)
    {
        inspectorLayout->addWidget(inspectorWidgets[i]);
    }
}
