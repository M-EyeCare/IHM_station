import PySide6.QtCore as QtCore
import random
from time import sleep

sharedMem=QtCore.QSharedMemory("BPM")
sharedMem.create(32)
sharedMem.attach()

while(1):
    rand=random.randint(70,170)
    sharedMem.lock()
    sharedMem.data()[0]=rand
    sharedMem.unlock()
    sleep(0.1)
