//
// Created by bennet on 6/5/16.
//

#include <QtWidgets/QLabel>
#include <QtLineEditFactory>
#include <Core/Model.h>
#include "PropertyBrowser.h"

PropertyBrowser::PropertyBrowser()
{
    this->setMaximumHeight(1000);
    this->setMaximumWidth(300);

    qvBoxLayout = new QVBoxLayout();

    qvBoxLayout->addWidget(new QLabel("Inspector"));

    // Subclass abstract property manager in the future to make
    // these for other types like vectors.
    intPropertyManager = new QtIntPropertyManager(this);
    doublePropertyManager = new QtDoublePropertyManager(this);
    stringPropertyManager = new QtStringPropertyManager(this);

    transformPropertyManager = new TransformPropertyManager();

    propertyBrowser = new QtGroupBoxPropertyBrowser(this);

    QtDoubleSpinBoxFactory* doubleSpinBoxFactory = new QtDoubleSpinBoxFactory();
    QtLineEditFactory* lineEditFactory = new QtLineEditFactory();
    QtSpinBoxFactory* intSpinBoxFactory = new QtSpinBoxFactory();

    propertyBrowser->setFactoryForManager(intPropertyManager, intSpinBoxFactory);
    propertyBrowser->setFactoryForManager(doublePropertyManager, doubleSpinBoxFactory);
    propertyBrowser->setFactoryForManager(stringPropertyManager, lineEditFactory);


    // Set up layout and container widget for propertyBrowser.
    qvBoxLayout->addWidget(propertyBrowser);

    this->setLayout(qvBoxLayout);

    // Set up property managers signals and slots
    connect(doublePropertyManager, SIGNAL(valueChanged(QtProperty *, double)),
            this, SLOT(valueChanged(QtProperty *, double)));
    connect(stringPropertyManager, SIGNAL(valueChanged(QtProperty *, QString)),
            this, SLOT(valueChanged(QtProperty *, QString)));
}

void PropertyBrowser::loadProperties(QObject *object) {
    currentItem = nullptr;

    propertyBrowser->clear();
    if (object) {
        const QMetaObject *meta = object->metaObject();

        qDebug() << "class : " << meta->className();

        for (int i = 0; i < meta->propertyCount(); i++) {
            QMetaProperty metaProperty = meta->property(i);
            QVariant value = metaProperty.read(object);
            QtProperty *property = NULL;

            qDebug() << "property : " << metaProperty.name() << " : " << value.toString();

            if (metaProperty.type() == QVariant::Int) {
                property = intPropertyManager->addProperty(metaProperty.name());
                intPropertyManager->setValue(property, value.toInt());
            }
            else if (metaProperty.type() == QVariant::Double)
            {
                property = doublePropertyManager->addProperty(metaProperty.name());
                doublePropertyManager->setValue(property, value.toDouble());
            }
            else if (metaProperty.type() == QVariant::String)
            {
                // objectName is just a field of QObject we don't need.
                // it's usually stored at index 0, I'll have a better method of
                // removing it later.
                if (metaProperty.propertyIndex() != 0)
                {
                    property = stringPropertyManager->addProperty(metaProperty.name());
                    stringPropertyManager->setValue(property, value.toString());
                }
                else
                {
                    qDebug() << "objectName field found";
                }
            }
            else if (metaProperty.type() == QVariant::nameToType("Transform*"))
            {
                // Sets up main transform property.
                property = transformPropertyManager->addProperty(metaProperty.name());

                // Initialize the transform to get it's properties.
                auto trans = value.value<Transform*>();

                // Get the transform meta object.
                const QMetaObject* transMeta = trans->metaObject();

                // Loop through the meta objects properties and add them as subproperties.
                for(int subprop = 0; subprop < transMeta->propertyCount(); subprop++)
                {
                    QMetaProperty transMetaProperty = transMeta->property(subprop);
                    QtProperty* transSubProperty = NULL;

                    transSubProperty = doublePropertyManager->addProperty(transMetaProperty.name());
                    doublePropertyManager->setValue(transSubProperty, value.toDouble());

                    property->addSubProperty(transSubProperty);
                }
            }
            else
            {
                fprintf(stderr, "meta property type is not QVariant::Int, QVariant::Double, QVariant::String"
                        "\n it is instead %s \n", metaProperty.typeName());
            }

            if (property)
            {
                property->setEnabled(true);
                propertyBrowser->addProperty(property);
            }
        }
    }

    currentItem = object;

    propertyBrowser->setEnabled(true);
    propertyBrowser->update();
}

void PropertyBrowser::valueChanged(QtProperty *property, double value)
{
    auto id = property->propertyName().toStdString().data();

    if (!id)
        return;

    if (!currentItem)
        return;

    Model* model = dynamic_cast<Model*> (currentItem);
    if (model != nullptr)
    {
        model->setProperty(id, value);
    }
}

void PropertyBrowser::valueChanged(QtProperty *property, QString value)
{
    auto id = property->propertyName().toStdString().data();

    if (!id)
        return;

    if (!currentItem)
        return;

    Model* model = dynamic_cast<Model*>(currentItem);
    if (model != nullptr)
    {
        model->setProperty(id, value);
    }
}
