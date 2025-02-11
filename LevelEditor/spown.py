import bpy
import bpy.ops
import os
from bpy.props import StringProperty

class SpawnNames():
    # インデックス
    PROTOTYPE = 0 # プロトタイプのオブジェクト名
    INSTANCE = 1 # 量産時のオブジェクト名
    FILENAME = 2 # リソースのファイル名

    names = {}
   
# 読み込む
class MYADDON_OT_load_spawn(bpy.types.Operator):
    bl_idname = "myaddon.myaddon_ot_load_spawn_"
    bl_label = "出現ポイントシンボルImport"
    bl_description = "出現ポイントのシンボルをImportします"
    prototype_object_name = "ProttypeSpawn"
    object_name = "Spawn"

    def load_obj(self, type):
        print("出現ポイントのシンボルをImportします")

        # 重複ロードを防止
        spawn_object = bpy.data.objects.get(SpawnNames.names[type][SpawnNames.PROTOTYPE])
        if spawn_object is not None:
            return {'CANCELLED'}
    
        addon_directory = os.path.dirname(__file__)
        relative_path = "player/player.obj"
        full_path = os.path.join(addon_directory,relative_path)
        bpy.ops.wm.obj_import('EXEC_DEFAULT',filepath=full_path,display_type='THUMBNAIL',forward_axis='Z',up_axis='Y')
        bpy.ops.object.transform_apply(location=False,rotation=True,scale=False,properties=False)
        
        # set
        object = bpy.context.active_object
        object.name = SpawnNames.names[type][SpawnNames.PROTOTYPE]
        object["type"]=SpawnNames.names[type][SpawnNames.INSTANCE]
        object["objectName"]=type
   
        bpy.context.collection.objects.unlink(object)

        return {"FINISHED"}
    
    def execute(self,context):
        # Enemyオブジェクト読み込み
        self.load_obj("Enemy")
        # Playerオブジェクト読み込み
        self.load_obj("Player")
        
        return {"FINISHED"}
    
# 作成・配置する
class MYADDON_OT_create_spawn(bpy.types.Operator):
    bl_idname = "myaddon.myaddon_ot_create_spawn"
    bl_label = "出現ポイントシンボルの作成"
    bl_description = "出現ポイントのシンボルを制作します"
    bl_options = {'REGISTER','UNDO'}

    type: bpy.props.StringProperty(name="Type", default="Player")

    def execute(self, context):
        # 検索
        spawn_object = bpy.data.objects.get(SpawnNames.names[self.type][SpawnNames.PROTOTYPE])

        # まだ読み込んでいない場合
        if spawn_object is None:
            bpy.ops.myaddon.myaddon_ot_spawn_import_symbol('EXEC_DEFAULT')
            spawn_object = bpy.data.objects.get(SpawnNames.names[self.type][SpawnNames.PROTOTYPE])
        
        print("出現ポイントのシンボルを制作します")

        bpy.ops.object.select_all(action = 'DESELECT')
        
        object = spawn_object.copy()

        bpy.context.collection.objects.link(object)
        object.name = SpawnNames.names[self.type][SpawnNames.INSTANCE]

        return {"FINISHED"}
    
class MYADDON_OT_spawn_create_player(bpy.types.Operator):

    bl_idname = "myaddon.myaddon_ot_spawn_create_player"
    bl_label = "プレイヤーの出現シンボルの作成"
    bl_description = "プレイヤー出現ポイントのシンボルを作成します"
    bl_options = {'REGISTER','UNDO'}

    def execute(self,context):
        bpy.ops.myaddon.myaddon_ot_create_spawn('EXEC_DEFAULT',type="Player")
        
        return {"FINISHED"}


class MYADDON_OT_spawn_create_player_menu(bpy.types.Menu):
    bl_idname = "MYADDON_OT_spawn_create_player_menu"
    bl_label="プレイヤーの出現ポイントの作成"
    bl_description="プレイヤーの出現ポイントの作成します"
    bl_options = {'REGISTER','UNDO'}

    def draw(self, context):
        layout = self.layout
        layout.operator(MYADDON_OT_spawn_create_player.bl_idname, text="プレイヤーの出現ポイントを作成")


class MYADDON_OT_spawn_create_enemy(bpy.types.Operator):

    bl_idname = "myaddon.myaddon_ot_spawn_create_enemy"
    bl_label = "敵の出現シンボルの作成"
    bl_description = "敵出現ポイントのシンボルを作成します"

    def execute(self,context):
        bpy.ops.myaddon.myaddon_ot_create_spawn('EXEC_DEFAULT',type="Enemy")
        
        return {"FINISHED"}

class MYADDON_OT_spawn_create_enemy_menu(bpy.types.Menu):
    bl_idname ="MYADDON_OT_spawn_create_enemy_menu"
    bl_label="エネミーの出現ポイントの作成"
    bl_description="プレイヤエネミーの出現ポイントの作成します"

    def draw(self, context):
        layout = self.layout
        layout.operator(MYADDON_OT_spawn_create_enemy.bl_idname, text="エネミーの出現ポイントを作成")