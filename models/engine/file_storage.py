#!/usr/bin/python3
""" 
FileStorage that serializes instances to a JSON file 
and deserializes JSON file to instances
"""
import json

class FileStorage:
    """
    serializes instances to a JSON file
    deserializes JSON file to instances
    """
    __file_path = "file.json"
    __objects = {}
    
    def all(self):
        """ returns the dictionary __objects"""
        return FileStorage.__objects

    def new(self, obj):
        """ set the key, value pair in __objects """
        FileStorage.__objects[f"{obj.__class__.__name__}.{obj.id}"] = obj

    def save(self):
        """ serializes __objects to the JSON file (path: __file_path)"""
        with open(FileStorage.__file_path, "w",encoding="utf-8") as f:
            d = {key: value.to_dict() for key, value in FileStorage.__objects.items()}
            json.dump(d, f)

    def reload(self):
        """ deserializes the JSON file to __objects """
        from models.base_model import BaseModel
        my_classes = {'BaseModel': BaseModel}
        try:
            with open(FileStorage.__file_path, "r", encoding="utf-8")as f:
                new_dict = json.load(f)
                for value in new_dict.values():
                    cls_name = value["__class__"]
                    cls_obj = my_classes[cls_name]
                    self.new(cls_obj(**value))
        except FileNotFoundError:
                pass






