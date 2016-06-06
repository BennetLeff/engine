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

class PropertyBrowser : public QWidget
{
public:
    PropertyBrowser();
    void loadProperties(QObject* object);
private:
    QtTreePropertyBrowser       *_browser;
    QtIntPropertyManager        *_intManager;
    QtDoublePropertyManager     *_doubleManager;
    QtStringPropertyManager     *_stringManager;
};

