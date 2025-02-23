#include "IScene.h"

void IScene::ListInitialize() 
{
   for (auto obj : managerList_) {
      auto it = obj.lock();
      if (it)
         continue;
      it->Initialize();
   }

   for (auto obj : particleList_) {
      auto it = obj.lock();
      if (it)
         continue;
      it->Initialize();
   }

   for (auto obj : objctDataList_) {
      auto it = obj.lock();
      if (it)
         continue;
      it->Initialize();
   }
}

void IScene::ListUpdate()
{

   for (auto obj : managerList_) {
      auto it = obj.lock();
      if (it)
         continue;

      it->Update();
   }

   for (auto obj : particleList_) {
       auto it = obj.lock();
      if (it)
         continue;
      it->Update();
   }

   for (auto obj : objctDataList_) {
      auto it = obj.lock();
      if (it)
         continue;
      it->Update();
   }

   for (auto obj : lightDataList_) {
      auto it = obj.lock();
      if (it)
         continue;
      it->Update();
   }
}
