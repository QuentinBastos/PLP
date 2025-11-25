class Etudiant:
    """
    Classe représentant un.e étudiant.e
    """

    def __init__(
            self,
            nom: str,
            prenom: str,
            adresse: str,
            notes: list
    ):
        self.nom = nom
        self.prenom = prenom
        self.adresse = adresse
        self.notes = notes

    def __str__(self):
        return f"Nom : {self.nom} \nPrénom : {self.prenom} \nAdresse : {self.adresse} \nNotes : {', '.join(map(str, self.notes))}"


if __name__ == "__main__":
    # Créer une liste d'étudiants
    etudiants: list[Etudiant] = []

    # Demander à l'utilisateur le nombre d'étudiants à ajouter
    nb_etudiants = int(input("Combien d'étudiant.e.s voulez-vous ajouter ? "))

    # Ajouter chaque étudiant.e à la liste
    for i in range(nb_etudiants):
        print(f"========== Etudiant.e n°{i + 1} ==========")

        # Demander les informations de l'étudiant.e
        nom = input("Nom : ")
        prenom = input("Prénom : ")
        adresse = input("Adresse : ")

        # Demander le nombre de notes à ajouter
        nb_notes = int(input("Combien de notes voulez-vous ajouter ? "))
        notes = []

        # Ajouter chaque note à la liste
        for j in range(nb_notes):
            note = float(input(f"Note n°{j + 1} : "))
            notes.append(note)

        # Ajouter l'étudiant.e à la liste
        etudiants.append(Etudiant(nom, prenom, adresse, notes))

    # Afficher la liste des étudiants
    print("\n\nListe des étudiants :\n")
    for etudiant in etudiants:
        print("==========")
        print(etudiant)
        print("==========\n")
