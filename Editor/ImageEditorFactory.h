//
// Created by bennet on 6/26/16.
//

#pragma once

#include <QtLineEditFactory>
#include <QLineEdit>
#include <QtWidgets/QLabel>

class ImageEditorFactory : public QWidget //: public QtLineEditFactory
{
    Q_OBJECT
public:
    ImageEditorFactory();
    QLineEdit* editor() { return mEditor; }

    //void connectPropertyManager(QtStringPropertyManager *manager);
    QWidget* createEditor(QtStringPropertyManager *manager, QtProperty *property,
                          QWidget *parent);
    QWidget* createEditor(); // QtProperty* property, QWidget* parent);
    //void disconnectPropertyManager(QtStringPropertyManager *manager);

private:
    QLineEdit* mEditor;
    QImage mImage;
    QLabel* mLabel;
    QWidget* mContainerWidget;
    QString mFilePath = "/home/bennet/Desktop/engine/res/default.jpg";

private slots:
    void valueChanged(const QString& value);
    void valueChanged(QtProperty* property, const QString& value);

signals:
    void imagePathChanged(const QString& value);
};

