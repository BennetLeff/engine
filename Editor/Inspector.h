//
// Created by bennet on 5/28/16.
//

#pragma once

#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QSizePolicy>
#include <QStandardItem>
#include <QDataWidgetMapper>

#include "Core/GameObject.h"
#include "Core/Model.h"

class Inspector : public QWidget
{
    Q_OBJECT
public:
    Inspector();

    QFormLayout* getLayout();
    QWidget* getLayoutParent();
    void updateLayout(Model* gameObject);
    void clearLayout();

    /*
     * In the future createWidgets should use
     * introspection to dynamically generate a Inspector
     * menu for any GameObject.
     */
    void createWidgets(GameObject gameObject);
    void updateGameObject();
private:
    QStandardItemModel* setupModel();
    QDataWidgetMapper* setupMapper();

    QFormLayout* formLayout;
    QWidget* controlsRestrictorWidget;
    Model* currentModel;
    QStandardItemModel* standardItemModel;
    QDataWidgetMapper* mapper;

private slots:
    void updateGameObjectX(const QString& text);
    void updateGameObjectY(const QString& text);
    void updateGameObjectZ(const QString& text);

    void updateGameObject(int row);
signals:
    void textEdited(const QString& text);
};
