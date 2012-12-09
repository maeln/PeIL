Format PAK:
3 premier octet : Signature 'PAK'
octets 4-8 : int 32 bit, nombre de fichier dans le pak
octet 8-(8+n*4) ou n = nb de fichier : adresse dans le PAK de chaque fichier
octet (8+n*4)-EOF : contenu des fichier
