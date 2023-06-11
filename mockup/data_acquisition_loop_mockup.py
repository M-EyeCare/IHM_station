import PySide6.QtCore as QtCore
import random
from time import sleep

# DEFINITION DES MEMOIRES PARTAGEES

questionMem=QtCore.QSharedMemory("QUEST")
questionMem.create(32)
questionMem.attach()

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

activationMem = QtCore.QSharedMemory("ACT")
activationMem.create(4)
activationMem.attach()


while(1):

    if(activationMem.lock()):  # Verrouiller la mémoire partagée
        data=int(activationMem.data()[0])#RECUPERER LA VALEUR CORRESPONDANT A UN CAPTEUR (1,2,3,4)
        print(data)
        # #######COPIER POUR CHAQUER CAPTEUR###########
        if data==1:
            if bpmMem.lock():
            # FAIRE TRAITEMENT ICI 
                send=1000 #REMPLACER PAR LA VALEUR A ENVOYER
                bpmMem.data()[:3]=send.to_bytes(3,'little')#envoyer la valeur sur la memoire partagée
                bpmMem.unlock()
        # #######FIN DE LA PARTIE A COPIER#############
        activationMem.unlock()  # Déverrouiller la mémoire partagée
    
    if(questionMem.lock()):
        data=str(questionMem.data()[:32])
        print("QUESTION RESPONSES:")
        print(data)
        questionMem.unlock()


    sleep(0.05)


    