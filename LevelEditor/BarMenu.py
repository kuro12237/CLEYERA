import bpy
from LevelEditor.ExportScene import MYADDON_OT_export_scene

class TOPBAR_MT_my_menu(bpy.types.Menu):
    bl_idname = "TOPBAR_MT_my_menu"
    bl_label = "MyMenu"
    bl_description="拡張メニュー by"
    
    def draw(self,context):
        self.layout.operator(MYADDON_OT_export_scene.bl_idname,text = MYADDON_OT_export_scene.bl_label)
    
    
    def submenu(self,context):
        self.layout.menu(TOPBAR_MT_my_menu.bl_idname)
    
    def submenuExport(self,context):
        self.layout.menu(MYADDON_OT_export_scene.bl_idname)
