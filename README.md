🏦 Système ATM - Distributeur Automatique de Billets
ATM System est une application console sophistiquée développée en C++ qui simule les opérations complètes d'un distributeur automatique de billets. Ce système offre une expérience bancaire sécurisée et intuitive pour la gestion des comptes clients.

✨ Fonctionnalités Principales
🔐 Sécurité et Authentification
Connexion sécurisée avec numéro de compte et code PIN

Validation robuste des identifiants

Protection contre les accès non autorisés

💰 Opérations Bancaires Complètes
Retrait Rapide : Montants prédéfinis pour un accès rapide

Retrait Personnalisé : Saisie libre du montant avec validation

Dépôt d'Argent : Alimentation du compte

Consultation de Solde : Affichage instantané du solde disponible

Déconnexion Sécurisée : Fermeture de session protégée

📊 Gestion des Données
Stockage persistant des informations clients

Mise à jour en temps réel des soldes

Architecture modulaire et extensible

🗂 Architecture du Projet
Structure des Fichiers
text
ATM_System/
├── ATM System.cpp          # Code source principal
├── Clients.txt             # Base de données des clients
├── ATM System.sln          # Solution Visual Studio
├── ATM System.vcxproj      # Projet Visual Studio
├── .vs/                    # Configuration IDE (ignorer)
└── x64/                    # Fichiers de compilation (ignorer)
Format du Fichier Clients.txt
Chaque client est enregistré selon le format structuré :

text
NumeroCompte#//#PIN#//#Nom#//#Téléphone#//#Solde
Exemple :

text
12345#//#1234#//#Lamrini Soufiane#//#0612345678#//#5000.00
67890#//#5678#//#Martin Claire#//#0623456789#//#3200.50
🚀 Guide d'Utilisation
Compilation et Exécution
Avec Visual Studio :
Ouvrir ATM System.sln

Compiler la solution (Build → Build Solution)

Exécuter le projet (Debug → Start Without Debugging)

Avec ligne de commande :
bash
g++ -std=c++11 "ATM System.cpp" -o atm_system
./atm_system
Processus de Connexion
Lancement de l'application

Saisie du numéro de compte

Entrée du code PIN

Accès au menu principal après validation

Navigation dans le Menu
text
=== MENU PRINCIPAL ATM ===
[1] Retrait Rapide
[2] Retrait Normal
[3] Dépôt
[4] Consulter Solde
[5] Déconnexion
==========================
🛠️ Fonctionnalités Techniques Avancées
Gestion des Transactions
Vérification des fonds suffisants avant retrait

Calcul automatique des nouveaux soldes

Validation des montants saisis

Sécurité Renforcée
Protection des données sensibles

Gestion sécurisée des fichiers

Architecture modulaire pour maintenance facile

Interface Utilisateur
Menus intuitifs et ergonomiques

Messages d'erreur explicites

Navigation fluide entre les options

🔮 Améliorations Futures
Fonctionnalités Planifiées
Création de comptes : Inscription de nouveaux clients

Gestion administrateur : Interface de gestion complète

Historique des transactions : Journal détaillé des opérations

Transferts entre comptes : Virements internes

Changement de PIN : Mise à jour sécurisée du code secret

Interface graphique : Version Windows Forms ou Qt

Système de logs : Traçabilité complète des opérations

Alertes de sécurité : Notifications pour activités suspectes

Optimisations Techniques
Chiffrement des données sensibles

Sauvegarde automatique des données

Systeme de recovery en cas d'erreur

Interface multilingue

Support des devises multiples

⚠️ Notes Importantes
Configuration Requise
Le fichier Clients.txt doit être présent dans le répertoire d'exécution

Accès en lecture/écriture nécessaire pour le fichier des clients

Compilateur C++11 ou supérieur recommandé

Gestion des Fichiers
Le dossier .vs/ et x64/ doivent être exclus du versioning

Utiliser un fichier .gitignore approprié :

text
.vs/
x64/
*.user
*.aps
🎓 Objectifs Pédagogiques
Ce projet démontre la maîtrise de :

Programmation C++ moderne avec gestion des fichiers

Concepts de sécurité et authentification

Architecture logicielle modulaire

Gestion d'erreurs et validation des entrées

Interface utilisateur en mode console

Manipulation de données persistantes
