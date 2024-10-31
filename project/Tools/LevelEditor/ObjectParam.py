import bpy
import math
import bpy_extras
import gpu
import gpu_extras.batch
import copy
import mathutils
import json 


from LevelEditor.Enum import ObjectType
from LevelEditor.Enum import DrawType
from bpy.props import StringProperty, CollectionProperty, PointerProperty,IntProperty
from bpy.types import Operator, Panel, PropertyGroup

class ParamFileNameItem(PropertyGroup):
    file_name: StringProperty(name="File Name", description="Enter file name")# type: ignore


# ファイル名を追加するオペレーター
class MYADDON_OT_add_paramfilename(bpy.types.Operator):
    bl_idname = "myaddon.add_paramfilename"
    bl_label = "Add File Name"
    bl_description = "Add a new paramfile_name to the list"
    bl_options = {"REGISTER", "UNDO"}

    def execute(self, context):
        obj = context.object
        obj.paramfile_names.add()  # 新しい項目を追加
        return {"FINISHED"}

class OBJECT_PT_FilesObject(Panel):
    bl_idname = "OBJECT_PT_FilesObject"
    bl_label = "Object File Properties"
    bl_space_type = "PROPERTIES"
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self, context):
        layout = self.layout
        obj = context.object

        # ファイル名リストを表示
        for i, item in enumerate(obj.paramfile_names):
            row = layout.row()
            row.prop(item, "file_name", text=f"File {i+1}")

        # ファイルを追加するボタン
        layout.operator("myaddon.add_paramfilename", text="Add File Name")


class MYADDON_OT_add_filename(bpy.types.Operator):
    bl_idname = "myaddon.myaddon_ot_add_filename"
    bl_label = "FileName 追加"
    bl_description = "['file_name']カスタムプロパティを追加"
    bl_options = {"REGISTER","UNDO"}

    def execute(self,context):
        obj = context.object
        
        obj["file_name"] = ""
        if not hasattr(obj,"modelFile_type"):
           obj.modelFile_type = bpy.data.objects.new("Object", None).modelFile_type
           obj.modelFile_type.modelFile_enum = 'obj'
        return {"FINISHED"}

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
        
        if not hasattr(obj,"draw_type"):
            obj.draw_type = bpy.data.objects.new("object",None).draw_type,
            obj.draw_type.draw_enum = 'Instancing'

        return {"FINISHED"}

class OBJECT_PT_Object(bpy.types.Panel):
    """ objectの名前 """

    bl_idname = "OBJECT_PT_Object"
    bl_label = "ObjectFileProperty"
    bl_space_type = "PROPERTIES" 
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self,context):
        obj = context.object

        if "file_name" in obj:
            self.layout.prop(obj,'["file_name"]',text = "modelFilePath")
            self.layout.prop(obj.modelFile_type,"modelFile_enum",text="拡張子選択")
        else:
            self.layout.operator(MYADDON_OT_add_filename.bl_idname)

        if "gameObject_type"in obj:
        
            self.layout.prop(obj.gameObject_type,"gameObject_enum",text="property")
            self.layout.prop(obj.draw_type,"draw_enum",text="表示方法")
        else:
            self.layout.operator(MYADDON_OT_add_object_property.bl_idname)

    