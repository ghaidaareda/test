#!/usr/bin/python3
"""
class BaseModel that defines all common 
attributes/methods for other classes
"""

from uuid import uuid4
from datetime import datetime
from models import storage
class BaseModel:
    """ main class of prject """
    def __init__(self, *args, **kwargs):
        """ init method """
        if kwargs:
            for key in kwargs:
                if key == '__class__':
                    continue
                elif key == "created_at":
                    self.__dict__["created_at"] = datetime.fromisoformat(kwargs["created_at"])
                elif key == "updated_at":
                    self.__dict__["updated_at"] = datetime.fromisoformat(kwargs["updated_at"])
                else:
                    self.__dict__[key] = kwargs[key]
        else:
            self.id = str(uuid4())
            self.created_at = datetime.now()
            self.updated_at = datetime.now()
            storage.new(self)
    def __str__(self):
        """ string representation of class """
        return f"[{self.__class__.__name__}]({self.id}) {self.__dict__}"
    
    def save(self):
        """ updates the public instance attribute updated_at"""
        self.updated_at = datetime.now()
        storage.save()

    def to_dict(self):
        """ returns a dictionary containing all keys/values """
        my_dict = self.__dict__.copy()
        my_dict["__class__"] = self.__class__.__name__
        my_dict["created_at"] = self.created_at.strftime("%Y-%m-%dT%H:%M:%S.%f")
        my_dict["updated_at"] = self.updated_at.strftime("%Y-%m-%dT%H:%M:%S.%f")

        return my_dict
