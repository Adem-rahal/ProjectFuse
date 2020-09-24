ADEM RAHAL Compte rendu

Utilisation:

Créez un dossier du nom de mountpoint dans le repertoire ou vous voulez travaillez.
Lancer ensuite le code avec le make file "make build" cela devrait aussi monter le mountpoint 
et freeze la console vous pouvez retirer le -f si voulu.
vous aurez ensuite 5 files créez dans le mountpoint qui se nomme mountpoint d'ailleurs.
et vous pouvez tester tout le tp sur les files en fonction de leurs nom hello correspond
au premier point qui va vous afficher "Hello" quoi qu'il arrive, ensuite les fichier shutdown, 
suspend et update font respectivement ce qui est demander dans les 2 dernières questions en fonction de
leurs noms et enfin un fichier test pour pour les autres questions tester d'écire et que ce qu'on écrit 
soit sauvegardé dedant et de lire (en utilisan les fonctions cat pour lire et echo ".." > test pour écrire).
ensuite make clean pour unmount le mountpoint si nécessaire.

Remarque: Ne pas faire attention au warning et problèmes dans la console VSD ça fonctionne très bien je pense que l'ordi a juste
un problème avec moi. J'ai aussi une erreur sur les fillers la console me dit too many arguments
sauf que quand j'enlève un arguments cela ne compile plus. 