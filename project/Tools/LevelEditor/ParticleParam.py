import bpy
import math
import bpy_extras
import gpu
import gpu_extras.batch
import copy
import mathutils
import json 

class MYADDON_OT_add_ParticleGroupName(bpy.types.Operator):
    bl_idname = "myaddon.myaddon_ot_add_particlegroupname"
    bl_label = "パーティクルのグループ設定"
    bl_description = "['particle_group_name']グループを設定"
    bl_options = {"REGISTER","UNDO"}

    def execute(self,context):
        obj = context.object
        
        obj["particle_group_name"] = ""
        obj["texture_name"] = ""
        obj["param_jsonfilepath"]=""
        return {"FINISHED"}


class OBJECT_PT_ParticleObject(bpy.types.Panel):
    """ objectの名前 """

    bl_idname = "OBJECT_PT_ParticleObject"
    bl_label = "ParticleProperty"
    bl_space_type = "PROPERTIES" 
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self,context):
        obj = context.object
        layout = self.layout

        if "particle_group_name" in obj:
            layout.prop(obj,'["particle_group_name"]',text = "ParticleGroupName")
            layout.prop(obj,'["texture_name"]',text = "textureName")
            layout.prop(obj,'["param_jsonfilepath"]',text = "paramJson")
        else:
            layout.operator(MYADDON_OT_add_ParticleGroupName.bl_idname)
    