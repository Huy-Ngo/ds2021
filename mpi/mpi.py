from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

if (rank == 0):
    f = open("logo-usth-pa3-01.png", "rb")
    data = f.read()
    comm.send(data, dest=1, tag=42)
elif (rank == 1):
    data = comm.recv(source=0, tag=42)
    f = open("logo.png", "wb")
    f.write(data)
    print(data)