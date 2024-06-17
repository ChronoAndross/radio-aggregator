# echo-client.py
# only used for local testing
# adapted from https://realpython.com/python-sockets/

import socket
import sys
import time

if len(sys.argv) != 3:
    print("needs an address and port, example: echo client 0.0.0.0 6969")

HOST = sys.argv[1]  # The server's hostname or IP address
PORT = int(sys.argv[2])  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    print("connecting...")
    s.connect((HOST, PORT))
    print("connected to HOST=" + HOST + " PORT=" + str(PORT))
    s.send(b"conncted to python client")
    while True:
        data = s.recv(1024)
        if data is not None and len(data) > 0:
            print(f"Received {data!r}")
        else:
            print("data empty")
        print("wait 3 seconds")
        time.sleep(3)
        