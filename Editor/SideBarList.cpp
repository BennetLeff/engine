//
// Created by bennet on 5/28/16.
//

#include "SideBarList.h"

SideBarList::SideBarList()
{
    this->gameObjectList = new QListView();
    this->standardModel = new QStandardItemModel();

    gameObjectList->setMaximumWidth(150);
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
}

void SideBarList::updateGameObjectName(QStandardItem *item)
{
    auto sideBarItem = static_cast<SideBarListItem*>(item);
    printf("object changed %s \n", sideBarItem->getGameObject()->getName().data());

    for (int i = 0; i < this->gameObjectListItems.size(); i++)
    {
        printf("Object: %s \n", static_cast<SideBarListItem* >(gameObjectListItems[i])->getGameObject()->getName().data());
    }
}

QModelIndexList* SideBarList::getSelected()
{
    auto indexes = gameObjectList->selectionModel()->selectedIndexes();
    for (int i = 0; i < indexes.size(); i++)
    {
        printf("Index: %s \n", indexes[i].data().toString().toStdString().data());
    }

    return nullptr;
}

std::vector<QStandardItem*> SideBarList::getGameObjectListItems()
{
    return this->gameObjectListItems;
}
