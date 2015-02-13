////////////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990Test.cpp
/// @author Samuel Millette
/// @date 2015-02-12
/// @version 1.0
///
/// @ingroup Test
////////////////////////////////////////////////////////////////////////////////////

#include "ArbreRenduINF2990Test.h"
#include "../Visiteurs/VisiteurAbstrait.h"
#include "../Visiteurs/VisiteurRotation.h"
#include "../Visiteurs/VisiteurDeselectionnerTout.h"
#include "NoeudAbstrait.h"
#include "NoeudComposite.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(ArbreRenduINF2990Test);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::setUp()
{
	// Nous pourrions initialiser l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune initialisation n'est requise.

	arbre = std::make_unique<ArbreRenduINF2990>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::tearDown()
{
	// Nous pourrions lib�rer l'objet, mais puisqu'il s'agit d'un singleton,
	// aucune lib�ration n'est requise.
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduINF2990Test::______()
///
/// Cas de test: ...
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990Test::testArbreDefaut()
{
	// On initialise l'arbre avec le fichier XML par d�faut
	arbre->initialiser();

	// On v�rifie que les �l�ments par d�faut sont dans l'arbre.
	CPPUNIT_ASSERT(arbre->estDefaut() == true);
	
	// L'arbre devrait avoir des enfants
	CPPUNIT_ASSERT(arbre->getSizeEnfants() > 0);

	// On v�rifie que la table contient une table de mani�re alternative
	bool trouve = false;

	for (int i = 0; i < arbre->getSizeEnfants(); i++)
	{
		if (arbre->getEnfant(i)->obtenirType() == ArbreRenduINF2990::NOM_TABLE)
			trouve = true;

	}
	CPPUNIT_ASSERT(trouve == true);

	// Les propri�t�s de jeu ne sont pas n�gatives
	for (int i = 0; i < 5; i++)
		CPPUNIT_ASSERT(arbre->obtenirProprietes()[i] > 0);

	// On vide l'arbre
	arbre->vider();
}

void ArbreRenduINF2990Test::testXmlInexistant()
{
	// On ouvre un fichier inexistant
	bool test = arbre->initialiserXML("Zones_de_jeu/inexistant.xml");
	CPPUNIT_ASSERT(!test);

	// On ouvre un fichier qui existe
	bool test2 = arbre->initialiserXML("Zones_de_jeu/default.xml");
	CPPUNIT_ASSERT(test2);

	// On vide l'arbre
	arbre->vider();
}

void ArbreRenduINF2990Test::testPortails()
{
	// On initialise une zone de jeu avec des portails
	bool test = arbre->initialiserXML("Zones_de_jeu/testportails.xml");
	CPPUNIT_ASSERT(test);

	// On cherche un portail.
	NoeudAbstrait* portail1 = arbre->chercher(ArbreRenduINF2990::NOM_PORTAIL);

	// On obtient le noeud li� au portail obtenu.
	NoeudAbstrait* portail2 = portail1->getTwin();

	// L'objet li� est un autre portail.
	CPPUNIT_ASSERT(portail2->obtenirType() == ArbreRenduINF2990::NOM_PORTAIL);

	// On vide l'arbre.
	arbre->vider();
}

void ArbreRenduINF2990Test::creerNoeudParUsine()
{
	// On cr�e un noeud de type non reconnu par les usines.
	NoeudAbstrait* noeudVide = arbre->creerNoeud("NOM_CIBLE");

	// On cr�e un nom de type reconnu par une usine.
	NoeudAbstrait* noeudCible = arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE);
	
	// Le noeud non reconnu est un nulptr
	CPPUNIT_ASSERT(noeudVide == NULL);

	// Le noeud reconnu par l'usine est du bon type.
	CPPUNIT_ASSERT(noeudCible->obtenirType() == ArbreRenduINF2990::NOM_CIBLE);

	// Nettoyage.
	delete noeudVide;
	delete noeudCible;

	// On vide l'arbre.
	arbre->vider();
}

void ArbreRenduINF2990Test::boiteEnglobante()
{
	// On cr�e une cible.
	NoeudAbstrait* noeudCible = arbre->creerNoeud(ArbreRenduINF2990::NOM_CIBLE);

	// On obtient sa position.
	glm::dvec3 vecteur{ noeudCible->obtenirPositionRelative() };

	// On v�rifie que le noeud est en position relative (0,0,0).
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[0]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[1]));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(vecteur[2]));

	// On cr�e un point � (0,0,0)
	glm::dvec3 point;
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;

	// On v�rifie qu'il est dans la bo�te englobante de la cible.
	CPPUNIT_ASSERT(noeudCible->pointEstDansBoite(point));

	// On d�place le point en X.
	point[0] = 100;
	point[1] = 0;
	point[2] = 0;

	// On v�rifie qu'il n'est plus dans la bo�te englobante de la cible.
	CPPUNIT_ASSERT(!noeudCible->pointEstDansBoite(point));

	// Nettoyage.
	delete noeudCible;

	// On vide l'arbre.
	arbre->vider();
}

void ArbreRenduINF2990Test::selectionTable()
{
	// On initialise l'arbre avec le fichier XML par d�faut
	arbre->initialiser();

	// On v�rifie que les �l�ments par d�faut sont dans l'arbre.
	CPPUNIT_ASSERT(arbre->estDefaut() == true);

	// On cherche une table.
	NoeudAbstrait* noeudTable = arbre->chercher(ArbreRenduINF2990::NOM_TABLE);

	CPPUNIT_ASSERT(!noeudTable->estSelectionnable());

	// On cherche un ressort.
	NoeudAbstrait* noeudRessort = arbre->chercher(ArbreRenduINF2990::NOM_RESSORT);

	CPPUNIT_ASSERT(noeudRessort->estSelectionnable());

	// On vide l'arbre.
	arbre->vider();
}

void ArbreRenduINF2990Test::testDeselection()
{

}

void ArbreRenduINF2990Test::testRotation()
{
	// On initialise l'arbre avec le fichier XML par d�faut
	arbre->initialiser();

	// On cherche un ressort.
	NoeudAbstrait* noeudRessort = arbre->chercher(ArbreRenduINF2990::NOM_RESSORT);

	// S�lectionner l'objet
	noeudRessort->assignerSelection(true);

	// Rotation originale.
	glm::dvec3 rotOriginale = noeudRessort->obtenirRotation();

	glm::dvec3 vecteur;
	vecteur[0] = 0;
	vecteur[1] = 0;
	vecteur[2] = 30;

	VisiteurAbstrait* visiteurRot = new VisiteurRotation(vecteur);

	// Test du visiteur.
	CPPUNIT_ASSERT(noeudRessort->accepterVisiteur(visiteurRot));

	// Nouvelle valeur de rotation.
	glm::dvec3 nouvRotation = noeudRessort->obtenirRotation();

	// Il y a eu une rotation.
	CPPUNIT_ASSERT(rotOriginale != nouvRotation);

	// Nettoyage.
	delete visiteurRot;

	// On vide l'arbre.
	arbre->vider();
}
