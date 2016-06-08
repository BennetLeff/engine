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
    Q_OBJECT
public:
    PropertyBrowser();
    void loadProperties(QObject* object);
private:
    QtTreePropertyBrowser* propertyBrowser;
    QtIntPropertyManager* intPropertyManager;
    QtDoublePropertyManager* doublePropertyManager;
    QtStringPropertyManager* stringPropertyManager;

    QVBoxLayout *qvBoxLayout;

    QObject* currentItem;

    std::vector<QObject*> items;

private slots:
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, QString value);
};

