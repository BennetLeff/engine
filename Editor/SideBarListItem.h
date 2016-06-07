//
// Created by bennet on 5/28/16.
//

#pragma once

#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QStandardItem>

#include "Core/GameObject.h"

class SideBarListItem : public QObject, public QStandardItem
{
    Q_OBJECT
public:
    SideBarListItem(GameObject* gameObject, QStandardItemModel* standModel, QListView* listWidget);

    GameObject* getGameObject()
    {
        return gameObject;
    }

private:
    GameObject *gameObject;
};