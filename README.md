# Tp_IoT_2022_LoRa_Bluetooth

Réalisé par Valentin GAUTREAU, Joshua LUCAS, Amand MESSE, Erwan SENECHAL

## 1. Receiver :

Ce code implémente une communication via LoRa et MQTT (Message Queuing Telemetry Transport) sur Wi-Fi.
Nous avons commencé par inclure les bibliothèques nécessaires pour le WiFi, le client MQTT, LoRa et l'affichage sur un écran OLED.
Puis nous avons définis les broches GPIO utilisées pour les connexions LoRa, ainsi qu'une structure de paquet pour stocker des données à recevoir.

Dans la méthode setup(), nous avons mis en en place une connexion WiFi et une connexion au broker MQTT.
Nous avons également défini une fonction de rappel pour traiter les messages MQTT entrants. Une fois le message MQTT avec les paramètres LoRa récupéré par le "Sender", nous avons configuré et initialisé le LoRa avec la fréquence, le facteur SF et la largeur de bande.

Nous avons également défini une fonction pour gérer les paquets LoRa entrants que nous n'avons pas utilisé.

Enfin, la boucle loop(), gère la communication MQTT, envoie des messages MQTT et des paquets LoRa à intervalles régulières.
 
## 2. Sender :
