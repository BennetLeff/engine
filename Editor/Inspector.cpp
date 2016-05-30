//
// Created by bennet on 5/28/16.
//

#include "Inspector.h"

Inspector::Inspector()
{
    inspectorLayout = new QVBoxLayout();
    inspectorLabel = new QLabel("Inspector");
    inspectorObjectName = new QLabel("Place Holder");

    inspectorLayout->setSpacing(10);
}

// To be implemented in the future.
void Inspector::createWidgets(GameObject gameObject) { }

void Inspector::insertRow(std::string label, std::string formData)
{
    inspectorLayout->addWidget(new LabeledLineEdit(label, formData));
}

void Inspector::clearLayout()
{
    while (inspectorLayout->count() != 0) // Check this first as warning issued if no items when calling takeAt(0).
    {
        QLayoutItem* forDeletion = inspectorLayout->takeAt(0);

        if (forDeletion != nullptr)
        {
            delete forDeletion->widget();
            delete forDeletion;
        }
    }

}

void Inspector::updateLayout() { }

QVBoxLayout* Inspector::getLayout()
{
    return inspectorLayout;
}