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
#include <QtWidgets/QFileDialog>

#include "Vec3PropertyManager.h"
#include "ImageEditorFactory.h"

class PropertyBrowser : public QWidget
{
    Q_OBJECT
public:
    PropertyBrowser();
    void loadProperties(QObject* object);
    std::vector<QtProperty*> setupProperty(QMetaProperty property);
private:
    QtProperty* loadTransformProperties(QObject* transformObject);
    QtProperty* loadVec3Properties(Vec3* vec3Object, std::string name);
    QtProperty* loadTextureProperties(Texture* textureObject);
    QtGroupBoxPropertyBrowser* propertyBrowser;
    QtIntPropertyManager* intPropertyManager;
    QtDoublePropertyManager* doublePropertyManager;
    QtStringPropertyManager* stringPropertyManager;
    QtStringPropertyManager* stringPropertyManagerImage;

    QtGroupPropertyManager* groupPropertyManager;
    Vec3PropertyManger* vec3PropertyManger;

    QVBoxLayout *qvBoxLayout;

    QObject* currentItem;

    std::vector<QObject*> items;

private slots:
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, QString value);
    void showImagePicker()
    {
        auto filepath = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    }
    void updateImage(const QString& value);
};

