from os import walk
from os.path import abspath, join
from pathlib import Path
from sys import argv
from xmlrpc.client import Binary
from xmlrpc.server import SimpleXMLRPCServer

if len(argv) != 2:
    print(f'usage: {argv[0]} DIR')
    exit()
prefix = abspath(argv[1])
paths = [join(parent, filename)[len(prefix)+1:]
         for parent, folders, files in walk(prefix)
         for filename in files]
path_str = ('\n'.join(paths) + '\n').encode()


def cat(file):
    """Return the file content if permitted."""
    if file not in paths: raise FileNotFoundError
    return Path(join(prefix, file)).read_bytes()


server = SimpleXMLRPCServer(("localhost", 8000))
server.register_function(lambda: path_str, 'ls')
server.register_function(cat, 'cat')
print("Listening on port 8000...")
server.serve_forever()
