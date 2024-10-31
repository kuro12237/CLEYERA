import bpy
import math
import bpy_extras
import gpu
import gpu_extras.batch
import copy
import mathutils
import json 

from LevelEditor.Enum import ColliderType

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
             
            if False == object["isLineDraw"]:
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

        shader = gpu.shader.from_builtin("UNIFORM_COLOR")
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
        context.object["isLineDraw"] = False

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
            
            self.layout.prop(obj, '["isLineDraw"]', text="コライダーの線を描画するか")
            self.layout.prop(obj.collider_type, "collider_enum", text = "コライダーの種類")
            self.layout.prop(obj,'["collider_center"]',text = "Center")
            self.layout.prop(obj,'["collider_size"]',text = "Size")
            self.layout.separator()
            self.layout.prop(obj,'["collider_Line_Color"]',text = "線の色")      
        else:
            self.layout.operator(MYADDON_OT_add_collider.bl_idname)

