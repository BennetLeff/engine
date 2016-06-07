//
// Created by bennet on 6/5/16.
//

#pragma once

#include <QtTreePropertyBrowser>
#include <QtIntPropertyManager>
#include <QtBoolPropertyManager>
#include <QtStringPropertyManager>

#include <QMetaProperty>
#include <QDebug>

#include <QVBoxLayout>

class PropertyBrowser : public QWidget
{
public:
    PropertyBrowser();
    void loadProperties(QObject* object);
private:
    QtTreePropertyBrowser* propertyBrowser;
    QtIntPropertyManager* intPropertyManager;
    QtDoublePropertyManager* doublePropertyManager;
    QtStringPropertyManager* stringPropertyManager;

    QVBoxLayout *qvBoxLayout;
};

