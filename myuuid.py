#!/usr/bin/python3
from uuid import uuid4

class Basemodel:
    def __init__(self):
        self.id = str(uuid4())
mod_1 = Basemodel()
print(mod_1.id)

