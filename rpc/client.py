from os import fdopen
from sys import argv, stdout
import xmlrpc.client

prog, subcmd, *args = argv  # dispatch the command
proxy = xmlrpc.client.ServerProxy("http://localhost:8000/")
out = fdopen(stdout.fileno(), 'wb')  # no we don't have to close it manually
out.write(getattr(proxy, subcmd)(*args).data)
