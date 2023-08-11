#!/usr/bin/python3
"""console the command interpreter"""

import cmd
from models import storage
from models.base_model import BaseModel
from models.amenity import Amenity
from models.city import City
from models.place import Place
from models.review import Review
from models.state import State
from models.user import User


class HBNBCommand(cmd.Cmd):
    """class to read command line interpreter"""
    prompt = "(hbnb) "
    __cls = ['BaseModel', 'User', 'City', 'Place', 'State', 'Amenity',
             'Review']

    def do_EOF(self, line):
        """EOF command(^D) to exit the program
        """
        print()
        return True

    def do_quit(self, line):
        """Quit command to exit the program
        """
        return True

    def emptyline(self):
        """if no command enter return prompt again """
        pass

    def do_create(self, line):
        """create an instance if class model exists,
        save it to json file and print ID
        """
        if not line:
            print("** class name missing **")
            return None
        elif line not in self.__cls:
            print("** class doesn't exist **")
            return None
        else:
            new_inst = eval(line + "()")
            print(new_inst.id)
            new_inst.save()

    def do_show(self, line):
        """Prints the string representation of an instance based of ID
        """
        args = line.split()
        if len(args) == 0:
            print("** class name missing **")
            return None
        elif args[0] not in self.__cls:
            print("** class doesn't exist **")
            return None
        elif len(args) == 1:
            print("** instance id missing **")
            return None
        else:
            obj = storage.all()
            key = args[0] + "." + args[1]
            if obj.get(key, False):
                value = obj[key]
                print(value)
            else:
                print("** no instance found **")

    def do_destroy(self, line):
        """Deletes an instance based on the class name and id
        """
        args = line.split()
        if len(args) == 0:
            print("** class name missing **")
            return None
        elif args[0] not in self.__cls:
            print("** class doesn't exist **")
            return None
        elif len(args) == 1:
            print("** instance id missing **")
            return None
        else:
            obj = storage.all()
            key = args[0] + "." + args[1]
            if obj.get(key, False):
                obj.pop(key)
                storage.save()
            else:
                print("** no instance found **")

    def do_all(self, line):
        """ Prints all string representation of all instances based on
        or not on the class name
        """
        args = line.split()
        o_list = []
        objs = storage.all()
        if not line:
            o_list = [str(value) for value in objs.values()]
            print(o_list)
        elif args[0] not in self.__cls:
            print("** class doesn't exist **")
            return None
        else:
            o_list = [str(v) for k, v in objs.items() if k.startswith(args[0])]
            print(o_list)

    def do_update(self, line):
        """Updates an instance based on the class name and id
        by adding or updating attribute
        <class name> <id> <attribute name> "<attribute value>"
        """
        args = line.split()
        if len(args) == 0:
            print("** class name missing **")
            return None
        elif args[0] not in self.__cls:
            print("** class doesn't exist **")
            return None
        elif len(args) == 1:
            print("** instance id missing **")
            return None
        elif f"{args[0]}.{args[1]}" not in storage.all():
            print("** no instance found **")
            return
        elif len(args) == 2:
            print("** attribute name missing **")
            return
        elif len(args) == 3:
            print("** value missing **")
        else:
            obj_key = args[0] + "." + args[1]
            obj = storage.all()[obj_key]
            obj_attr = args[2]
            attr_value = args[3]
            if attr_value[0] == '"':
                attr_value = attr_value[1:-1]
            if hasattr(obj, obj_attr):
                val_type = type(getattr(obj, obj_attr))
                if val_type in [str, float, int]:
                    attr_value = val_type(attr_value)
                    setattr(obj, obj_attr, attr_value)
            else:
                setattr(obj, obj_attr, attr_value)
            storage.save()


if __name__ == '__main__':
    HBNBCommand = HBNBCommand()
    if not sys.stdin.isatty():
        for line in sys.stdin:
            HBNBCommand.the_cmd(line.strip())
    else:
        HBNBCommand().cmdloop()
