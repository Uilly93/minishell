# Minishell

Minishell est un projet de l’école **42** qui consiste à recréer un interpréteur de commandes simplifié, en reproduisant certaines fonctionnalités principales de **bash**. Ce projet permet de mieux comprendre le fonctionnement des **processus**, des **pipes**, de la **gestion des signaux**, et de la **programmation système en C**.

---

## 🎯 Objectifs du projet

- Comprendre le fonctionnement d’un shell.
- Manipuler les processus et la communication inter-processus.
- Gérer la mémoire et éviter les fuites.
- Implémenter une boucle de lecture → évaluation → exécution.
- Gérer les signaux (Ctrl+C, Ctrl+\\ et Ctrl+D).
- Gestion dynamique d'un environnement.

---

## ⚙️ Fonctionnalités

Le minishell doit :

- Afficher un prompt en attente d’une commande.
- Exécuter des commandes simples (ex : `ls`, `echo`, etc.).
- Gérer les chemins relatifs et absolus.
- Implémenter les **builtins** :
  - `echo` (avec option `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Gérer les **redirections** :
  - `>` (sortie)
  - `>>` (sortie append)
  - `<` (entrée)
  - `<<` (heredoc)
- Gérer les **pipes** (`|`).
- Gérer les **variables d’environnement** (`$VAR`).
- Gérer les **quotes** (`'` et `"`).
- Gérer les **signaux** :
  - `Ctrl-C` interrompt la commande en cours sans quitter le shell.
  - `Ctrl-\\` est ignoré.
  - `Ctrl-D` ferme le shell.

---

## 🛠️ Compilation

Un **Makefile** est fourni avec les règles :

```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime les objets et l’exécutable
make re     # Recompile tout
```

Cela génère un exécutable :

```bash
./minishell
```

---

## 🔍 Exemple d’utilisation

<img width="693" height="347" alt="image" src="https://github.com/user-attachments/assets/b3325f17-fbfe-4638-8160-9d6099a40e0d" />

