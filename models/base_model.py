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
        self.id = str(uuid4())
        self.created_at = datetime.now()
        self.updated_at = datetime.now()

    def __str__(self):
        return f"[{self.__class__.__name__}]({self.id}) {self.__dict__}"
mod_1 = BaseModel()
print(mod_1)
