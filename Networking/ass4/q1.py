import os
import time
import random
import string

def id_generator(size=10, chars=string.ascii_uppercase + string.digits):
    string = ''.join(random.choice(chars) for _ in range(size))
    bytestring = string.encode()
    return bytestring 

def generate_input():
    input1 = id_generator()
    input2 = id_generator()
    input3 = id_generator()

    f1 = open('/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp1', 'wb')
    f2 = open('/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp2', 'wb')
    f3 = open('/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp3', 'wb')
    f1.write(input1)  
    f2.write(input2) 
    f3.write(input3)

    f1.close()
    f2.close()
    f3.close()

    return

def IPC_init():
    r1,w1 = os.pipe()
    r2,w2 = os.pipe()
    r3,w3 = os.pipe()
    
    return r1,r2,r3,w1,w2,w3

def STS_1_Tributary(pipein, pipeout,i):
    if i==1:
        f = open("/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp1", "rb")
    elif i==2:
        f = open("/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp2", "rb")
    else:
        f = open("/Users/anjishnu/Documents/GitHub/6th_sem/Networking/ass4/inp3", "rb")

    data = f.read()
    os.close(pipein)
    os.write(pipeout,data)
    A = data.decode('utf-8').strip()
    print("Input text :", A)  
    f.close()
    return

def Three_to_1_Multiplexer(r1,r2,r3,w1,w2,w3):
    os.close(w1)
    os.close(w2)
    os.close(w3)
    f1 = os.fdopen(r1)
    f2 = os.fdopen(r2)
    f3 = os.fdopen(r3)

    try:
        a = f1.read(1)
        b = f2.read(1)
        c = f3.read(1)
        frame = a+b+c
        byte_frame = frame.encode()
        count = 1
        while a and b and c:
            print("Frame " + str(count) + " : ", end='',flush=True)
            time.sleep(0.001)
            os.write(1,byte_frame)
            print(end='\n',flush=True)
            a = f1.read(1)
            b = f2.read(1)
            c = f3.read(1)
            frame = a+b+c
            byte_frame = frame.encode()
            count += 1
    finally:
        f1.close()
        f2.close()
        f3.close()

def kill_zombies(pid1,pid2,pid3,pid4):
    os.waitpid(pid1, 0)
    os.waitpid(pid2, 0)
    os.waitpid(pid3, 0)

def work():

    r1,r2,r3,w1,w2,w3 = IPC_init()

    pid1 = os.fork()
    if pid1 == 0:
        STS_1_Tributary(r1, w1, 1)
    
    else:
        pid2 = os.fork()
        if pid2 == 0:
            STS_1_Tributary(r2, w2, 2)

        else:
            pid3 = os.fork()
            if pid3 == 0:
                STS_1_Tributary(r3, w3, 3)
            
            else:
                pid4 = os.fork()
                if pid4 == 0:
                    Three_to_1_Multiplexer(r1,r2,r3,w1,w2,w3)
                else :
                    kill_zombies(pid1,pid2,pid3,pid4)

if __name__ == "__main__":
    generate_input()
    work()
    exit(0)