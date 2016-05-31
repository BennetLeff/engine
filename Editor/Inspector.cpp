//
// Created by bennet on 5/28/16.
//

#include "Inspector.h"
#include "Core/Model.h"

Inspector::Inspector()
{
    this->setMaximumHeight(10);

    formLayout = new QFormLayout();

    auto inspectorLabel = new QLabel("Inspector");

    formLayout->addWidget(inspectorLabel);
    formLayout->addWidget(new QLabel(""));
    formLayout->setAlignment(Qt::AlignLeft);

    /*
     * controlsRestrictorWidget holds the
     * formLayout so that the formLayout's
     * size will set properly.
     */
    controlsRestrictorWidget = new QWidget();
    controlsRestrictorWidget->setLayout(formLayout);
    controlsRestrictorWidget->setMaximumWidth(150);
}

// To be implemented in the future.
void Inspector::createWidgets(GameObject gameObject) { }

void Inspector::clearLayout()
{
    while (formLayout->count() != 0) // Check this first as warning issued if no items when calling takeAt(0).
    {
        QLayoutItem* forDeletion = formLayout->takeAt(0);

        if (forDeletion != nullptr)
        {
            delete forDeletion->widget();
            delete forDeletion;
        }
    }
}

void Inspector::updateLayout(GameObject* gameObject)
{
    clearLayout();

    auto inspectorLabel = new QLabel("Inspector");

    auto objectNameLabel = new QLabel(gameObject->getName().data());

    getLayout()->addRow(inspectorLabel);
    getLayout()->addRow(objectNameLabel);

    // Cast gameObject to Model and get properties.
    auto model = dynamic_cast<Model*>(gameObject);
    if (model != nullptr)
    {
        auto xLineEdit = new QLineEdit(std::to_string(model->transform->getPosition()->x).data());
        xLineEdit->setMaximumWidth(100);
        auto yLineEdit = new QLineEdit(std::to_string(model->transform->getPosition()->y).data());
        yLineEdit->setMaximumWidth(100);
        auto zLineEdit = new QLineEdit(std::to_string(model->transform->getPosition()->z).data());
        zLineEdit->setMaximumWidth(100);

        getLayout()->addRow(tr("x: "), xLineEdit);
        getLayout()->addRow(tr("y: "), yLineEdit);
        getLayout()->addRow(tr("z: "), zLineEdit);
    }
    else
    {
        fprintf(stderr, "Error: Model pointer not passed to update editor. ");
    }

    getLayout()->setSpacing(20);
}

QFormLayout* Inspector::getLayout()
{
    return formLayout;
}

QWidget* Inspector::getLayoutParent()
{
    return controlsRestrictorWidget;
}