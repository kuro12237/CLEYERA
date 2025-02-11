import bpy
import math
import bpy_extras
import gpu
import gpu_extras.batch
import copy
import mathutils
import json 
import gpu
import gpu_extras.batch


from bpy.props import (
    IntProperty,
    FloatProperty,
    FloatVectorProperty,
    EnumProperty,
    BoolProperty,
    PointerProperty
)
from bpy.props import StringProperty, CollectionProperty, PointerProperty
from bpy.types import Operator, Panel, PropertyGroup

from LevelEditor.Enum import ColliderType
from LevelEditor.Enum import ObjectType
from LevelEditor.Enum import DrawType
from LevelEditor.Enum import ModelFileType

from LevelEditor.BarMenu import TOPBAR_MT_my_menu
from LevelEditor.ExportScene import MYADDON_OT_export_scene

from LevelEditor.ObjectParam import MYADDON_OT_add_filename
from LevelEditor.ObjectParam import MYADDON_OT_add_object_property
from LevelEditor.ObjectParam import OBJECT_PT_Object

from LevelEditor.ObjectParam import ParamFileNameItem
from LevelEditor.ObjectParam import MYADDON_OT_add_paramfilename
from LevelEditor.ObjectParam import OBJECT_PT_FilesObject


from LevelEditor.ParticleParam import MYADDON_OT_add_ParticleGroupName
from LevelEditor.ParticleParam import OBJECT_PT_ParticleObject

from LevelEditor.Collider import MYADDON_OT_add_collider
from LevelEditor.Collider import OBJECT_PT_collider
from LevelEditor.Collider import DrawCollider

from LevelEditor.RailSet import MYADDON_OT_add_RailGroupName
from LevelEditor.RailSet import OBJECT_PT_RailObject
from LevelEditor.RailSet import DrawRail
from LevelEditor.RailSet import MYADDON_OT_export_Rail

from LevelEditor.disabled import MYADDON_OT_Disabled
from LevelEditor.disabled import OBJECT_PT_Disabled

from LevelEditor.spown import MYADDON_OT_load_spawn
from LevelEditor.spown import MYADDON_OT_create_spawn
from LevelEditor.spown import MYADDON_OT_spawn_create_player
from LevelEditor.spown import MYADDON_OT_spawn_create_player_menu
from LevelEditor.spown import MYADDON_OT_spawn_create_enemy
from LevelEditor.spown import MYADDON_OT_spawn_create_enemy_menu

bl_info={
    "name": "test 10_10",
    "author": "Ibu",
    "version": (1.0),
    "blender": (4,1,0),
    "location": "",
    "description": "就活用レベルエディタ",
    "waning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "object"
}

classes =(
    ###列挙
    ColliderType,
    ObjectType,
    DrawType,
    ModelFileType,
    ###トップメニュー
    MYADDON_OT_export_scene,
    TOPBAR_MT_my_menu,
    MYADDON_OT_export_Rail,
    #export無効化
    MYADDON_OT_Disabled,
    OBJECT_PT_Disabled,
    ###プロパティ
    MYADDON_OT_add_filename,
    MYADDON_OT_add_object_property,
    OBJECT_PT_Object,
    ParamFileNameItem,
    MYADDON_OT_add_paramfilename,
    OBJECT_PT_FilesObject,

    MYADDON_OT_load_spawn,
    MYADDON_OT_create_spawn,
    MYADDON_OT_spawn_create_player,
    MYADDON_OT_spawn_create_player_menu,
    MYADDON_OT_spawn_create_enemy,
    MYADDON_OT_spawn_create_enemy_menu,
    ###コライダー
    MYADDON_OT_add_collider,
    OBJECT_PT_collider,
    ###パーティクル
    OBJECT_PT_ParticleObject,
    MYADDON_OT_add_ParticleGroupName,
    ###Rail
    OBJECT_PT_RailObject,
    MYADDON_OT_add_RailGroupName,
    
)
    
def register():

    ###クラス登録
    for cls in classes:
        bpy.utils.register_class(cls)

    ###Enum登録
    bpy.types.Object.collider_type = PointerProperty(type = ColliderType)
    bpy.types.Object.gameObject_type = PointerProperty(type = ObjectType)
    bpy.types.Object.draw_type = PointerProperty(type = DrawType)
    bpy.types.Object.modelFile_type = PointerProperty(type = ModelFileType)
    bpy.types.Object.paramfile_names = CollectionProperty(type=ParamFileNameItem)

    bpy.types.TOPBAR_MT_editor_menus.append(TOPBAR_MT_my_menu.submenu)
    bpy.types.TOPBAR_MT_editor_menus.append(TOPBAR_MT_my_menu.submenuExport)
    
    #プロパティ
    DrawCollider.handle = bpy.types.SpaceView3D.draw_handler_add(DrawCollider.draw_collider,(),"WINDOW","POST_VIEW")
    DrawRail.handle=bpy.types.SpaceView3D.draw_handler_add(DrawRail.draw_Lines,(),"WINDOW","POST_VIEW")
  
    print("レベルエディタが有効化されました")

def unregister():

    #プロパティ
    bpy.types.SpaceView3D.draw_handler_remove(DrawCollider.handle,"WINDOW")
    bpy.types.SpaceView3D.draw_handler_remove(DrawRail.handle,"WINDOW")

    bpy.types.TOPBAR_MT_editor_menus.remove(TOPBAR_MT_my_menu.submenu)
    bpy.types.TOPBAR_MT_editor_menus.remove(TOPBAR_MT_my_menu.submenuExport)
    
    for cls in classes:
        bpy.utils.unregister_class(cls)
        
    print("レベルエディタが無効化されました")

if __name__ == "__main__":
   register()