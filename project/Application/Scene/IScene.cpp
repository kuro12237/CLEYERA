#include "IScene.h"

void IScene::ListInitialize()
{
   for (auto obj : managerList_) {
      auto it = obj.lock();
      if (it)
         it->Initialize();
   }

   for (auto obj : particleList_) {
      auto it = obj.lock();
      if (it)
         it->Initialize();
   }

   for (auto obj : objctDataList_) {
      auto it = obj.lock();
      if (it)
         it->Initialize();
   }
}

void IScene::ListUpdate()
{

   for (auto obj : managerList_) {
      auto it = obj.lock();
      if (it)
         it->RemoveEmptyObjList();
         it->Update();
   }

   for (auto obj : particleList_) {
      auto it = obj.lock();
      if (it)
         it->Update();
   }

   for (auto obj : objctDataList_) {
      auto it = obj.lock();
      if (it)
         it->Update();
   }

   for (auto obj : lightDataList_) {
      auto it = obj.lock();
      if (it)
         it->Update();
   }
}
