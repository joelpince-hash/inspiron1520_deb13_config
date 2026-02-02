Linux Kernel pour Dell Inspiron 1520
Ce dépôt contient la configuration optimisée sur mesure pour un Dell Inspiron 1520 (Core 2 Duo, NVidia GeForce 8600M GT)

Philosophie
Ce kernel est optimisé pour :
1) être léger avec la suppression de tous les pilotes inutiles pour la machine
2) être optimisé pour le processeur Intel(R) Core(TM)2 Duo CPU     T5250  @ 1.50GHz
3) être utilisé sous Debian 13 testing avec DWM ou XFCE

Spécifications
Dernière version : 6.18.8
Architecture : x86_64
Optimisations : ZRAM, NTFS, NOUVEAU

Utilisation : compilation manuelle
Placez le fichier de config dans votre dossier de compilation et renommez-le en .config
Chargez la configuration avec make oldconfig
Modifiez votre configuration avec make menuconfig si nécessaire
Lancez la configuration avec 3.	make -j2 bindeb-pkg
Installez et redémarrez !

Nota : le config.h concerne dwm. Si vous envisagez un autre bureau, il ne vous servira à rien. Je conseille XFCE pour X11.
