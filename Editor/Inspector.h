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

#include "Core/GameObject.h"

class Inspector : public QWidget
{
    Q_OBJECT
public:
    Inspector();
    // QVBoxLayout* getLayout();
    QFormLayout* getLayout();
    QWidget* getLayoutParent();
    void updateLayout(GameObject* gameObject);
    void clearLayout();
    /*
     * In the future createWidgets should use
     * introspection to dynamically generate a Inspector
     * menu for any GameObject.
     */
    void createWidgets(GameObject gameObject);
private:
    QFormLayout* formLayout;
    QWidget* controlsRestrictorWidget;
};
