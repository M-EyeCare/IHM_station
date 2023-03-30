import PySide6.QtCore as QtCore
import random

sharedMem=QtCore.QSharedMemory("BPM")
sharedMem.create(32)

sharedMem.attach()


while(1):

    # Lire des données depuis la mémoire partagée
    sharedMem.lock()  # Verrouiller la mémoire partagée
    data = int(sharedMem.data()[0])
    sharedMem.unlock()  # Déverrouiller la mémoire partagée
    
