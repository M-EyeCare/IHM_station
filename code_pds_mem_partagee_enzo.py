import serial
import codebug_tether
import time
import mysql.connector
from datetime import datetime
from time import strftime
#from smartcard.System import readers
#from smartcard.util import toHexString
import PySide6.QtCore as QtCore
import random
from time import sleep

# DEFINITION DES MEMOIRES PARTAGEES
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

questionMem = QtCore.QSharedMemory("QUEST")
questionMem.create(100)
questionMem.attach()

#validationMem = QtCore.QSharedMemory("VAL")
#validationMem.create(4)
#validationMem.attach()

# variables pour recuperer les infos sur la tablette -> A INITIALISER A FALSE
debut_diag = True

# variables pour le deroulement du diag
diag_pulse = False
diag_temp = False
diag_sud = False
diag_press = False

# variables pour le lecteur de carte a puce
inserted = False

def analyse_questions(texte):
    # je suis censee recevoir un string de la forme "0;0;1;1;..."
    # je vais devoir le separer et faire l'analyse pour emma
    # nombre de questions : 12
    print(texte)
    ressenti = ""
    valeurs = texte.split(";")

    if len(valeurs) > 1:
        if(valeurs[0]=="1"):
            # question : Ressentez-vous des douleurs ?
            ressenti = ressenti + "Douleurs. "
            print("Douleurs. ")

        if(valeurs[1]=="1"):
            # question : Ressentez-vous des douleurs au crane ?
            ressenti = ressenti + "Douleurs au crane. "
            print("Douleurs au crane. ")

        if(valeurs[2]=="1"):
            # question : Ressentez-vous des douleurs au ventre ?
            ressenti = ressenti + "Douleurs au ventre. "
            print("Douleurs au ventre. ")

        if(valeurs[3]=="1"):
            # question : Ressentez-vous des douleurs au dos ?
            ressenti = ressenti + "Douleurs au dos. "
            print("Douleurs au dos. ")
        
        if(valeurs[4]=="1"):
            # question : Ressentez-vous des douleurs a la gorge ?
            ressenti = ressenti + "Douleurs a la gorge. "
            print("Douleurs a la gorge. ")
        
        if(valeurs[5]=="1"):
            # question : Avez-vous une respiration douloureuse ?
            ressenti = ressenti + "Respiration douloureuse. "
            print("Respiration douloureuse. ")
        
        if(valeurs[6]=="1"):
            # question : Avez-vous des douleurs autres que celles enoncees precedemment ?
            ressenti = ressenti + "Autres douleurs. "
            print("Autres douleurs. ")
        
        if(valeurs[7]=="1"):
            # question : Avez-vous des nausees ?
            ressenti = ressenti + "Presence de nausees. "
            print("Presence de nausees. ")
        
        if(valeurs[8]=="1"):
            # question : Ressentez-vous une fatigue ?
            ressenti = ressenti + "Ressenti de fatigue. "
            print("Ressenti de fatigue. ")
        
        if(valeurs[9]=="1"):
            # question : Avez-vous des troubles du sommeil ?
            ressenti = ressenti + "Troubles du sommeil. "
            print("Troubles du sommeil. ")
        
        if(valeurs[10]=="1"):
            # question : Suivez-vous actuellement un traitement ?
            ressenti = ressenti + "Le patient suit actuellement un traitement. "
            print("Le patient suit actuellement un traitement. ")
        
        if(valeurs[11]=="1"):
            # question : Avez-vous des eruptions cutanees ?
            ressenti = ressenti + "Presence d'eruptions cutanees. "
            print("Presence d'eruptions cutanees. ")
        
        if(valeurs[12]=="1"):
            # question : etes-vous fumeur ?
            ressenti = ressenti + "Patient fumeur. "
            print("Patient fumeur. ")
    else:
        print("Problème de réception du ressenti du patient.")       
        ressenti = "Problème de transmission des données."
    return ressenti
        


# fonction de connexion au lecteur de carte a puce, la carte doit deja etre inseree
def con_carte():
    """
    sc_readers=readers()
    connection = sc_readers[0].createConnection()
    connection.connect() 

    # lecture de l'identifiant du patient
    APDUcmd=[0x80, 0xBE, 0x00, 0x10, 0x04]
    data, sw1, sw2 = connection.transmit(APDUcmd)
    id_patient = data[3]
    print("L'identifiant du patient est : ",id_patient)
    connection.disconnect()
    return id_patient"""
    return 3
    

# fonction d'envoi des donnees a la BD
def com_bd(res_pulse, res_temp, res_sud, res_press, ressenti):
    
    # connexion a la base de donnees
    conn = mysql.connector.connect(user="311698",password="phpMEyeConsult",host="mysql-meyeconsult.alwaysdata.net",port=3306,database="meyeconsult_diagnostic")
    cursor=conn.cursor(buffered=True)
    
    # date a recuperer sur le moment
    date = datetime.now().date()
    
    # file c'est la photo de l'image retinienne, a choisir au hasard
    file='raspi.jpg'
    
    # convertir l'image au format binaire BLOB pour la base de donnees
    with open(file, 'rb') as myfile:
        blobFile = myfile.read()
    
    # id du patient a recuperer -> carte vitale ou ecran tactile
    id_patient = con_carte()
    
    # id de la consultation, max +1 
    cursor.execute("SELECT MAX(id) FROM CONSULTS")
    conn.commit()
    res = cursor.fetchone()
    for resultat in res :
        id_consult = resultat + 1
    
    # resultats de la consultation
    temp = res_temp
    pulse = res_pulse
    sud = res_sud
    press = res_press
    
    # recuperation de l'id resultat, ligne dans la table RESULTS a creer
    cursor.execute("SELECT MAX(id) FROM RESULTS")
    conn.commit()
    res = cursor.fetchone()
    for resultat in res :
        id_result = resultat + 1
    
    #recuperation des resultats des questions
    texte = "?"
    
    # on remplit la table RESULTS
    diabetes = False
    dmla = False
    report = ""
    validated = False
    id_doctor = None
    ref1 = (id_result,diabetes,dmla,report,validated,id_doctor)
    cursor.execute("INSERT INTO RESULTS(id, diabetes, dmla, report, validated, idDoctor) VALUES (%s, %s, %s, %s, %s, %s)",ref1)
    conn.commit()

    # recuperer les observations du questionnaire de l'ecran tactile
    #obs = analyse_questions(texte)
    obs=ressenti
    
    # envoie a la bd
    reference = (id_consult, id_patient, date, temp, pulse, press, sud, blobFile, id_result, obs)
    cursor.execute("INSERT INTO CONSULTS(id, idPatient, dateConsult, temperature, heartRate, breathing, sweating, eye, idResult, observations) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)",reference)
    
    conn.commit()
    cursor.close()
    conn.close()
    print("Envoi en base de données terminé.")

def main():
    # utilisation des variables globales
    global debut_diag
    global diag_pulse
    global diag_temp
    global diag_sud
    global diag_press
    
    # connexion avec l'arduino
    # ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    if ser.isOpen():
        print("La connexion série est ouverte.")
    else:
        print("Impossible d'ouvrir la connexion série.")
    
    # variable pour le capteur de pression
    cpm=0
    
    while True:
        
        #if(bouton_appuye == True):
        #    debut_diag=True

        
        
        # si le bouton "debut diag" a ete enclenche
        if(debut_diag==True and activationMem.lock()):

            #print("En attente de commande")
            # Recuperation la valeur en memoire partagee
            data=int(activationMem.data()[0])
            #data_quest=int(validationMem.data()[0])

            #print(data_quest)

            # on envoie le message a l'arduino
            ser.write(repr(data).encode('utf-8'))

            # capteur cardiaque
            if(data==1):
                print(data)
                if bpmMem.lock():
                    print("waiting for the result")
                    time.sleep(17)
                    line = ser.readline().decode('utf-8').rstrip()
                    if(line!=""):
                        print(line)
                        line=int(line)
                        diag_pulse = True
                        res_pulse=line
                        if(line>110):
                            print("--> Tachycardie !")
                        elif(line<50):
                            print("--> Bradycardie !")
                        else:
                            print("RAS")
                        
                        send=int(res_pulse*10)
                        bpmMem.data()[:3]=send.to_bytes(3,'little')#envoyer la valeur sur la memoire partagee
                        bpmMem.unlock()

            # capteur de temperature
            elif(data==2):
                print(data)
                if tempMem.lock():
                    print("waiting for the result")
                    time.sleep(92)
                    line = ser.readline().decode('utf-8').rstrip()
                    if(line!=""):
                        print(line)
                        line=float(line)
                        diag_temp = True
                        res_temp=line
                        if(line>=35.5 and line<=38.5):
                            print("RAS")
                        elif(line<35.5 and line>=34.5):
                            print("--> Inconfort a surveiller ")
                        elif(line<34.5 and line>=31.5):
                            print("--> Hypothermie legere ")
                        elif(line<31.5):
                            print("--> Hypothermie ! ")
                        elif(line<=39.5 and line>38.5):
                            print("--> Fievre legere ")
                        elif(line<=40.5 and line>39.5):
                            print("--> Fievre severe ")
                        else :
                            print("Redemander la mesure")
                        send=int(res_temp*10)
                        tempMem.data()[:3]=send.to_bytes(3,'little')#envoyer la valeur sur la memoire partagee
                        tempMem.unlock()
            
            # capteur de sudation
            elif(data==3):
                print(data)
                if sweatingMem.lock():
                    print("waiting for the result")
                    time.sleep(11)
                    line = ser.readline().decode('utf-8').rstrip()
                    if(line!=""):
                        print(line)
                        line=int(line)
                        diag_sud = True
                        res_sud=line
                        if(line<=700 or line>=300):
                            print("RAS")
                        elif(line>700):
                            print("--> Sudation anormalement haute")
                        elif(line<300):
                            print("--> Sudation anormalement basse")
                        send=int(res_sud*10) 
                        sweatingMem.data()[:3]=send.to_bytes(3,'little')#envoyer la valeur sur la memoire partagee
                        sweatingMem.unlock()
            # capteur de pression
            elif(data==4):
                print(data)
                if breathMem.lock():
                    print("waiting for the result")
                    time.sleep(30)
                    # recuperation age
                    id_patient = con_carte()
                    conn = mysql.connector.connect(user="311698",password="phpMEyeConsult",host="mysql-meyeconsult.alwaysdata.net",port=3306,database="meyeconsult_diagnostic")
                    cursor=conn.cursor(buffered=True)
                    cursor.execute("SELECT age FROM PATIENTS WHERE id=%s",(id_patient,))
                    conn.commit()
                    res = cursor.fetchone()
                    for resultat in res :
                        age = resultat 
                        print("age : ",age)
                    cursor.close()
                    conn.close()
                    line = ser.readline().decode('utf-8').rstrip()
                    if(line!=""):
                        print(line)
                        diag_press = True
                        cpm=2*int(line)
                        res_press=cpm
                        if(age>14):
                            if((cpm>=12) and (cpm<=20)):
                                print("RAS")
                            elif(cpm>20):
                                print("--> Tachypnee ! ")
                            elif(cpm<12):
                                print("--> Bradypnee ! ")
                        send=int(res_press *10)
                        breathMem.data()[:3]=send.to_bytes(3,'little')#envoyer la valeur sur la memoire partagee
                        breathMem.unlock()
            
            # si toutes les infos sont recuperees, on envoie a la bd
            if((diag_pulse==True)and(diag_temp==True)and(diag_sud==True)and(diag_press==True)):
                # on remet les signaux a false
                # on indique la fin du diag, on attend que le bouton soit de nouveau appuye
                #debut_diag = false
                # on envoie a la bd
                print("Fin du diagnostic")

                sleep(3)

                if(questionMem.lock()):

                    source = questionMem.data()
                    data = bytes(source).decode('utf-8') 
                    print(data)
                    ressenti = analyse_questions(data)
                    print("Envoi des donnees en base de donnees")
                    com_bd(res_pulse, res_temp, res_sud, res_press, ressenti)
                    diag_pulse = False
                    diag_temp = False
                    diag_sud = False
                    diag_press = False
                    questionMem.unlock()




                    """
                    texte=str(questionMem.data(),encoding="utf-8")
                    print("QUESTION RESPONSES:")
                    print(texte)
                    questionMem.unlock()
                    ressenti = analyse_questions(texte)
                    print("Envoi des donnees en base de donnees")
                    com_bd(res_pulse, res_temp, res_sud, res_press, ressenti)
                    diag_pulse = False
                    diag_temp = False
                    diag_sud = False
                    diag_press = False"""
                else:
                    sleep(0.5)
                    print("en attente que le verrou soit libre")
            
            activationMem.unlock()  # Deverrouiller la memoire partagee
        else:
            print("Problème de verrou ou diagnostic mal terminé")
        sleep(0.05)

main()
