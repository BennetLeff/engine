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


class TransformPropertyManager : public QtGroupPropertyManager
{
public:
    TransformPropertyManager() { }
};

class PropertyBrowser : public QWidget
{
    Q_OBJECT
public:
    PropertyBrowser();
    void loadProperties(QObject* object);
private:
    QtGroupBoxPropertyBrowser* propertyBrowser;
    QtIntPropertyManager* intPropertyManager;
    QtDoublePropertyManager* doublePropertyManager;
    QtStringPropertyManager* stringPropertyManager;

    TransformPropertyManager* transformPropertyManager;

    QVBoxLayout *qvBoxLayout;

    QObject* currentItem;

    std::vector<QObject*> items;

private slots:
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, QString value);
};

