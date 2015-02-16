///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"

#include <map>
#include <string>
#include "tinyxml2.h"


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui repr�sente l'arbre de rendu sp�cifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilis�s par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par d�faut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu � son �tat initial.
   void initialiser();

   /// Obtenir le i�me enfant de l'arbre
   NoeudAbstrait* getEnfant(int position) const;

   /// Methode de test
   glm::dvec3 getPosRessort() const { return posRessort; };

   /// Accepter un visiteur
   virtual bool accepterVisiteur(VisiteurAbstrait* vis);

   /// Initialiser l'arbre � partir d'un fichier XML
   bool initialiserXML(std::string nomFichier);

   /// Obtenir les propri�t�s de la zone de jeu
   int* obtenirProprietes() const { return proprietes_; };

   /// Permet de savoir si l'arbre est la zone de jeu par d�faut
   bool estDefaut() const;

   static const std::string NOM_BUTOIRD; ///< Repr�sente le type Butoir droit
   static const std::string NOM_BUTOIRG; ///< Repr�sente le type Butoir gauche
   static const std::string NOM_BUTOIRCIRCULAIRE; ///< Repr�sente le type Butoir circulaire
   static const std::string NOM_CIBLE; ///< Repr�sente le type Cible
   static const std::string NOM_BILLE; ///< Repr�sente le type Bille
   static const std::string NOM_GENERATEURBILLE; ///< Repr�sente le type Generateur bille
   static const std::string NOM_MUR; ///< Repr�sente le type Mur
   static const std::string NOM_PALETTED; ///< Repr�sente le type Palette droite
   static const std::string NOM_PALETTEG; ///< Repr�sente le type Palette gauche
   static const std::string NOM_PORTAIL; ///< Repr�sente le type Portail
   static const std::string NOM_RESSORT; ///< Repr�sente le type Ressort
   static const std::string NOM_TROU; ///< Repr�sente le type Trou
   static const std::string NOM_VIDE; ///< Repr�sente le type Vide
   static const std::string NOM_COUVERCLE; ///< Repr�sente le type Couvercle
   static const std::string NOM_TABLE; ///< Repr�sente le type Table

private:

	/// Lire un fichier XML
	bool lireXML(tinyxml2::XMLDocument& doc);

	// D�finir ce qu'est la zone de jeu par d�faut
	void assignerDefaut();

	/// Propri�t�s de la zone de jeu
	int* proprietes_ = new int[6];

	// Zone de jeu par d�faut
	glm::dvec3 posRessort;
	glm::dvec3 scaleRessort;
	glm::dvec3 angleRessort;
	glm::dvec3 posTrou;
	glm::dvec3 scaleTrou;
	glm::dvec3 angleTrou;
	glm::dvec3 posGenerateur;
	glm::dvec3 scaleGenerateur;
	glm::dvec3 angleGenerateur;

};


#endif // __ARBRE_ARBRERENDUINF2990_H__
