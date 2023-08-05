#!/usr/bin/python3
import cmd
class myconsole(cmd.Cmd):
    prompt = "(Airbnb) "

if __name__ == '__main__':
    myconsole().cmdloop()
