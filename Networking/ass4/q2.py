import os
import random
import string

def generate_data():
    string = 'Networking'
    payload = string.encode() 
    f = open('/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp4', 'wb')
    f.write(payload)
    f.close()
    return

def read_data():
    f1 = open('/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp4', 'rb')
    data = f1.read()
    A = data.decode('utf-8').strip()
    print("Input text :", A)  
    f1.close()
    return data

def coinToss(n=10000):
    heads = 0
    tails = 0
    for i in range(n):
        flip = random.randint(0,1)
        if (flip==0):  heads += 1
        else : tails+=1
    decision = 1 if heads > tails else 0
    return decision

def calculate_checksum(payload):
    n = 0
    for i in range(len(payload)):
        n += payload[i]
    n.to_bytes((n.bit_length() + 7) // 8, 'big') or b'\0'
    n = ~n
    print("Checksum : " + str(n))
    return n

def message(payload, checksum):
    message = []
    for i in range(len(payload)+1):
        if i==len(payload):
            message.append(checksum)
        else:
            message.append(payload[i])
    
    print(message)
    return

def checksum_receiver(payload, checksum):
    sum = 0
    for i in range(len(payload)+1):
        if i==len(payload):
            sum += checksum
        else:
            sum += payload[i]
    
    sum = ~sum
    print(sum)

def corrupted_message(payload,checksum):
    message = []
    sum = 0
    modified_index = random.randint(0,10)
    for i in range(len(payload)+1):
        if i==len(payload):
            message.append(checksum)
            sum += checksum
        else:
            if (i==modified_index):
                message.append(ord('z'))
            else:
                message.append(payload[i])
            sum += message[i]
    sum = ~sum
    print(message)
    print("Calculated checksum at receiver's end : ")
    print(sum)


def transmission(payload,checksum):
    corrupted = coinToss()
    if corrupted==0:
        
        print("--------------")

        print("Message transmitted : ")
        message(payload,checksum)

        print("Message received : ")
        message(payload,checksum)

        print("Calculated checksum at receiver's end : ")
        checksum_receiver(payload, checksum)

        print("--------------")
        print("Receiver side checksum=0. Hence, not corrupted")


    else:
        print("--------------")

        print("Message transmitted : ")
        message(payload,checksum)

        print("Message received : ")
        corrupted_message(payload,checksum)

        print("--------------")
        print("Receiver side checksum!=0 . Hence, corrupted")

if __name__ == "__main__":
    generate_data()
    payload = read_data()
    initial_checksum = calculate_checksum(payload)
    transmission(payload,initial_checksum)
    
