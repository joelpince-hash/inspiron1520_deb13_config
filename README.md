# 🐧 Configurations Noyau Linux Optimisées (Refurbished Laptops)

Ce dépôt héberge les fichiers de configuration (`.config`) du noyau Linux (Kernel), optimisés spécifiquement pour des ordinateurs portables professionnels d'ancienne génération reconditionnés.

## 🎯 L'Objectif
L'idée est de prolonger la durée de vie de matériel informatique de qualité (Dell Latitude, Inspiron, ThinkPad...) qui ne supporte plus Windows 11.
Ces configurations sont destinées à **Debian Stable**. Elles visent à produire un système :
* **Ultra-léger :** Suppression des pilotes inutiles et du "bloatware" du noyau générique.
* **Performant :** Optimisation spécifique au processeur (CPU) et au matériel de chaque machine.
* **Stable :** Basé sur les versions LTS (Long Term Support) du noyau.

Idéal pour les étudiants ou les petits budgets cherchant une machine rapide et fiable pour travailler.

---

## 💻 Machines Supportées

| Modèle | Statut | Noyau (Kernel) | Particularités |
| :--- | :--- | :--- | :--- |
| **Dell Inspiron 1520** | ✅ Disponible | 6.1.x (LTS) | Core 2 Duo, Optimisé pour bureautique/web |
| **Dell Latitude 7480** | 🚧 En cours | 6.1.x (LTS) | Ultrabook pro, Optimisé autonomie |

*D'autres modèles seront ajoutés au fur et à mesure des rénovations.*

---

## 🛠 Comment utiliser ces configurations ?

Si vous avez acquis un de ces PC ou si vous possédez le même modèle, voici comment compiler votre noyau avec ma configuration :

1.  **Installez les pré-requis sur Debian :**
    ```bash
    sudo apt install build-essential libncurses-dev bison flex libssl-dev libelf-dev
    ```

2.  **Téléchargez les sources du noyau (sur kernel.org) et extrayez-les.**

3.  **Récupérez mon fichier `.config` :**
    Allez dans le dossier correspondant à votre machine sur ce dépôt, téléchargez le fichier `.bak` et renommez-le en `.config` à la racine de vos sources.

4.  **Lancez la compilation :**
    ```bash
    make oldconfig
    make -j$(nproc) bindeb-pkg
    ```

5.  **Installez les .deb générés :**
    ```bash
    sudo dpkg -i ../linux-image*.deb ../linux-headers*.deb
    ```

---

## ⚠️ Avertissement
Ces configurations sont fournies "telles quelles". Elles sont taillées pour le matériel spécifique listé ci-dessus. L'utilisation sur d'autres machines peut entraîner des instabilités ou un système non-bootable.

**Auteur :** JoelPince-Hash
*Passionné par la rénovation informatique et l'Open Source.*
