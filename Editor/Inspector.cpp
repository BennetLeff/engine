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

    standardItemModel = setupModel();
    mapper = setupMapper();
}

QStandardItemModel* Inspector::setupModel()
{
    auto standardsModel = new QStandardItemModel(3, 2);

    return  standardsModel;
}

QDataWidgetMapper* Inspector::setupMapper()
{
    auto widgetMapper = new QDataWidgetMapper();
    widgetMapper->setModel(standardItemModel);

    return widgetMapper;
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

void Inspector::updateLayout(Model* gameObject)
{
    clearLayout();

    auto inspectorLabel = new QLabel("Inspector");

    auto objectNameLabel = new QLabel(gameObject->getName().data());

    getLayout()->addRow(inspectorLabel);
    getLayout()->addRow(objectNameLabel);

    fprintf(stderr, "%g\n", gameObject->transform->getPosition()->x);

    // Cast gameObject to Model and get properties.
    // auto model = dynamic_cast<Model*>(gameObject);
    if (gameObject != nullptr)
    {
        auto xLineEdit = new QLineEdit(std::to_string(gameObject->transform->getPosition()->x).data());
        xLineEdit->setMaximumWidth(100);
        mapper->addMapping(xLineEdit, 0);
        connect(xLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(updateGameObjectX(const QString&)));

        auto yLineEdit = new QLineEdit(std::to_string(gameObject->transform->getPosition()->y).data());
        yLineEdit->setMaximumWidth(100);
        mapper->addMapping(yLineEdit, 1);
        connect(yLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(updateGameObjectY(const QString&)));


        auto zLineEdit = new QLineEdit(std::to_string(gameObject->transform->getPosition()->z).data());
        zLineEdit->setMaximumWidth(100);
        mapper->addMapping(zLineEdit, 2);
        connect(zLineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(updateGameObjectZ(const QString&)));

        connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGameObject(int)));

        getLayout()->addRow(tr("x: "), xLineEdit);
        getLayout()->addRow(tr("y: "), yLineEdit);
        getLayout()->addRow(tr("z: "), zLineEdit);

        currentModel = gameObject;
        // modelPos = gameObject->transform->getPosition();
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

void Inspector::updateGameObjectX(const QString& text)
{
    fprintf(stderr, "%s", text.toStdString().data());
    auto pos_x = std::atof(text.toStdString().data());
}

void Inspector::updateGameObjectY(const QString& text)
{
    fprintf(stderr, "%s", text.toStdString().data());
    auto pos_y = std::atof(text.toStdString().data());
}

void Inspector::updateGameObjectZ(const QString& text)
{
    fprintf(stderr, "%s", text.toStdString().data());
    auto pos_z = std::atof(text.toStdString().data());
}

void Inspector::updateGameObject(int row)
{
    fprintf(stderr, "update game object row %d", row);
}