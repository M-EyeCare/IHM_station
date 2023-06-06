import PySide6.QtCore as QtCore
import random
from time import sleep

bpmMem=QtCore.QSharedMemory("BPM")
bpmMem.create(4)
bpmMem.attach()


tempMem=QtCore.QSharedMemory("TEMP")
tempMem.create(4)
tempMem.attach()

breathMem=QtCore.QSharedMemory("BREATH")
breathMem.create(4)
breathMem.attach()

sweatingMem=QtCore.QSharedMemory("SWEATING")
sweatingMem.create(4)
sweatingMem.attach()

activationMem = QtCore.QSharedMemory("activation")
activationMem.create(4)
activationMem.attach()



while(1):
    rand=random.randint(70,170)
    if bpmMem.lock():
        print(rand)
        bpmMem.data()[0]=rand
        bpmMem.unlock()

    rand=random.randint(70,170)
    if tempMem.lock():
        tempMem.data()[0]=rand
        tempMem.unlock()

    rand=random.randint(70,170)
    if breathMem.lock():
        breathMem.data()[0]=rand
        breathMem.unlock()

    rand=random.randint(70,170)
    if sweatingMem.lock():
        sweatingMem.data()[0]=rand
        sweatingMem.unlock()
    
    sleep(0.05)
