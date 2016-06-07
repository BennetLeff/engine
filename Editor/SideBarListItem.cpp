//
// Created by bennet on 5/28/16.
//

#include "SideBarListItem.h"

SideBarListItem::SideBarListItem(GameObject* gameObject, QStandardItemModel* standModel, QListView* listWidget)
{
    this->gameObject = gameObject;
    this->setText(gameObject->getName().data());

    standModel->insertRow(standModel->rowCount() + 1);
    standModel->appendRow(this);

    listWidget->setModel(standModel);
}
