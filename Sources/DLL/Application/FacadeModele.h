//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @ingroup Application
//////////////////////////////////////////////////////////////////////////////

/**
*  @defgroup INF2990 INF2990
* Painball
*/

/**
*	@defgroup Noyau Noyau
*	@ingroup INF2990
*  Ce module contient le coeur de l'application.
*/

/** @defgroup Application Application
*	@ingroup Noyau
*/

#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__


#include <windows.h>
#include <string>
#include "glm/glm.hpp"

class NoeudAbstrait;
class ArbreRenduINF2990;

namespace vue {
   class Vue;
}


///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.
   static FacadeModele* obtenirInstance();
   /// Lib�re l'instance unique de la classe.
   static void libererInstance();

   /// Cr�e un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration � partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Lib�re le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du mod�le.
   void afficher() const;
   /// Affiche la base du contenu du mod�le.
   void afficherBase() const;
 
   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

   /// R�initialise la sc�ne.
   void reinitialiser();

   /// Anime la sc�ne.
   void animer(float temps);


   int selectionnerObjetSousPointClique(int i, int j, int largeur, int hauteur, bool ctrlDown = false);

   /// Deplacement des noeuds selectionn�s dans l'arbre de rendu.
   void deplacerSelection(int x1, int y1, int x2, int y2);

   /// Rotation des noeuds s�lectionn�s
   void tournerSelectionSouris(int x1, int y1, int x2, int y2);

   /// Scale de la s�lection
   void agrandirSelection(int x1, int y1, int x2, int y2);

   /// xxxxx
   void rectangleElastique(int i, int j);
   
   /// xxxxx
   int selectionMultiple(bool c);

   void initialiserRectangleElastique(int i, int j);

   void terminerRectangleElastique();

   /// V�rifier si un point cliqu� est dans la table
   bool verifierCliqueDansTable(int x, int y);

   /// Pour la duplication d'objets selectionn�s
   void dupliquerSelection(int i, int j);

   /// Pour la sauvegarde de fichier XML
   int creerXML(char* path, int prop[6]);

   /// V�rifier si un point cliqu� est dans la table 
   bool estDansTable(glm::dvec3 pointDuMonde);

private:
   /// Constructeur par d�faut.
   FacadeModele() = default;
   /// Destructeur.
   ~FacadeModele();
   /// Constructeur copie d�sactiv�.
   FacadeModele(const FacadeModele&) = delete;
   /// Op�rateur d'assignation d�sactiv�.
   FacadeModele& operator =(const FacadeModele&) = delete;

   static const std::string FICHIER_CONFIGURATION; /**< Nom du fichier XML dans lequel doit se trouver la configuration. */

   static FacadeModele* instance_; ///< Pointeur vers l'instance unique de la classe. */

   HWND  hWnd_{ nullptr }; ///< Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
   HGLRC hGLRC_{ nullptr }; ///< Poign�e ("handle") vers le contexte OpenGL.
   HDC   hDC_{ nullptr }; ///< Poign�e ("handle") vers le "device context".

   vue::Vue* vue_{ nullptr }; ///< Vue courante de la sc�ne. */
   ArbreRenduINF2990* arbre_{ nullptr }; ///< Arbre de rendu contenant les diff�rents objets de la sc�ne. */

   glm::dvec3 selectionBasGauche_, selectionHautDroit_;
   glm::ivec2 pointInitial_, pointAvant_;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__
