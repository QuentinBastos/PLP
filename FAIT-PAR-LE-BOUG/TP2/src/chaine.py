def longueur(chaine):
    """
    Retourne la longueur de la chaine de caractères passée en paramètre
    """
    return len(chaine)


def copie(source):
    """
    Retourne une copie de la chaine de caractères passée en paramètre
    """
    return source[:]


def concatenation(chaine1, chaine2):
    """
    Retourne la concaténation des deux chaines de caractères passées en paramètre
    """
    return chaine1 + chaine2


def main() -> None:
    chaine1: str = str(input("Entrez une chaine de caractères: "))
    chaine2: str = str(input("Entrez une autre chaine de caractères: "))

    print(f"La longueur de la chaine {chaine1} est {longueur(chaine1)}")
    print(f"La copie de la chaine {chaine1} est {copie(chaine1)}")
    print(f"La concaténation des chaines {chaine1} et {chaine2} est {concatenation(chaine1, chaine2)}")


if __name__ == "__main__":
    main()
