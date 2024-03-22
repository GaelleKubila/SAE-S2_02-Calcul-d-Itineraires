
#include <iostream>
#include <cstring>
using namespace std;

/// <summary>
/// Permet de manipuler un couple de noms de stations pour l'algorithme de Dijkstra.
/// </summary>
class trajet

{

protected:

    char* stationdepart;
    char* stationarrivee;

public:

    trajet(string depart, string arrivee)
    {
        int nbchar_dep = depart.length();
        int nbchar_arr = arrivee.length();

        stationdepart = new char[nbchar_dep + 1];

        for (int i = 0; i < nbchar_dep; i++)
        {
            stationdepart[i] = depart[i];
        }

        stationdepart[nbchar_dep] = '\0';

        stationarrivee = new char[nbchar_arr + 1];

        for (int i = 0; i < nbchar_arr; i++)
        {
            stationarrivee[i] = arrivee[i];
        }

        stationarrivee[nbchar_arr] = '\0';

    }

    trajet(const trajet& t)
    {
        stationdepart = t.stationdepart;
        stationarrivee = t.stationarrivee;

    }

    trajet& operator= (const trajet& t)
    {
        if (this != &t)
        {
            if (stationdepart != NULL)
            {
                stationdepart = t.stationdepart;
            }
            else
            {
                stationdepart = NULL;
            }

            if (stationarrivee != NULL)
            {
                stationarrivee = t.stationarrivee;
            }
            else
            {
                stationarrivee = NULL;
            }


        }

        return *this;



    }

    void affiche()

    {
        cout << "Le trajet selectionne est le suivant : " << endl;
        cout << "Depart : " << stationdepart << endl;
        cout << "Arrivee : " << stationarrivee << endl;

    }

    char* depart_recup()
    {
        return stationdepart;
    }

    char* arrivee_recup()
    {
        return stationarrivee;
    }


};


/// <summary>
/// Permet de manipuler un sommet de graphe à nommer.
/// </summary>
class sommet
{

protected:

    char* nom;

public:

    // constructeur vide
    sommet()

    {
        nom = NULL;
    }

    //constructeur avec nom prédéfini
    sommet(string chaine)

    {

        int nbchar = chaine.length();

        nom = new char[nbchar + 1];

        for (int i = 0; i < nbchar; i++)
        {
            nom[i] = chaine[i];
        }

        nom[nbchar] = '\0';


    }

    ~sommet()

    {
        delete nom;
    }

    sommet(const sommet& s)

    {

        if (s.nom != NULL)
        {

            int nbchar = strlen(s.nom);

            nom = new char[nbchar + 1];

            for (int i = 0; i < nbchar; i++)
            {
                nom[i] = s.nom[i];
            }

            nom[nbchar] = '\0';
        }
        else
        {
            nom = NULL;
        }

    }


    sommet& operator=(const sommet& s)

    {
        if (this != &s)

        {

            int nbchar;

            if (s.nom != NULL)
            {

                nbchar = strlen(s.nom);
                nom = new char[nbchar + 1];


                for (int i = 0; i < nbchar; i++)

                {
                    nom[i] = s.nom[i];
                }

                nom[nbchar] = '\0';


            }

        }

        return *this;

    }

    const bool& operator== (const sommet& s)
    {
        if ((string)this->nom == (string)s.nom)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    const bool& operator!= (const sommet& s)
    {
        if ((string)this->nom != (string)s.nom)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    bool egalite_securisee(sommet s) // la surcharge normale de l'égalité peut provoquer des segfaults...
    {
        if ((string)this->nom == (string)s.nom)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    void affiche()

    {

        if (nom != NULL)
        {

            cout << nom;

        }
        else
        {

            cout << "NULL";
        }

    }

    char* collectnom()

    {
        return nom;

    }


};

/// <summary>
/// Permet de manipuler une liaison (non-orientée) entre deux sommets d'un graphe, valuées par un poids.
/// </summary>
class arc
{

protected:

    sommet somdepart;
    sommet somarriv;
    int poids;

public:

    arc()

    {
        poids = 0;

    }

    arc(sommet s1, sommet s2, int k)

    {

        somdepart = s1;
        somarriv = s2;
        poids = k;

    }


    ~arc()
    {

    }


    arc(const arc& a)

    {
        somdepart = a.somdepart;
        somarriv = a.somarriv;
        poids = a.poids;

    }


    arc& operator= (const arc& a)

    {

        if (this != &a)

        {

            somdepart = a.somdepart;
            somarriv = a.somarriv;
            poids = a.poids;


        }

        return *this;

    }

    void affiche()

    {

        cout << "L'arc relie ";
        somdepart.affiche();
        cout << " a ";
        somarriv.affiche();
        cout << endl;
        cout << "Distance entre les deux sommets : " << poids << endl;

    }

    /// <summary>
    /// Retourne le nom d'un sommet extrémité en fonction du type demandé passé en paramètre.
    /// </summary>
    /// <param name="type">string : chaîne de caracteres ("depart" ou "arrivee").</param>
    /// <returns>Le nom de l'extrémité demandée.</returns>
    string recup_sommetnom(string type)

    {
        string nomsommet;

        if (type == "depart")
        {
            nomsommet = somdepart.collectnom();
        }

        if (type == "arrivee")
        {
            nomsommet = somarriv.collectnom();
        }

        return nomsommet;

    }

    /// <summary>
    /// Retourne un sommet extrémité en fonction du nom de sommet passé en paramètre.
    /// </summary>
    /// <param name="type">const char* : chaîne de caracteres.</param>
    /// <returns>L'objet sommet demandé (s'il existe), sinon un sommet vide.</returns>
    sommet recup_sommetobj(const char* nomsommet)

    {

        sommet somrecup;
        char* res_som_d = somdepart.collectnom();
        char* res_som_a = somarriv.collectnom();
        bool depart_egal = true;
        bool arrivee_egal = true;
        int i;

        i = 0;

        while (res_som_d[i] != '\0' && nomsommet[i] != '\0')

        {
            if (res_som_d[i] != nomsommet[i])
            {
                depart_egal = false;
            }

            i++;
        }

        i = 0;

        while (res_som_a[i] != '\0' && nomsommet[i] != '\0')

        {
            if (res_som_a[i] != nomsommet[i])
            {
                arrivee_egal = false;
            }

            i++;
        }

        if (depart_egal)
        {
            somrecup = somdepart;
        }

        if (arrivee_egal)
        {
            somrecup = somarriv;
        }

        return somrecup;

    }

    /// <summary>
    /// Vérifie si cet arc a comme l'une de ses extrémités le sommet passé en paramètre.
    /// </summary>
    /// <param name="type">const char* : chaîne de caracteres.</param>
    /// <returns>true ou false.</returns>
    bool sommet_existe(const char* nomsommet)

    {
        char* res_som_d = somdepart.collectnom();
        char* res_som_a = somarriv.collectnom();
        bool depart_egal = true;
        bool arrivee_egal = true;
        int i;

        i = 0;

        if(res_som_a==NULL || res_som_d==NULL)
        {
            return false;
        }
        else
        {



        while (res_som_d[i] != '\0' && nomsommet[i] != '\0')

        {
            if (res_som_d[i] != nomsommet[i])
            {
                depart_egal = false;
            }

            i++;
        }

        i = 0;

        while (res_som_a[i] != '\0' && nomsommet[i] != '\0')

        {
            if (res_som_a[i] != nomsommet[i])
            {
                arrivee_egal = false;
            }

            i++;
        }

        if (depart_egal || arrivee_egal)
        {
            return true;
        }
        else
        {
            return false;
        }
        }
    }

    /// <summary>
    /// Retourne le sommet à l'opposé du nom de sommet passé en paramètre.
    /// </summary>
    /// <param name="type">const char* : chaîne de caracteres.</param>
    /// <returns>L'objet sommet demandé (s'il existe), sinon un sommet vide.</returns>
    sommet recup_inversesommetobj(const char* nomsommet)

    {

        sommet somrecup;
        char* res_som_d = somdepart.collectnom();
        char* res_som_a = somarriv.collectnom();
        bool depart_egal = true;
        bool arrivee_egal = true;
        int i;

        i = 0;

        if(res_som_a!=NULL || res_som_d!=NULL)
        {

        while (res_som_d[i] != '\0' && nomsommet[i] != '\0')

        {
            if (res_som_d[i] != nomsommet[i])
            {
                depart_egal = false;
            }

            i++;
        }

        i = 0;

        while (res_som_a[i] != '\0' && nomsommet[i] != '\0')

        {
            if (res_som_a[i] != nomsommet[i])
            {
                arrivee_egal = false;
            }

            i++;
        }

        if (depart_egal)
        {
            somrecup = somarriv;
        }

        if (arrivee_egal)
        {
            somrecup = somdepart;
        }
        }

        return somrecup;

    }

    /// <summary>
    /// Vérifie si deux arcs sont reliés à un même sommet et le retourne s'il existe.
    /// </summary>
    /// <param name="type">arc</param>
    /// <returns>L'objet sommet demandé (s'il existe), sinon un sommet vide.</returns>
    sommet recup_sommetencommun(arc bis)
    {
        sommet som_final;
        sommet recup_d = bis.recup_sommetobj(somdepart.collectnom());
        sommet recup_a = bis.recup_sommetobj(somarriv.collectnom());

        //regarde si bis contient somdepart

        if (recup_d.collectnom() != NULL)
        {
            som_final = recup_d;
        }

        //regarde si bis contient somarriv

        if (recup_a.collectnom() != NULL)
        {
            som_final = recup_a;;
        }

        return som_final;
    }


    int recup_poids()

    {
        return poids;
    }

};


/// <summary>
/// Permet de manipuler simplement un graphe à l'aide de sommets et d'arcs.
/// Contient différentes méthodes pour mieux visualiser et utiliser les connexions.
/// </summary>
class graphe

{
protected:

    sommet* So;
    arc* Ar;
    int nbsommets;
    int nbarcs;

public:

    graphe()

    {

        So = NULL;
        Ar = NULL;
        nbsommets = 0;
        nbarcs = 0;

    }

    ~graphe()

    {
        delete[] So;
        delete[] Ar;

    }

    //constructeur de recopie

    graphe(const graphe& g)
    {

        So = new sommet[g.nbsommets];
        Ar = new arc[g.nbarcs];

        for (int i = 0; i < nbsommets; i++)

        {
            So[i] = g.So[i];
        }

        for (int i = 0; i < nbarcs; i++)

        {
            Ar[i] = g.Ar[i];
        }

        nbsommets = g.nbsommets;
        nbarcs = g.nbarcs;

    }

    //surcharge de l'égalité

    graphe& operator= (const graphe& g)
    {

        if (this != &g)

        {
            delete[] So;
            delete[] Ar;

            So = new sommet[g.nbsommets];
            Ar = new arc[g.nbarcs];

            for (int i = 0; i < nbsommets; i++)

            {
                So[i] = g.So[i];
            }

            for (int i = 0; i < nbarcs; i++)

            {
                Ar[i] = g.Ar[i];
            }

            nbsommets = g.nbsommets;
            nbarcs = g.nbarcs;


        }

        return *this;

    }

    // Extraction des valeurs de base

    int extraction_nbsommets()
    {
        return nbsommets;
    }

    int extraction_nbarcs()
    {
        return nbarcs;
    }



    // Manipulation des sommets

    void ajoutsommet(sommet s)

    {

        sommet* temp;

        temp = new sommet[nbsommets];

        for (int i = 0; i < nbsommets; i++)

        {
            temp[i] = So[i];

        }

        delete[] So;

        So = new sommet[nbsommets + 1];

        for (int i = 0; i < nbsommets; i++)

        {
            So[i] = temp[i];

        }

        So[nbsommets] = s;

        nbsommets++;

    }

    void affichesommet()

    {

        cout << "Ce graphe possede " << nbsommets << " sommet(s)." << endl;

        if (nbsommets > 0)

        {

            for (int i = 0; i < nbsommets; i++)

            {

                cout << "Sommet numero" << i + 1 << " : ";
                So[i].affiche();
                cout << endl;

            }

        }

    }

    void affichesommet(int k)
    {

        if (nbsommets > 0)
        {

            cout << "Sommet numero" << k << " : ";
            So[k = 1].affiche();
            cout << endl;

        }
        else
        {
            cout << "Ce graphe n'a aucun sommet" << endl;
        }

    }

    //manipulation des arcs

    void ajoutarc(arc a)
    {
        bool sommetpresent_dep = false;
        bool sommetpresent_arr = false;

        for (int i = 0; i < nbsommets; i++)
        {

            if (a.recup_sommetnom("depart") == So[i].collectnom())

            {
                sommetpresent_dep = true;

            }

            if (a.recup_sommetnom("arrivee") == So[i].collectnom())

            {
                sommetpresent_arr = true;

            }

        }

        if (sommetpresent_dep && sommetpresent_arr)

        {

            arc* temp;

            temp = new arc[nbarcs];

            for (int i = 0; i < nbarcs; i++)

            {
                temp[i] = Ar[i];

            }

            delete[] Ar;

            Ar = new arc[nbarcs + 1];

            for (int i = 0; i < nbarcs; i++)

            {
                Ar[i] = temp[i];

            }

            Ar[nbarcs] = a;

            nbarcs++;


        }

        else

        {

            cout << "L'arc ne peut pas etre ajoute au graphe" << endl;
            cout << "Verifiez que les deux sommets soient tous les deux dans le graphe..." << endl;

        }
    }


    void affichearc()
    {

        cout << "Ce graphe possede " << nbarcs << " arc(s)." << endl;

        if (nbarcs > 0)

        {

            for (int i = 0; i < nbarcs; i++)

            {

                cout << "Arc numero" << i + 1 << " : ";
                Ar[i].affiche();
                cout << endl;

            }

        }

    }

    void affichearc(int k)
    {

        if (nbarcs > 0)

        {

            cout << "Arc numero" << k << " : ";
            Ar[k - 1].affiche();
            cout << endl;

        }

        else

        {
            cout << "Ce graphe n'a aucun arc" << endl;
        }

    }

    //manipulation des sommets

    /// <summary>
    /// Affiche tous les sommets du graphe demandé.
    /// </summary>
    void listepoints_affiche()
    {
        for (int i = 0; i < nbsommets; i++)
        {
            So[i].affiche();
            cout << endl;
        }
    }

    //manipulation des connexions


    /// <summary>
    /// Affiche tous les arcs du graphe partant d'un sommet demandé.
    /// </summary>
    /// <param name="pointdepart">: le nom du sommet dont on souhaite donner la liste.</param>
    void listeconnexions_affiche(const string pointdepart)
    {

        for (int i = 0; i < nbarcs; i++)
        {
            if (Ar[i].recup_sommetnom("depart") == pointdepart)

            {
                Ar[i].affiche();

            }

            if (Ar[i].recup_sommetnom("arrivee") == pointdepart)

            {
                Ar[i].affiche();

            }


        }

    }


    /// <summary>
    /// Affiche tous les arcs du graphe partant d'un sommet demandé.
    /// </summary>
    /// <param name="pointdepart">: le sommet dont on souhaite donner la liste.</param>
    void listeconnexions_affiche(sommet pointdepart)
    {

        for (int i = 0; i < nbarcs; i++)
        {

            if (Ar[i].recup_sommetnom("depart") == pointdepart.collectnom())

            {
                Ar[i].affiche();

            }

            if (Ar[i].recup_sommetnom("arrivee") == pointdepart.collectnom())

            {
                Ar[i].affiche();

            }


        }

    }



    /// <summary>
    /// Retourne les nombre d'arcs du graphe partant d'un sommet demandé.
    /// </summary>
    /// <param name="pointdepart">: le nom du sommet dont on souhaite utiliser la liste.</param>
    int listeconnexions_copie(sommet pointdepart)

    {

        int nombreactuel_arcs = 0;

        for (int i = 0; i < nbarcs; i++) {

            if (Ar[i].recup_sommetnom("depart") == pointdepart.collectnom())

            {
                nombreactuel_arcs++;

            }

            if (Ar[i].recup_sommetnom("arrivee") == pointdepart.collectnom())

            {
                nombreactuel_arcs++;

            }

        }

        return nombreactuel_arcs;

    }

    /// <summary>
    /// Compte et cnstitue la liste de tous les arcs du graphe partant d'un sommet demandé.
    /// </summary>
    /// <param name="pointdepart">: le nom du sommet dont on souhaite donner la liste.</param>
    /// <param name="liste">: le tableau d'arc vers lequel on souhaite extraire la liste.</param>
    int listeconnexions_copie(string pointdepart, arc liste[])

    {

        int nombreactuel_arcs = 0;

        for (int i = 0; i < nbarcs; i++) {

            if (Ar[i].recup_sommetnom("depart") == pointdepart)

            {
                arc temp(Ar[i]);

                liste[nombreactuel_arcs] = temp;
                nombreactuel_arcs++;

            }

            if (Ar[i].recup_sommetnom("arrivee") == pointdepart)

            {

                arc temp(Ar[i]);

                liste[nombreactuel_arcs] = temp;
                nombreactuel_arcs++;

            }

        }

        return nombreactuel_arcs;

    }

    /// <summary>
    /// Compte et constitue la liste de tous les arcs du graphe partant d'un sommet demandé.
    /// </summary>
    /// <param name="pointdepart">: le sommet dont on souhaite donner la liste.</param>
    /// <param name="liste">: le tableau d'arc vers lequel on souhaite extraire la liste.</param>
    int listeconnexions_copie(sommet pointdepart, arc liste[])

    {

        int nombreactuel_arcs = 0;

        for (int i = 0; i < nbarcs; i++) {

            if (Ar[i].recup_sommetnom("depart") == pointdepart.collectnom())

            {
                arc temp(Ar[i]);

                liste[nombreactuel_arcs] = temp;
                nombreactuel_arcs++;

            }

            if (Ar[i].recup_sommetnom("arrivee") == pointdepart.collectnom())

            {

                arc temp(Ar[i]);

                liste[nombreactuel_arcs] = temp;
                nombreactuel_arcs++;

            }

        }

        return nombreactuel_arcs;

    }


    /// <summary>
    /// Calcule le chemin le plus court pour aller d'un sommet à un autre et donne les sommets par lequels passer + le poids minimal.
    /// </summary>
    /// <param name="T">: Le couple départ/arrivée utilisé pour calculer l'itinéraire.</param>
    void dijkstra(trajet T)
    {

        //initialisation

        int i;
        int nbconnexions;
        arc connexions_nbarcs[256]; // l'ensemble de tous les arcs
                                    // note : on a décidé de le faire en statique pour des raisons de simplicité de code

        int* ecart = new int[nbsommets];
        sommet* precedent = new sommet[nbsommets]; // la liste de tous les sommets "précédents" à une étape T

        sommet* deja_visite = new sommet[nbsommets]; // la liste de tous les sommets déjà visités à une étape T


        for (i = 1; i < nbsommets; i++)
        {
            ecart[i] = 9999999; // en pseudo-code, correspond à +infini
        }

        ecart[0] = 0; // le sommet initial est distant de 0 de lui-même...

        int cptecart = 1; //on compte les étapes à partir de 1 pour des raisons de calcul

        /* On récupère T.stationdebut : ça permettra ainsi de débuter l'algorithme */

        sommet u(T.depart_recup());

        sommet a(T.arrivee_recup());

        while (!(u.egalite_securisee(a))) // tant que le sommet sélectionné est différent de celui de fin :
        {

            nbconnexions = listeconnexions_copie(u, connexions_nbarcs);

            i = 0;

            while (i < nbconnexions)
            {

                int distance_alternative;


                if (deja_visite[i].collectnom() != NULL)
                {
                    if ((connexions_nbarcs[i].sommet_existe(deja_visite[i].collectnom()))) //on saute un arc s'il est déjà visité
                    {
                        i++;
                    }

                    if (connexions_nbarcs[i].sommet_existe(T.arrivee_recup()))
                    {
                        break;

                        //pas très élégant, mais c'est pour dire qu'il faut s'arrêter dès qu'on a trouvé le sommet destination.
                    }
                }


                distance_alternative = ecart[cptecart - 1] + connexions_nbarcs[i].recup_poids(); //addition ecart actuel et poids supplementaire de la liste

                if (distance_alternative < ecart[cptecart])

                {
                    ecart[cptecart] = distance_alternative;
                    precedent[cptecart - 1] = u;

                }



                i++;
            }

            cptecart++;

            deja_visite[cptecart - 1] = u;

            //On récupére le u de distance la plus petite


            u = connexions_nbarcs[i - 1].recup_inversesommetobj(u.collectnom());

            if (i >= nbconnexions)
            {
                i = nbconnexions - 1;
            }
            if (connexions_nbarcs[i].sommet_existe(T.arrivee_recup())) //si le sommet trouvé est celui qui achève le chemin
            {
                sommet fin(T.arrivee_recup());
                u = fin;
                precedent[cptecart - 1] = u;

            }

        }

        T.affiche();

        cout << "Nous proposons ce chemin :" << endl;

        for (int j = 0; j < cptecart; j++)
        {
            cout << "Station :";
            precedent[j].affiche();
            cout << endl;
            cout << "Temps mis :";
            cout << ecart[j];
            cout << " minutes" << endl;
            cout << endl;

        }

        cout << "temps total de trajet : " << ecart[cptecart - 1] << " minutes" << endl;
    }



};



int main()
{


    sommet s1("Gare de l'Ouest");

    sommet s3("Beekant");


    arc a1(s1, s3, 3);


    graphe G;

    G.ajoutsommet(s3);
    G.ajoutsommet(s1);

    G.ajoutarc(a1);

    sommet s4("Osseghem");

    sommet s5("Simonis Leopold II");

    sommet s6("Etangs Noirs");

    sommet s7("Jacques Brel");

    sommet s8("Delacroix");

    G.ajoutsommet(s4);
    G.ajoutsommet(s5);
    G.ajoutsommet(s6);
    G.ajoutsommet(s7);
    G.ajoutsommet(s8);

    arc a2(s3, s4, 1);
    arc a3(s4, s5, 2);
    arc a4(s3, s6, 2);
    arc a5(s1, s7, 1);
    arc a6(s8, s1, 2);


    G.ajoutarc(a2);
    G.ajoutarc(a3);
    G.ajoutarc(a4);
    G.ajoutarc(a5);
    G.ajoutarc(a6);

    G.affichesommet();
    G.affichearc();

    trajet T("Etangs Noirs", "Osseghem");

    G.dijkstra(T); //ATTENTION : sujet à crash


    return 0;
}
