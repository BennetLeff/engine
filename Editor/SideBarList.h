//
// Created by bennet on 5/28/16.
//

#pragma once

#include <vector>

#include "Editor/SideBarListItem.h"
#include <QModelIndexList>

class SideBarList : public QObject
{
    Q_OBJECT
public:
    SideBarList();
    void addSideBarListItem(GameObject *gameObject);
    QStandardItemModel* getStandardModel();
    QListView* getGameObjectList();
    std::vector<QStandardItem*> getGameObjectListItems();
    void setupSideBar();
    QModelIndexList* getSelected();

private slots:
    void updateGameObjectName(QStandardItem* item);

signals:
    void itemChanged(QStandardItem* item);

private:
    // Contains the GameObjects added
    // to the scene.
    QListView* gameObjectList;

    // Stores all GameObject list items so they can be edited.
    std::vector<QStandardItem*> gameObjectListItems;
    QStandardItemModel* standardModel;
};
