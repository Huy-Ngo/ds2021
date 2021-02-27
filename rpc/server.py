from pathlib import Path
from xmlrpc.client import Binary
from xmlrpc.server import SimpleXMLRPCServer

path = Path(__file__).parent.parent / 'logo-usth-pa3-01.png'
with open(path, 'rb') as f: logo = Binary(f.read())
server = SimpleXMLRPCServer(("localhost", 8000))
print("Listening on port 8000...")
server.register_function(lambda: logo, 'logo')
server.serve_forever()