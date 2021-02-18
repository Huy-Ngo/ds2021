import xmlrpc.client

proxy = xmlrpc.client.ServerProxy("http://localhost:8000/")
with open("logo.png", "wb") as handle: handle.write(proxy.logo().data)
