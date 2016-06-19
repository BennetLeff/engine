//
// Created by bennet on 6/5/16.
//

#include <QtWidgets/QLabel>
#include <QtLineEditFactory>
#include <Core/Model.h>
#include <QtCore/QString>
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

    groupPropertyManager = new QtGroupPropertyManager(this);


    propertyBrowser = new QtGroupBoxPropertyBrowser(this);

    QtDoubleSpinBoxFactory* doubleSpinBoxFactory = new QtDoubleSpinBoxFactory();
    QtLineEditFactory* lineEditFactory = new QtLineEditFactory();
    QtSpinBoxFactory* intSpinBoxFactory = new QtSpinBoxFactory();

    propertyBrowser->setFactoryForManager(intPropertyManager, intSpinBoxFactory);
    propertyBrowser->setFactoryForManager(doublePropertyManager, doubleSpinBoxFactory);
    propertyBrowser->setFactoryForManager(stringPropertyManager, lineEditFactory);

    vec3PropertyManger = new Vec3PropertyManger(this, doublePropertyManager);

    // Set up layout and container widget for propertyBrowser.
    qvBoxLayout->addWidget(propertyBrowser);

    this->setLayout(qvBoxLayout);

    // Set up property managers signals and slots
    connect(doublePropertyManager, SIGNAL(valueChanged(QtProperty *, double)),
            this, SLOT(valueChanged(QtProperty *, double)));
    connect(stringPropertyManager, SIGNAL(valueChanged(QtProperty *, QString)),
            this, SLOT(valueChanged(QtProperty *, QString)));
}

QtProperty* PropertyBrowser::loadTransformProperties(QObject* object)
{
    auto mainPropery = groupPropertyManager->addProperty("Transform");

    // Get the transform meta object.
    const QMetaObject* objMeta = object->metaObject();

    // Loop through the meta objects properties and add them as subproperties.
    for(int subprop = objMeta->propertyOffset(); subprop < objMeta->propertyCount(); subprop++)
    {
        QMetaProperty objMetaProperty = objMeta->property(subprop);

        auto vec3Variant =  objMetaProperty.read(object);
        auto vec3Obj = vec3Variant.value<Vec3*>();

        auto propName = QString("Transform.") +  QString(objMetaProperty.name());

        mainPropery->addSubProperty(loadVec3Properties(vec3Obj, propName.toStdString()));
    }

    return mainPropery;
}

QtProperty* PropertyBrowser::loadVec3Properties(Vec3* object, std::string name = "")
{
    return vec3PropertyManger->addProperty(name.data(), object);
}

QtProperty* PropertyBrowser::loadTextureProperties(QObject *textureObject)
{
    auto mainPropery = groupPropertyManager->addProperty("Texture");

    // Get the transform meta object.
    const QMetaObject* objMeta = textureObject->metaObject();

    // Loop through the meta objects properties and add them as subproperties.
    for(int i = objMeta->propertyOffset(); i < objMeta->propertyCount(); i++)
    {
        QMetaProperty objMetaProperty = objMeta->property(i);

        auto fieldVariant = objMetaProperty.read(textureObject);
        auto fieldObj = fieldVariant.value<QString>();

        auto propId = QString("Texture.") + QString(objMetaProperty.name());

        auto subProp = stringPropertyManager->addProperty(objMetaProperty.name());
        subProp->setEnabled(true);
        subProp->setPropertyId(propId);

        mainPropery->addSubProperty(subProp);
    }

    return mainPropery;
}

void PropertyBrowser::loadProperties(QObject *object)
{
    currentItem = nullptr;

    propertyBrowser->clear();
    if (object)
    {
        const QMetaObject *meta = object->metaObject();

//        qDebug() << "class : " << meta->className();

        for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
        {
            QMetaProperty metaProperty = meta->property(i);
            QVariant value = metaProperty.read(object);
            QtProperty *property = NULL;

//            qDebug() << "property : " << metaProperty.name() << " : " << value.toString();

            if (metaProperty.type() == QVariant::Int)
            {
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
            else
            {
                // Sets up main property.
                property = groupPropertyManager->addProperty(metaProperty.name());

                // Initialize the object to get it's properties.
                QObject* obj = new QObject();

                if (QVariant(metaProperty.typeName()) == QVariant("Transform*"))
                {
                    obj = value.value<Transform*>();
                    property = loadTransformProperties(obj);
                }
                else if (QVariant(metaProperty.typeName()) == QVariant("Vec3*"))
                {
                    obj = value.value<Vec3*>();
                    auto vec3 = dynamic_cast<Vec3*>(obj);
                    property = loadVec3Properties(vec3, QString(meta->className()).toStdString() + "." + QString(metaProperty.name()).toStdString());
                }
                else if (QVariant(metaProperty.typeName()) == QVariant("Texture*"))
                {
                    obj = value.value<Texture*>();
                    property = loadTextureProperties(obj);
                }
                else
                {
                    qDebug() << "Non primitive of following type not recognized: " << metaProperty.typeName();
                }

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
    auto propertyName = property->propertyName().toStdString().data();

    if (!propertyName)
        return;

    if (!currentItem)
        return;

    Model* model = dynamic_cast<Model*> (currentItem);
    if (model != nullptr)
    {
        auto propertySubTypeList = property->propertyId().split(".");
        // Is this is a Transform?
        if (propertySubTypeList[0].compare("Transform") == 0)
        {
            // Is this a Rotation?
            if (propertySubTypeList[1].compare("Rotation") == 0)
                model->transform->rotation()->setProperty(propertyName, value);
            else if (propertySubTypeList[1].compare("Position") == 0)
                model->transform->position()->setProperty(propertyName, value);
            else if (propertySubTypeList[1].compare("Scale") == 0)
                model->transform->scale()->setProperty(propertyName, value);
        }
        else
            qDebug() << "not transform property" << property->propertyId();
    }

    Light* light = dynamic_cast<Light*> (currentItem);
    if (light != nullptr)
    {
        auto propertySubTypeList = property->propertyId().split(".");

        if (propertySubTypeList[1].compare("Position") == 0)
            light->position->setProperty(propertyName, value);
        else if (propertySubTypeList[1].compare("Color") == 0)
            light->color->setProperty(propertyName, value);
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
        auto propertySubTypeList = property->propertyId().split(".");
        
        if (propertySubTypeList[1].compare("Path") == 0)
        {
            model->bindTexture(new Texture(value.toStdString()));
        }
    }
}
