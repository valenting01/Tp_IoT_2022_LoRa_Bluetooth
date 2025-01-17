# Tp_IoT_2022_LoRa_Bluetooth

Réalisé par Valentin GAUTREAU, Joshua LUCAS, Amand MESSE, Erwan SENECHAL

Groupe TP SRT 2024

## Introduction
Ce code implémente une communication via LoRa et MQTT (Message Queuing Telemetry Transport) sur Wi-Fi.
Nous avons commencé par inclure les bibliothèques nécessaires pour le WiFi, le client MQTT, LoRa et l'affichage sur un écran OLED.
Puis nous avons définis les broches GPIO utilisées pour les connexions LoRa, ainsi qu'une structure de paquet pour stocker des données à recevoir et à envoyer.

Nous vous présentons les différences entre notre "Receiver" et "Sender".

## 1. Receiver

Dans la méthode setup(), nous avons mis en en place une connexion WiFi et une connexion au broker MQTT.
Nous avons également défini une fonction de rappel pour traiter les messages MQTT entrants. Une fois le message MQTT avec les paramètres LoRa récupéré par le "Sender", nous avons configuré et initialisé le LoRa avec la fréquence, le facteur SF et la largeur de bande.

Nous avons également défini une fonction pour gérer les paquets LoRa entrants que nous n'avons pas utilisé.

Enfin, la boucle loop(), gère la communication MQTT et envoie des paquets LoRa à intervalles régulières un fois avoir reçu les paramètres du "Sender".
 
## 2. Sender

Dans ce fichier, les paramètres de fréquence (freq), facteur SF, et bande passante du signal (sb) sont définis. Puis le code se connecte à un réseau Wi-Fi en utilisant les identifiants ssid et password fournis.
Puis dans la méthode setup(), nous avons également mis en en place une connexion WiFi et une connexion au broker MQTT. Si l'initialisation échoue, le programme entre dans une boucle infinie.

Dans la boucle loop(), toutes les 5 secondes, une fonction est définie pour publier un message MQTT toutes les 5 secondes avec un paramètre spécifié qui correspond au paramètres de fréquence, SF et la BP du signal qui servira au récepteur pour configurer son LoRa. Cette boucle gère également l'émission et la réception de données LoRa.

## 3. Schéma de l'échange
Voici un diagramme simplifié des échanges, en pointillé ce qui n'a pas été réalisé.
![Diagramme_TP](https://github.com/valenting01/Tp_IoT_2022_LoRa_Bluetooth/assets/42234363/a1199b3a-7d16-4a7e-8cbc-2ba44fb74410)
