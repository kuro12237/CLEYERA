import bpy

bl_info={
    "name": "レベルエディタ",
    "author": "Ibu",
    "version": (1.0),
    "blender": (3,3,0),
    "location": "",
    "description": "レベルエディタ",
    "waning": "",
    "support": "TESTING",
    "wiki_url": "",
    "tracker_url": "",
    "category": "object"
}

def register():
    print("レベルエディタが有効化されました");

def unregister():
    print("レベルエディタが無効化されました")
    
if __name__ == "__main__":
   register()