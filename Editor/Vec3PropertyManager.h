//
// Created by bennet on 6/11/16.
//

#pragma once

#include <QtTreePropertyBrowser>
#include <QtIntPropertyManager>
#include <QtBoolPropertyManager>
#include <QtStringPropertyManager>
#include <QtVariantPropertyManager>

#include <QMetaProperty>
#include <QDebug>

#include <QVBoxLayout>
#include <QtGroupBoxPropertyBrowser>

class Vec3PropertyManger : public QtAbstractPropertyManager
{
public:
    Vec3PropertyManger(QObject *parent = 0, QtDoublePropertyManager* doublePropertyManager = 0) : QtAbstractPropertyManager(parent)
    {
        this->doublePropertyManager = doublePropertyManager;
        this->groupPropertyManager = new QtGroupPropertyManager();
    }

    // Use name to set whether property is from Transform, Light etc. as well as actual name.
    // For instance Transform.Rotation.
    QtProperty* addProperty(const QString& name, Vec3* vector3)
    {
        auto splitName = QString(name).split(".");

        QtProperty* mainProp = groupPropertyManager->addProperty(splitName[splitName.size() - 1]);

        auto vec3MetaObj = vector3->metaObject();

        for (int i = 1; i < vec3MetaObj->propertyCount(); i++)
        {
            QMetaProperty vec3MetaProperty = vec3MetaObj->property(i);

            auto subProp = doublePropertyManager->addProperty( vec3MetaProperty.name() );
            subProp->setPropertyId(name);

            doublePropertyManager->setValue(subProp, vec3MetaProperty.read(vector3).value<double>());

            mainProp->addSubProperty(subProp);
        }

        return mainProp;
    }

    void initializeProperty(QtProperty *property)
    {

    }

private:
    QtDoublePropertyManager* doublePropertyManager;
    QtGroupPropertyManager* groupPropertyManager;
};
