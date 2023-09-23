from socket import socket, AF_INET, SOCK_STREAM

host = "127.0.0.1"

with socket(AF_INET, SOCK_STREAM) as s:
    for i in range(65536):
        try:
            s.connect((host, i))
            print(f"{str(i)} is open")
        except:
            print(f"{str(i)} is closed")


