import PySide6.QtCore as QtCore
import random
from time import sleep

bpmMem=QtCore.QSharedMemory("BPM")
bpmMem.create(32)
bpmMem.attach()

tempMem=QtCore.QSharedMemory("TEMP")
tempMem.create(32)
tempMem.attach()

breathMem=QtCore.QSharedMemory("BREATH")
breathMem.create(32)
breathMem.attach()

sweatingMem=QtCore.QSharedMemory("SWEATING")
sweatingMem.create(32)
sweatingMem.attach()

while(1):
    rand=random.randint(70,170)
    bpmMem.lock()
    bpmMem.data()[0]=rand
    bpmMem.unlock()

    rand=random.randint(70,170)
    tempMem.lock()
    tempMem.data()[0]=rand
    tempMem.unlock()

    rand=random.randint(70,170)
    breathMem.lock()
    breathMem.data()[0]=rand
    breathMem.unlock()

    rand=random.randint(70,170)
    sweatingMem.lock()
    sweatingMem.data()[0]=rand
    sweatingMem.unlock()
    
    sleep(0.05)
