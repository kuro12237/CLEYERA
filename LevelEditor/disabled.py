import bpy


class MYADDON_OT_Disabled(bpy.types.Operator):
    bl_idname = "myaddon.disabled"
    bl_label = "DisabledFlag"
    bl_description = "flagManager"
    bl_options = {"REGISTER", "UNDO"}


    def execute(self, context):
        obj = context.object
        obj["disabled_Flag"] = False
        return {"FINISHED"}


class OBJECT_PT_Disabled(bpy.types.Panel):
    """ 無効化フラグパネル """

    bl_idname = "OBJECT_PT_Disabled"
    bl_label = "DisabledFlagPanel"
    bl_space_type = "PROPERTIES" 
    bl_region_type = "WINDOW"
    bl_context = "object"

    def draw(self,context):
        obj = context.object

        if "disabled_Flag" in obj:
            self.layout.prop(obj, '["disabled_Flag"]', text="オブジェクトをExportする時にfalse")
        else:
            self.layout.operator(MYADDON_OT_Disabled.bl_idname)
            