import bpy
import math
import bpy_extras
import gpu
import gpu_extras.batch
import copy
import mathutils
import json 

from bpy.props import (
    IntProperty,
    FloatProperty,
    FloatVectorProperty,
    EnumProperty,
    BoolProperty,
     PointerProperty
)

bl_info={
    "name": "就活用レベルエディタ",
    "author": "Ibu",
    "version": (1.0),
    "blender": (3,3,0),
    "location": "",
    "description": "就活用レベルエディタ",
    "waning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "object"
}


#json出力
class MYADDON_OT_export_scene(bpy.types.Operator,bpy_extras.io_utils.ExportHelper):
    bl_idname ="myaddon.myaddon_ot_export_scene"
    bl_label = "シーン出力"
    bl_description ="シーン情報をexportします"
    filename_ext = ".json"

    
    def write_and_print(self,file,str):
        print(str)

        file.write(str)
        file.write('\n')
 
        
    def parse_scene_recursive_json(self,data_parent,object,level):
        json_object=dict()
        json_object["type"] = object.type
        json_object["name"] = object.name
        
        if "file_name" in object:
            json_object["file_name"] = object["file_name"]
        else:
            json_object["file_name"] = "Box"
        
        json_object["objectType"] = object.gameObject_type.gameObject_enum

        trans,rotate,scale=object.matrix_local.decompose()
        rotate = rotate.to_euler()
        rotate.x = math.degrees(rotate.x)
        rotate.y = math.degrees(rotate.y)
        rotate.z = math.degrees(rotate.z)
        transform = dict()
        transform["translate"] = (trans.x,trans.y,trans.z)
        transform["rotate"] = (rotate.x,rotate.y,rotate.z)
        transform["scale"] = (scale.x,scale.y,scale.z)
        json_object["transform"] = transform
        
       
        if "collider" in object:
            collider = dict()
            collider["type"] = object.collider_type.collider_enum
            collider["center"] = object["collider_center"].to_list()
            collider["size"] = object["collider_size"].to_list()
            json_object["collider"] = collider

        data_parent.append(json_object)
        if len(object.children) > 0:
            json_object["children"] = list()
            for child in object.children:
                self.parse_scene_recursive_json(json_object["children"],child,level +1)


    def export_json(self):
        #保存情報をまとめるdict
        json_object_root = dict()
    
        json_object_root["name"] = "scene"

        #objectのデータ
        json_object_root["objects"] = list()
    
        for object in bpy.context.scene.objects:
            if(object.parent):
               continue
            self.parse_scene_recursive_json(json_object_root["objects"],object,0)

        json_text = json.dumps(json_object_root,ensure_ascii=False,cls=json.JSONEncoder,indent=4)
        print(json_text)
        with open(self.filepath,"wt",encoding="utf-8") as file:
            file.write(json_text)

    def execute(self,context):
        print("シーン情報をExportします")

        self.export_json()
        print("シーン情報をExportした")
        self.report({'INFO'},"シーン情報をExportした")
        return {'FINISHED'}


#メニュー
class TOPBAR_MT_my_menu(bpy.types.Menu):
    bl_idname = "TOPBAR_MT_my_menu"
    bl_label = "MyMenu"
    bl_description = "拡張メニュー by" + bl_info["author"]
    
    def draw(self,context):
        self.layout.operator(MYADDON_OT_export_scene.bl_idname,text = MYADDON_OT_export_scene.bl_label)
    
    def submenu(self,context):
        self.layout.menu(TOPBAR_MT_my_menu.bl_idname)

    def submenuExport(self,context):
        self.layout.menu(MYADDON_OT_export_scene.bl_idname)

#objectごとの

class MYADDON_OT_add_filename(bpy.types.Operator):
    bl_idname = "myaddon.myaddon_ot_add_filename"
    bl_label = "FileName 追加"
    bl_description = "['file_name']カスタムプロパティを追加"
    bl_options = {"REGISTER","UNDO"}

    def execute(self,context):
        context.object["file_name"] = ""
        return {"FINISHED"}

class ObjectType(bpy.types.PropertyGroup):
    gameObject_enum : EnumProperty(
        name="オブジェクトの種類",
        description="objectの種類",
        items=[
            ('Map', "ブロック", "ブロック"),
            ('Player', "プレイヤー", "プレイヤー"),
            ('Enemy', "敵", "敵")
        ],
        default='Map'
    ) # type: ignore

class MYADDON_OT_add_object_property(bpy.types.Operator):
    """objectの固有の設定"""
    bl_idname = "mayaddon.myaddon_ot_add_object_property"
    bl_label = "オブジェクトのプロパティを追加"
    bl_description = "カスタムプロパティを追加"
    bl_options = {"REGISTER","UNDO"}

    def execute(self,context):
        obj = context.object
        
        if not hasattr(obj,"gameObject_type"):
            obj.gameObject_type = bpy.data.objects.new("Object", None).gameObject_type
            obj.gameObject_type.gameObject_enum = 'Map'

        return {"FINISHED"}

class OBJECT_PT_Object(bpy.types.Panel):
    """ objectの名前 """

    bl_idname = "OBJECT_PT_Object"
    bl_label = "ObjectFilename"
    bl_space_type = "PROPERTIES" 
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self,context):
        obj = context.object

        if "file_name" in obj:
            self.layout.prop(obj,'["file_name"]',text = self.bl_label)
        else:
            self.layout.operator(MYADDON_OT_add_filename.bl_idname)

        if "gameObject_type"in obj:
            self.layout.prop(obj.gameObject_type,"gameObject_enum",text="property")
        else:
            self.layout.operator(MYADDON_OT_add_object_property.bl_idname)


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
      
#BoxCollider
class DrawCollider:

    handle = None

    def draw_collider():
        vertices = {"pos":[]}
        
        indices = []

        offsets = [
            [-0.5,-0.5,-0.5],
            [+0.5,-0.5,-0.5],
            [-0.5,+0.5,-0.5],
            [+0.5,+0.5,-0.5],
            [-0.5,-0.5,+0.5],
            [+0.5,-0.5,+0.5],
            [-0.5,+0.5,+0.5],
            [+0.5,+0.5,+0.5],
        ]

        size = [2,2,2]
     
        color = [0.5,1.0,1.0,1.0]

        #シーンのあるオブジェクトの探査
        for object in bpy.context.scene.objects:

            if not "collider" in object:
                continue
             
            color = [0.5,1.0,1.0,1.0]
            center = mathutils.Vector((0,0,0))
            size = mathutils.Vector((2,2,2))
            color = [object["collider_Line_Color"][0],
                     object["collider_Line_Color"][1],
                     object["collider_Line_Color"][2],
                     1.0
                    ]
               
            center[0] = object["collider_center"][0]
            center[1] = object["collider_center"][1]
            center[2] = object["collider_center"][2]

            size[0] = object["collider_size"][0]
            size[1] = object["collider_size"][1]
            size[2] = object["collider_size"][2]
            start = len(vertices["pos"])
            
            for offset in offsets:
                pos = copy.copy(center)
                pos[0] += offset[0] * size[0]
                pos[1] += offset[1] * size[1]
                pos[2] += offset[2] * size[2]
                pos = object.matrix_world @ pos
                vertices['pos'].append(pos)

                indices.append([start + 0,start + 1])
                indices.append([start + 2,start + 3])
                indices.append([start + 0,start + 2])
                indices.append([start + 1,start + 3])

                indices.append([start + 4,start + 5])
                indices.append([start + 6,start + 7])
                indices.append([start + 4,start + 6])
                indices.append([start + 5,start + 7])

                indices.append([start + 0,start + 4])
                indices.append([start + 1,start + 5])
                indices.append([start + 2,start + 6])
                indices.append([start + 3,start + 7])

            shader = gpu.shader.from_builtin("3D_UNIFORM_COLOR")
            batch = gpu_extras.batch.batch_for_shader(shader,"LINES",vertices,indices = indices)
     
            shader.bind()
            shader.uniform_float("color",color)
            batch.draw(shader)

#colliderの追加
class MYADDON_OT_add_collider(bpy.types.Operator):
    bl_idname = "mayaddon.myaddon_ot_add_collider"
    bl_label = "コライダーの追加"
    bl_description = "['collider']カスタムプロパティを追加"
    bl_options = {"REGISTER","UNDO"}
    
    def execute(self,context):
        
        obj = context.object
        
        context.object["collider"] = ""
        if not hasattr(obj, "collider_type"):
            obj.collider_type = bpy.data.objects.new("Object", None).collider_type
            obj.collider_type.collider_enum = 'Box'

        obj["collider_center"] = mathutils.Vector((0, 0, 0))
        obj["collider_size"] = mathutils.Vector((2, 2, 2))
        obj["collider_Line_Color"]=mathutils.Vector((0,1,1))
        return {"FINISHED"}

class OBJECT_PT_collider(bpy.types.Panel):
    bl_idname="OBJECT_PT_collider"
    bl_label = "Collider"
    bl_space_type = "PROPERTIES"
    bl_region_type ="WINDOW"
    bl_context ="object"
    
    def draw(self,context):
        
        obj = context.object
       
        if "collider"in obj:
            self.layout.prop(obj.collider_type, "collider_enum", text = "コライダーの種類")
            self.layout.prop(obj,'["collider_center"]',text = "Center")
            self.layout.prop(obj,'["collider_size"]',text = "Size")
            self.layout.separator()
            self.layout.prop(obj,'["collider_Line_Color"]',text = "線の色")

        else:
            self.layout.operator(MYADDON_OT_add_collider.bl_idname)


classes =(
    ###構造体
    ColliderType,
    ObjectType,
    ###トップメニュー
    MYADDON_OT_export_scene,
    TOPBAR_MT_my_menu,
    ###カスタムプロパティ
    #ファイルの名前
    MYADDON_OT_add_filename,
    MYADDON_OT_add_object_property,
    OBJECT_PT_Object,
    #コライダー
    MYADDON_OT_add_collider,
    OBJECT_PT_collider
)

#登録
def register():

    for cls in classes:
        bpy.utils.register_class(cls)
    
  
    bpy.types.Object.collider_type = PointerProperty(type = ColliderType)
    bpy.types.Object.gameObject_type = PointerProperty(type = ObjectType)


    #メニュー
    bpy.types.TOPBAR_MT_editor_menus.append(TOPBAR_MT_my_menu.submenu)
    bpy.types.TOPBAR_MT_editor_menus.append(TOPBAR_MT_my_menu.submenuExport)
    

    #プロパティ
    DrawCollider.handle = bpy.types.SpaceView3D.draw_handler_add(DrawCollider.draw_collider,(),"WINDOW","POST_VIEW")

    print("就活用レベルエディタが有効化されました")

def unregister():
    #プロパティ
    bpy.types.SpaceView3D.draw_handler_remove(DrawCollider.handle,"WINDOW")
    #メニュー
    bpy.types.TOPBAR_MT_editor_menus.remove(TOPBAR_MT_my_menu.submenu)
    bpy.types.TOPBAR_MT_editor_menus.remove(TOPBAR_MT_my_menu.submenuExport)

    
    for cls in classes:
        bpy.utils.unregister_class(cls)

    print("就活用レベルエディタが無効化されました")


if __name__ == "__main__":
   register()