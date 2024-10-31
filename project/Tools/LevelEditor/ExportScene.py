import bpy
import math
import bpy_extras
import gpu
import gpu_extras.batch
import copy
import mathutils
import json 


from LevelEditor.bl_Info import bl_info

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
        
        if "disabled_Flag" in object:
            if False == object["disabled_Flag"]:
                return

        
        json_object = dict()
        json_object["type"] = object.type
        json_object["name"] = object.name
        
        
        if "particle_group_name" in object :
          json_object["particle_group_name"] = object["particle_group_name"]
          json_object["texture_name"] = object["texture_name"]
          json_object["param_jsonfilepath"]=object["param_jsonfilepath"]
        

        if "file_name" in object:
            json_object["file_name"] = object["file_name"]
            #拡張子
            json_object["ModelFileType"] = object.modelFile_type.modelFile_enum 
            json_object["DrawType"] = object.draw_type.draw_enum

            if object.draw_type.draw_enum == "Instancing":
               json_object["InstancingObjName"] = object.gameObject_type.gameObject_enum
        
        #ファイルのoutput
        if object.paramfile_names:
            
            items = dict()
            for i,item in enumerate(object.paramfile_names):
                
                items[f"File {i}"] = item.file_name

            json_object["paramFileNames"] = items



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
