//
// Created by bennet on 6/26/16.
//

#include <QtWidgets/QHBoxLayout>
#include "ImageEditorFactory.h"


ImageEditorFactory::ImageEditorFactory()
{
    mEditor = new QLineEdit(mFilePath);
    mImage = QImage(mFilePath); // QString("/home/bennet/Desktop/engine/res/brick.jpg"));

    mLabel = new QLabel(); // sets parent of label to main window
    mLabel->setPixmap(QPixmap::fromImage(mImage));

    mLabel->setMaximumSize(100, 100);

    mContainerWidget = new QWidget();
    auto containerWidgetLayout = new QVBoxLayout();

    containerWidgetLayout->addWidget(mEditor);
    containerWidgetLayout->addWidget(mLabel);

    mContainerWidget->setLayout(containerWidgetLayout);

    mLabel->show();
}

QWidget* ImageEditorFactory::createEditor(QtStringPropertyManager *manager, QtProperty *property,
                                          QWidget *parent)
{
    return mContainerWidget;
}

QWidget* ImageEditorFactory::createEditor( )//QtProperty* property, QWidget* parent)
{
    const QString& value = "";
//    connect(mEditor, SIGNAL(textEdited(const QString&)), this, SLOT(valueChanged(const QString&)));

    return mContainerWidget;
}
//
//void ImageEditorFactory::connectPropertyManager(QtStringPropertyManager *manager)
//{
//    fprintf(stderr, "called");
//
//    connect(manager, SIGNAL(valueChanged(QtProperty*, const QString&)), this, SLOT(valueChanged(QtProperty*, const QString&)));
//
//    connect(manager, SIGNAL(valueChanged(QtProperty *, const QString &)),
//            this, SLOT(slotPropertyChanged(QtProperty *, const QString &)));
//    connect(manager, SIGNAL(regExpChanged(QtProperty *, const QRegExp &)),
//            this, SLOT(slotRegExpChanged(QtProperty *, const QRegExp &)));
//
//}

//void ImageEditorFactory::disconnectPropertyManager(QtStringPropertyManager *manager)
//{
//
//}

void ImageEditorFactory::valueChanged(const QString &value)
{
    fprintf(stderr, "called");

    mFilePath = value;

    mImage = QImage(mFilePath);
    mLabel->setPixmap(QPixmap::fromImage(mImage));

    emit imagePathChanged(value);
}

void ImageEditorFactory::valueChanged(QtProperty*, const QString &value)
{
    mFilePath = value;

    mImage = QImage(mFilePath);
    mLabel->setPixmap(QPixmap::fromImage(mImage));
}