# Get Next Line

## 📋 Description

`get_next_line` est un projet de l'école 42 qui consiste à créer une fonction permettant de lire une ligne depuis un file descriptor, une ligne à la fois.

## 🎯 Objectif

Implémenter une fonction `get_next_line()` qui :
- Lit une ligne complète depuis un file descriptor
- Retourne la ligne lue (incluant le `\n` sauf si c'est la fin du fichier)
- Peut être appelée plusieurs fois pour lire un fichier ligne par ligne
- Gère correctement différents `BUFFER_SIZE`
- Fonctionne avec les fichiers et l'entrée standard

## 🔧 Compilation

### Compilation de base
```bash
make
```
Compile la bibliothèque statique `get_next_line.a`

### Avec un BUFFER_SIZE personnalisé
```bash
make BUFFER_SIZE=1
make BUFFER_SIZE=42
make BUFFER_SIZE=9999
```

### Compilation avec flags standards
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

## 📖 Utilisation

### Prototype
```c
char *get_next_line(int fd);
```

### Paramètres
- `fd` : Le file descriptor à lire

### Valeur de retour
- **Succès** : Pointeur vers la ligne lue (incluant le `\n`)
- **Fin de fichier** : `NULL`
- **Erreur** : `NULL`

### Exemple d'utilisation
```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("fichier.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## 🧪 Tests

### Compiler le testeur
```bash
make test
```

### Exécuter les tests
```bash
# Tests automatiques
./test_gnl

# Tester avec un fichier spécifique
./test_gnl fichier.txt
```

### Tests inclus
- ✅ Fichier vide
- ✅ Fichier avec une seule ligne
- ✅ Fichier avec plusieurs lignes
- ✅ Fichier sans `\n` à la fin
- ✅ File descriptor invalide
- ✅ Ligne très longue
- ✅ Différents `BUFFER_SIZE` (1, 42, etc.)

## 🧹 Nettoyage

### Nettoyer les fichiers objets
```bash
make clean
```

### Nettoyer tout (bibliothèque + exécutable de test)
```bash
make fclean
```

### Nettoyer les fichiers de test
```bash
make test_clean
```

### Recompiler depuis le début
```bash
make re
```