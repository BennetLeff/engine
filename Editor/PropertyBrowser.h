//
// Created by bennet on 6/5/16.
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

#include "Vec3PropertyManager.h"

class PropertyBrowser : public QWidget
{
    Q_OBJECT
public:
    PropertyBrowser();
    void loadProperties(QObject* object);
    std::vector<QtProperty*> setupProperty(QMetaProperty property);
private:
    QtGroupBoxPropertyBrowser* propertyBrowser;
    QtIntPropertyManager* intPropertyManager;
    QtDoublePropertyManager* doublePropertyManager;
    QtStringPropertyManager* stringPropertyManager;

    QtGroupPropertyManager* groupPropertyManager;
    Vec3PropertyManger* vec3PropertyManger;

    QVBoxLayout *qvBoxLayout;

    QObject* currentItem;

    std::vector<QObject*> items;

private slots:
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, QString value);

    QtProperty* loadTransformProperties(QObject* transformObject);
    QtProperty* loadVec3Properties(Vec3* vec3Object, std::string name);
};

