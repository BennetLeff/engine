//
// Created by bennet on 5/28/16.
//

#include "SideBarList.h"

SideBarList::SideBarList(Editor* editor)
{
    this->gameObjectList = new QListView();
    this->standardModel = new QStandardItemModel();

    gameObjectList->setMaximumWidth(150);

    mEditorParent = editor;
}

void SideBarList::addSideBarListItem(GameObject* gameObject)
{
    auto item = new SideBarListItem(gameObject, this->standardModel, this->gameObjectList);
    this->gameObjectListItems.push_back(item);
}

QStandardItemModel* SideBarList::getStandardModel()
{
    return this->standardModel;
}

QListView* SideBarList::getGameObjectList()
{
    return this->gameObjectList;
}

void SideBarList::setupSideBar()
{
    connect(this->getStandardModel(), SIGNAL(itemChanged(QStandardItem*)), this, SLOT(updateGameObjectName(QStandardItem*)));
    connect(gameObjectList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateClicked(QModelIndex)));
}

void SideBarList::updateGameObjectName(QStandardItem *item)
{
    auto sideBarItem = dynamic_cast<SideBarListItem*>(item);

    mEditorParent->updateEditor(sideBarItem->getGameObject());
}

void SideBarList::updateClicked(const QModelIndex &index)
{
    QStandardItem *item = getStandardModel()->itemFromIndex(index);
    updateGameObjectName(item);
}
