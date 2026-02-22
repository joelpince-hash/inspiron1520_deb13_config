# 🐧 Configurations du noyau Linux Optimisées (Refurbished Laptops)

Ce dépôt héberge les fichiers de configuration (`.config`) du noyau Linux (Kernel), optimisés spécifiquement pour des ordinateurs portables professionnels d'ancienne génération reconditionnés. L'objectif est d'obtenir un kernel léger, tout en assurant la compatibilité avec le matériel usuel (clavier et souris externes, etc).'

## 🎯 L'Objectif
L'idée est de prolonger la durée de vie de matériel informatique de qualité (Dell Latitude, Inspiron, ThinkPad...) qui ne supporte plus Windows 11.
Ces configurations sont destinées à **Debian Stable** mais sont utilisable sur toutes les distributions debian-compatibles. Elles visent à produire un système :
* **Ultra-léger :** Suppression des pilotes inutiles et du "bloatware" du noyau générique.
* **Performant :** Optimisation spécifique au processeur (CPU) et au matériel de chaque machine.
* **Stable :** Basé sur la dernière version stable du noyau.

Idéal pour les étudiants ou les petits budgets cherchant une machine rapide et fiable pour travailler, ces vieux PC étant obsolètes pour Windows mais encore largement utilisables avec Linux !

---

## 💻 Machines Supportées

| Modèle | Statut | Noyau (Kernel) | Particularités |
| :--- | :--- | :--- | :--- |
| **Dell Inspiron 1520** | ✅ Disponible | 6.19.3 | Core 2 Duo, Optimisé pour bureautique/web |
| **Dell Latitude 7480** | ✅ Disponible | 6.19.0 | Ultrabook pro, Optimisé autonomie |
| **HP Stream 13** | ✅ Disponible | 6.19.0 | Intel Celeron N3050, Optimisé |

*D'autres modèles seront ajoutés au fur et à mesure des rénovations.*

---

## 🛠 Comment utiliser ces configurations ?

Si vous avez acquis un de ces PC ou si vous possédez le même modèle, voici comment compiler votre noyau avec ma configuration :

1.  **Installez les pré-requis sur Debian :**
    ```bash
    sudo apt install build-essential ccache zstd bc git rsync dpkg-dev debhelper dwarves libdw-dev libelf-dev libssl-dev libncurses-dev flex bison btop lm-sensors htop btrfs-progs
    ```
Je vous invite à configurer ccache à 20Go max.
    ```bash
    ccache -M 20G
    ```
N'oubliez pas d'ajouter ccache à votre PATH :
    ```bash
    export PATH=\"/usr/lib/ccache:\$PATH\"
    ```

2.  **Téléchargez les sources du noyau (sur kernel.org) et extrayez-les.**

3.  **Récupérez mon fichier `.config` :**
    Allez dans le dossier correspondant à votre machine sur ce dépôt, téléchargez le fichier `.bak` et renommez-le en `.config` à la racine de vos sources.

4.  **Lancez la compilation :**
    ```bash
    make oldconfig
    time make CC="ccache gcc" KCFLAGS="-march=native -O3" -j2 bindeb-pkg
    ```

5.  **Installez les .deb générés :**
    ```bash
    sudo dpkg -i ../linux-image*.deb ../linux-headers*.deb
    ```

---

Vous pouvez aussi télécharger les noyaux déjà installables fournis dans les packages. Mais une compilation du dernier noyau disponible est une meilleure idée.
## ⚠️ Avertissement
Ces configurations sont fournies "telles quelles". Elles sont taillées pour le matériel spécifique listé ci-dessus. L'utilisation sur d'autres machines peut entraîner des instabilités ou un système non-bootable.

**Auteur :** JoelPince-Hash
*Passionné par la rénovation informatique et l'Open Source.*
