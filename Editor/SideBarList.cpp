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

void SideBarList::addSideBarListItem(GameObject gameObject)
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
    auto thing = static_cast<SideBarListItem*>(item);
    printf("object changed %s \n", thing->getGameObject().getName().data());
    printf("item changed to %s \n", item->text().toStdString().data());
}