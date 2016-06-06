//
// Created by bennet on 6/5/16.
//

#include "PropertyBrowser.h"

PropertyBrowser::PropertyBrowser()
{


    _intManager = new QtIntPropertyManager();
    _doubleManager = new QtDoublePropertyManager();
    _stringManager = new QtStringPropertyManager();

    _browser = new QtTreePropertyBrowser(this);
}

void PropertyBrowser::loadProperties(QObject *object) {
    _browser->clear();
    if (object) {
        const QMetaObject *meta = object->metaObject();

        qDebug() << "class : " << meta->className();

        for (int i = 0; i < meta->propertyCount(); i++) {
            QMetaProperty metaProperty = meta->property(i);
            QVariant value = metaProperty.read(object);
            QtProperty *property = NULL;

            qDebug() << "property : " << metaProperty.name() << " : " << value.toInt();

            if (metaProperty.type() == QVariant::Int) {
                property = _intManager->addProperty(metaProperty.name());
                _intManager->setValue(property, value.toInt());
            }
            else if (metaProperty.type() == QVariant::Double) {
                property = _doubleManager->addProperty(metaProperty.name());
                _doubleManager->setValue(property, value.toDouble());
            }
            else if (metaProperty.type() == QVariant::String) {
                property = _stringManager->addProperty(metaProperty.name());
                _stringManager->setValue(property, value.toString());
            }

            if (property)
                _browser->addProperty(property);
        }
    }
}