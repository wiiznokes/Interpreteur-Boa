# Projet interpreteur
 


## Strucutre

Il nous faut faire un automate pour reconnaitre le lexeme de notre language


Dans l'analyse syntaxique, on doit construire un arbre

## Process

- start analyse syntaxique
- découvrir le premier lexeme -> Donc return si une erreur lexicale est découverte
dans le premier lexeme
- créer une node en fonction du lexeme trouvé, découvrir d'autre si besoin
- construire l'arbre tant que tous les lexemes non pas été découvert



On doit donc penser a la strucure finale de l'arbre, en pensant a la facon la plus simple pour calculer 
les instuctions plus-tard


## Notes

au final, je me dis qu'on devrait peut-être reprendre le code de la calculette pour calculter des trucs compliqué du genre

entier = 55+94*9494+94+(0/10)-6;

faudra juste rejouter quelque grammaire dans l'abre pour supporter
les affectations, condition, ect

et aussi rajouter des listes de variables