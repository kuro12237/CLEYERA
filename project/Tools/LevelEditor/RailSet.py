import bpy
import math
import bpy_extras
import gpu
import gpu_extras.batch
import copy
import mathutils
import json 

class DrawRail:

    handle = None

    def draw_Lines():
        vertices = {"pos": []}
        indices = []
        
        for obj in bpy.context.scene.objects:

            if "railgroup_name" in obj:

               # 子オブジェクトがある場合、親を取得して線を描画
               if obj.parent:
                    posA=mathutils.Vector((0,0,0))
                    posB=mathutils.Vector((0,0,0))
               
                    parent_loc = obj.parent.matrix_world @ posA
                    child_loc = obj.matrix_world @ posB
            
                    # 頂点を追加
                    start = len(vertices["pos"])
                    vertices["pos"].append(parent_loc)
                    vertices["pos"].append(child_loc)
               
            
                    # インデックスを追加
                    indices.append([start + 0,start + 1])  # 親のインデックス

        shader = gpu.shader.from_builtin("UNIFORM_COLOR")
              
        batch = gpu_extras.batch.batch_for_shader(shader, "LINES", vertices, indices=indices)
        shader.bind() 
        shader.uniform_float("color", (1.0, 0.0, 0.0, 1.0))
        batch.draw(shader)


class MYADDON_OT_export_Rail(bpy.types.Operator,bpy_extras.io_utils.ExportHelper):
    bl_idname ="myaddon.myaddon_ot_export_rail"
    bl_label = "Rail出力"
    bl_description ="Railのポジションをexportします"
    filename_ext = ".json"

    def write_and_print(self,file,str):
        print(str)

        file.write(str)
        file.write('\n')

    def parse_scene_recursive_json(self,data_parent,object,level):
        
        json_object = dict()

        json_object["number"] = level

        if "railgroup_name" in object:
           json_object["RailGroup"] = object["railgroup_name"]
        
        trans,rotate,scale = object.matrix_local.decompose()
        rotate = rotate.to_euler()
        rotate.x = math.degrees(rotate.x)
        rotate.y = math.degrees(rotate.y)
        rotate.z = math.degrees(rotate.z)
        transform = dict()
        transform["translate"] = (trans.x,trans.y,trans.z)
        transform["rotate"] = (rotate.x,rotate.y,rotate.z)
        transform["scale"] = (scale.x,scale.y,scale.z)
        json_object["transform"] = transform

        data_parent.append(json_object)
        
        if len(object.children) > 0:
            for child in object.children:
                self.parse_scene_recursive_json(data_parent,child,level +1)
    
    def export_Railjson(self,context):
        #保存情報をまとめるdict
        json_object_root = dict()
    
        json_object_root["name"] = "Rail"

        #objectのデータ
        json_object_root["positions"] = list()
    
    
        if "railgroup_name" in context.object:

           self.parse_scene_recursive_json(json_object_root["positions"],context.object,0)


        json_text = json.dumps(json_object_root,ensure_ascii=False,cls=json.JSONEncoder,indent=4)
        print(json_text)
        with open(self.filepath,"wt",encoding="utf-8") as file:
            file.write(json_text)

    def execute(self,context):
        print("Rail情報をExportします")

        self.export_Railjson(context)
        print("Rail情報をExportした")
        self.report({'INFO'},"Rail情報をExportした")
        
        return {'FINISHED'}



class MYADDON_OT_add_RailGroupName(bpy.types.Operator):
    bl_idname = "myaddon.myaddon_ot_add_railgroupname"
    bl_label = "レールのグループ設定"
    bl_description = "['railgroup_name']グループを設定"
    bl_options = {"REGISTER","UNDO"}

    def execute(self,context):
        obj = context.object
        obj["railgroup_name"] = ""
        obj["railparam_jsonfilepath"]=""
       
        return {'FINISHED'}


class OBJECT_PT_RailObject(bpy.types.Panel):
    """ objectの名前 """

    bl_idname = "OBJECT_PT_RailObject"
    bl_label = "RailProperty"
    bl_space_type = "PROPERTIES" 
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self,context):
        obj = context.object
        layout = self.layout

        if "railgroup_name" in obj:
            layout.prop(obj,'["railgroup_name"]',text = "RailGroupName")
            layout.prop(obj,'["railparam_jsonfilepath"]',text = "paramJson")
            layout.operator(MYADDON_OT_export_Rail.bl_idname,text="Export")
        else:
            layout.operator(MYADDON_OT_add_RailGroupName.bl_idname)
        
        {'FINISHED'}