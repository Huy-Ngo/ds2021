
from mpi4py import MPI

rank = MPI.COMM_WORLD.Get_rank()

def log(msg, *args):
    if rank == 0:
        print (msg % args)

# establish communication
info = MPI.INFO_NULL
port = MPI.Open_port(info)
root = 0

service = 'chat client'
MPI.Publish_name(service, info, port)
log("published service: '%s'", service)

log('waiting for client connection...')
comm = MPI.COMM_WORLD.Accept(port, info, root)
log('client connected...')

while True:
    done = False
    if rank == root:
        message = comm.recv(source=0, tag=0)
        if message is None:
            done = True
        else:
            try:
                print ("message: %r" % message)
            except StandardError:
                print ("invalid expression: %s" % message)
    done = MPI.COMM_WORLD.bcast(done, root)
    if done:
        break

log('disconnecting client...')
comm.Disconnect()

log('upublishing service...')
MPI.Unpublish_name(service, info, port)

log('closing port...')
MPI.Close_port(port)