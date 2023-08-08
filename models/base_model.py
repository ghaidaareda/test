#!/usr/bin/python3
"""
class BaseModel that defines all common 
attributes/methods for other classes
"""

from uuid import uuid4
from datetime import datetime
class BaseModel:
    """ main class of prject """
    def __init__(self):
        """ init method """
        self.id = str(uuid4())
        self.created_at = datetime.now()
        self.updated_at = datetime.now()

    def __str__(self):
        """ string representation of class """
        return f"[{self.__class__.__name__}]({self.id}) {self.__dict__}"
    
    def save(self):
        """ updates the public instance attribute updated_at"""
        self.updated_at = datetime.now()

    def to_dict(self):
        """ returns a dictionary containing all keys/values """
        my_dict = {key: value for key, value in self.__dict__.items()}
        my_dict["__class__"] = self.__class__.__name__
        my_dict["created_at"] = self.created_at.strftime("%Y-%m-%dT%H:%M:%S.%f")
        my_dict["updated_at"] = self.updated_at.strftime("%Y-%m-%dT%H:%M:%S.%f")

        return my_dict
