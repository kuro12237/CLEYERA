import bpy;

from bpy.props import (
 
    EnumProperty,
 
)


#instancingGroup
class ObjectType(bpy.types.PropertyGroup):
    gameObject_enum : EnumProperty(
        name="オブジェクトの種類",
        description="objectの種類",
        items=[
            ('None',"None","None"),
            ('Map', "ブロック", "ブロック"),
            ('Fence',"フェンス","フェンス"),
            ('FenceEnd',"フェンスの端","フェンス端"),
            ('Tower',"塔","塔"),
            ('WarpRoot',"ワープの道","ワープの道"),
            ('WarpConnector',"ワープ接続","ワープ接続"),
            ('BreakMap', "壊れるブロック", "壊れるブロック"),

        ],
        #items=get_enum_items,
        default='Map'
    ) # type: ignore

#DrawGrop
class DrawType(bpy.types.PropertyGroup):
    draw_enum : EnumProperty(
        name="オブジェクトの表示の種類",
        description="objectの表示種類",
        items=[
            ('Normal',"通常","通常"),
            ('Instancing', "インスタンシング", "インスタンシング"),
        ],
        default='Instancing'
    ) # type: ignore

#modelFilePath
class ModelFileType(bpy.types.PropertyGroup):
    modelFile_enum : EnumProperty(
        name="モデルのフォルダの拡張子",
        description="objectの表示種類",
        items=[
            ('obj',"obj","obj"),
            ('gltf', "gltf", "gltf"),
        ],
        default='obj'
    ) # type: ignore

#Colliderのenumの定義
class ColliderType(bpy.types.PropertyGroup):
      collider_enum : EnumProperty(
        name="当たり判定の種類",
        description="当たり判定の種類",
        items=[
            ('Box', "箱", "箱"),
            ('Sphere', "球", "球"),
            ('Enemy', "敵", "敵")
        ],
        default='Box'
    ) # type: ignore
    