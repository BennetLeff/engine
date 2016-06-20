//
// Created by bennet on 5/28/16.
//

#pragma once

#include <vector>

#include "Editor/SideBarListItem.h"
#include "Editor.h"
#include <QModelIndexList>

class Editor;

class SideBarList : public QObject
{
    Q_OBJECT
public:
    SideBarList(Editor* editor);
    void addSideBarListItem(GameObject *gameObject);
    QStandardItemModel* getStandardModel();
    QListView* getGameObjectList();
    void setupSideBar();

private slots:
    void updateGameObjectName(QStandardItem* item);
    void updateClicked(const QModelIndex &index);

signals:
    void itemChanged(QStandardItem* item);
    void clicked(const QModelIndex &index);

private:
    // Contains the GameObjects added
    // to the scene.
    QListView* gameObjectList;

    // Stores all GameObject list items so they can be edited.
    std::vector<QStandardItem*> gameObjectListItems;
    QStandardItemModel* standardModel;

    Editor* mEditorParent;
};
