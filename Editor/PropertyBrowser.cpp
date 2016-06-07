//
// Created by bennet on 6/5/16.
//

#include <QtWidgets/QLabel>
#include <QtLineEditFactory>
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

    propertyBrowser = new QtTreePropertyBrowser(this);

    QtDoubleSpinBoxFactory* doubleSpinBoxFactory = new QtDoubleSpinBoxFactory();
    QtLineEditFactory* lineEditFactory = new QtLineEditFactory();
    QtSpinBoxFactory* intSpinBoxFactory = new QtSpinBoxFactory();

    propertyBrowser->setFactoryForManager(intPropertyManager, intSpinBoxFactory);
    propertyBrowser->setFactoryForManager(doublePropertyManager, doubleSpinBoxFactory);
    propertyBrowser->setFactoryForManager(stringPropertyManager, lineEditFactory);

    qvBoxLayout->addWidget(propertyBrowser);

    this->setLayout(qvBoxLayout);
}

void PropertyBrowser::loadProperties(QObject *object) {
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
                property = stringPropertyManager->addProperty(metaProperty.name());
                stringPropertyManager->setValue(property, value.toString());
            }
            else if (metaProperty.type() == QVariant::nameToType("Transform*"))
            {
                fprintf(stderr, "Identified a Transform* \n");
                fprintf(stderr, "%d \n", metaProperty.enclosingMetaObject()->propertyCount());
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

    propertyBrowser->setEnabled(true);
    propertyBrowser->update();
}