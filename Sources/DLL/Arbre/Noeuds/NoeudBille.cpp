///////////////////////////////////////////////////////////////////////////
/// @file NoeudBille.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudBille.h"
#include "Utilitaire.h"

#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>
#include <iomanip>

#include "Modele3D.h"
#include "NoeudComposite.h"
#include "../ArbreRenduINF2990.h"
#include "NoeudTable.h"
#include "../../Application/FacadeModele.h"
#include "../../Commun/Utilitaire/AideCollision.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include "glm\gtx\norm.hpp"
#include "../../Commun/Externe/glm/include/glm/gtx/Projection.hpp"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::NoeudBille(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBille::NoeudBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	vitesse_ = glm::dvec3{ 10 ,100, 0 };
	constanteDeFrottement_ = 1.0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::~NoeudBille()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudBille::~NoeudBille()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	// Affichage du modele.
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if (spotLight_) {
		/* TO DO SOMETHING HERE */
	}

	if (colorShift_)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	if (pause_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ZERO); // Set The Blending Function For Translucency
		glEnable(GL_BLEND);
	}
	else if (impossible_)
		glColorMask(0, 1, 1, 1);
	else if (selectionne_) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		if (twin_ != nullptr && twin_ != NULL)
			twin_->setTransparent(true);

	}
	else if (transparent_) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	else
		if (twin_ != nullptr && twin_ != NULL)
			twin_->setTransparent(false);
	if (twin_ != nullptr && twin_ != NULL)
		if (!selectionne_ && !twin_->estSelectionne())
			twin_->setTransparent(false);

	glTranslatef(0.0, -10, 0.0); // Il faudrait changer le mod�le
	liste_->dessiner();
	glPopAttrib();
	// Restauration de la matrice.
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::animer(float temps)
///
/// Le travail fait dans cette m�thode est comme suit,
///  - Calculer la somme des forces agissant sur la bille 
///  - Calculer la nouvelle vitesse
///		- Calculer la vitesse apres la collision (pr�sentement juste la d�tection)
///		- Calculer la nouvelle vitesse en appliquant les forces
///  - Calculer la nouvelle position � partir de la vitesse apr�s la collision.
///  - Changer l'oritentation de la bille pour faire comme si elle roule (TODO).
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::animer(float temps) // rajouter des parametres ou une fonction animerCollision(float temps, detailCollision detail)
{
	static int counter = 0;
	counter++;


	NoeudComposite::animer(temps);
	// A METTRE DANS LA FACADEMODELE
	// Somme des forces agissant sur les particules.
	// =============================================
	glm::dvec3 attractionsPortails{ 0, 0, 0 };
	glm::dvec3 gravite{ 0, -30*masse_, 0 };
	glm::dvec3 forceFrottement{ 0, 0, 0 };
	if (glm::length(vitesse_) > 0.001)
		forceFrottement = -constanteDeFrottement_ * glm::normalize(vitesse_);
	glm::dvec3 forceTotale = forceFrottement + gravite + attractionsPortails;



	// Calcul de la nouvelle vitesse. 
	// =============================

	glm::dvec3 vitesseApresCollision = vitesse_;


	// Obtenir une liste de noeuds a checker pour une collision
	std::vector<NoeudAbstrait*> noeudsAChecker;
	std::list<NoeudAbstrait*> listeNoeudsAChecker;
	bool useQuadTree = false;

	/*	
	if (useQuadTree)
	{
		// TODO faire une liste de noeuds candidats � �tre en collision avec la bille
			// Obtenir le quad
		QuadTree* quadTree = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->obtenirQuadTree();
		listeNoeudsAChecker = quadTree->retrieve(this);
		if (counter % 30 == 0)
		{
			std::cout << "Size de listeNoeudsAChecker : " << listeNoeudsAChecker.size() << std::endl;
		}
	}
	*/
	
	if (1)
	{
		// Travail a faire par le quad tree
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
		NoeudComposite* table = (NoeudComposite*)arbre->getEnfant(0);
		for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
		{
			NoeudAbstrait* noeud = table->getEnfant(i);
			// conditions a verifier?
			if (noeud != this && noeud->getType() != "generateurbille")
				noeudsAChecker.push_back(noeud);
		}
	}

	
	bool enCollision = false;

	// Pour chaque noeud � checker, v�rifier s'il est en collision avec la bille (this)

	/*
	if (useQuadTree)
	{
		// Pour chaque noeud de la liste, checker collisions et r�agir...
		std::list<NoeudAbstrait*>::iterator iter = listeNoeudsAChecker.begin();
		for (; iter != listeNoeudsAChecker.end(); iter++)
		{
			NoeudAbstrait* noeudCourrant = *iter;
			std::vector<glm::dvec3> boite;
			{ // Travail a faire par std::vector<glm::dvec3> NoeudAbstrait::obtenirBoite()
				glm::dvec3 tableau[4];
				noeudCourrant->obtenirVecteursBoite(tableau[0], tableau[1], tableau[2], tableau[3]);
				for (unsigned int i = 0; i < 4; i++) boite.push_back(tableau[i] + noeudCourrant->obtenirPositionRelative());
			}
			for (unsigned int i = 0; i < boite.size(); i++)
			{
				// On veut calculer la collision en 2D et caster les param�tres en glm::dvec2 "oublie" leur composante en Z et choisi la bonne surcharge de calculerCollisionSegment.
				aidecollision::DetailsCollision details = aidecollision::calculerCollisionSegment((glm::dvec2)boite[i], (glm::dvec2)boite[(i + 1) % boite.size()], (glm::dvec2)positionRelative_, 7, true);
				if (details.type != aidecollision::COLLISION_AUCUNE)
				{
					enCollision = true;
					glm::dvec3 vitesseNormaleInitiale = glm::proj(vitesse_, details.direction);
					glm::dvec3 vitesseTangentielleInitiale = vitesse_ - vitesseNormaleInitiale;
					glm::dvec2 vitesseNormale2D = aidecollision::calculerForceAmortissement2D(details, (glm::dvec2)vitesse_, 1.0);
					vitesseApresCollision = vitesseTangentielleInitiale + glm::dvec3{ vitesseNormale2D.x, vitesseNormale2D.y, 0 };
				}
			}
		}
	}
	*/

	if (1)
	{
		for (NoeudAbstrait* noeud : noeudsAChecker)
		{
			std::vector<glm::dvec3> boite = noeud->obtenirVecteursEnglobants();
			if (boite.size() > 1)
			{
				for (unsigned int i = 0; i < boite.size(); i++) boite[i] += noeud->obtenirPositionRelative();
				// Considerer tous les segments boite[i] --- boite[i+1 % size] 
				for (unsigned int i = 0; i < boite.size(); i++)
				{
					// On veut calculer la collision en 2D et caster les param�tres en glm::dvec2 "oublie" leur composante en Z et choisi la bonne surcharge de calculerCollisionSegment.
					aidecollision::DetailsCollision details = aidecollision::calculerCollisionSegment((glm::dvec2)boite[i], (glm::dvec2)boite[(i + 1) % boite.size()], (glm::dvec2)positionRelative_, 7, true);
					if (details.type != aidecollision::COLLISION_AUCUNE)
					{
						enCollision = true;
						mettreAJourCollision(noeud);
						glm::dvec3 vitesseNormaleInitiale = glm::proj(vitesse_, details.direction);
						glm::dvec3 vitesseTangentielleInitiale = vitesse_ - vitesseNormaleInitiale;
						glm::dvec2 vitesseNormale2D = aidecollision::calculerForceAmortissement2D(details, (glm::dvec2)vitesse_, 1.0);
						vitesseApresCollision = vitesseTangentielleInitiale + glm::dvec3{ vitesseNormale2D.x, vitesseNormale2D.y, 0 };
					}
				}
			}
			else if (boite.size() == 1)
			{
				double rayon = boite[0].x;
				aidecollision::DetailsCollision details = aidecollision::calculerCollisionCercle((glm::dvec2)noeud->obtenirPositionRelative(), rayon, (glm::dvec2)positionRelative_, 7);
				if (details.type != aidecollision::COLLISION_AUCUNE)
				{
					enCollision = true;
					mettreAJourCollision(noeud);
					glm::dvec3 vitesseNormaleInitiale = glm::proj(vitesse_, details.direction);
					glm::dvec3 vitesseTangentielleInitiale = vitesse_ - vitesseNormaleInitiale;
					glm::dvec2 vitesseNormale2D = aidecollision::calculerForceAmortissement2D(details, (glm::dvec2)vitesse_, 1.0);
					vitesseApresCollision = vitesseTangentielleInitiale + glm::dvec3{ vitesseNormale2D.x, vitesseNormale2D.y, 0 };
				}

			}
		}

		// Considerer les limites de la table.
		std::vector<glm::dvec3> boite;
		boite.push_back({ 108, -190, 0 });
		boite.push_back({ 272, -190, 0 });
		boite.push_back({ 272, 96, 0 });
		boite.push_back({ 108, 96, 0 });
		// Considerer tous les segments boite[i] --- boite[i+1 % size] 
		for (unsigned int i = 0; i < boite.size(); i++)
		{
			// On veut calculer la collision en 2D et caster les param�tres en glm::dvec2 "oublie" leur composante en Z et choisi la bonne surcharge de calculerCollisionSegment.
			aidecollision::DetailsCollision details = aidecollision::calculerCollisionSegment((glm::dvec2)boite[i], (glm::dvec2)boite[(i + 1) % boite.size()], (glm::dvec2)positionRelative_, 7, true);
			if (details.type != aidecollision::COLLISION_AUCUNE)
			{
				enCollision = true;

				glm::dvec3 vitesseNormaleInitiale = glm::proj(vitesse_, details.direction);
				glm::dvec3 vitesseTangentielleInitiale = vitesse_ - vitesseNormaleInitiale;
				glm::dvec2 vitesseNormale2D = aidecollision::calculerForceAmortissement2D(details, (glm::dvec2)vitesse_, 1.0);
				vitesseApresCollision = vitesseTangentielleInitiale + glm::dvec3{ vitesseNormale2D.x, vitesseNormale2D.y, 0 };
			}
		}
	}
	
	assignerImpossible(enCollision);
	
	glm::dvec3 nouvellePosition = positionRelative_ + (double)temps*vitesseApresCollision;

	glm::dvec3 nouvelleVitesse = vitesseApresCollision + (double)temps * forceTotale / masse_;


	if(debug_ && enCollision) {
		afficherVitesse(vitesseApresCollision);
	}

	// Calcul de la rotation
	// =====================
	// C'est pas la bonne facon de calculer la rotation a appliquer a la boule,
	// C'est pas un bug, j'ai just pas encore trouve la bonne facon de le faire.
	double constanteACalculer{ 0.1 }; // Depend du rayon de la boule, mais avec 0.1, ca parait deja bien.
	glm::dvec3 rotation{ 0, 0, 0 };
	rotation.x = constanteACalculer * -vitesse_.y;
	rotation.y = constanteACalculer * vitesse_.x;

	// Assignation des nouvelles valeurs.
	assignerRotation(rotation);
	positionRelative_ = nouvellePosition;
	vitesse_ = nouvelleVitesse;
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudBille::accepterVisiteur(VisiteurAbstrait* vis)
///
/// Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis : Le visiteur a traiter
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudBille::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::setDebug(bool debug)
///
/// Cette fonction change al valeur du mode debug
///
/// @param[in] debug : La valeur du mode debug a assigner
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::setDebug(bool debug)
{
	debug_ = debug;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::setSpotLight(bool debug)
///
/// Cette fonction change la valeur du mode spotLight
///
/// @param[in] debug : La valeur du mode debug a assigner pour le spotLight
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::setSpotLight(bool debug)
{
	spotLight_ = debug;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::afficherVitesse(glm::dvec3 nouvelleVitesse)
/// Affiche la nouvelle vitesse donnee a une bille apres une collision.
///
/// @param[in] nouvelleVitesse : La valeur de la vitesse a imprimer
///
/// @return aucun
/// 
////////////////////////////////////////////////////////////////////////
void NoeudBille::afficherVitesse(glm::dvec3 nouvelleVitesse)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	std::cout << std::fixed << std::setw(2) << std::setprecision(2) << time.wHour << ":"
		<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wMinute << ":"
		<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wSecond << ":"
		<< std::fixed << std::setfill('0') << std::setw(3) << std::setprecision(3) << time.wMilliseconds;

	std::cout << std::fixed << std::setfill('0') << std::setw(2) << " - Vitesse " << glm::length(nouvelleVitesse) << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::mettreAJourCollision(NoeudAbstrait* noeud)
///
/// Cette fonction met a jour le pointage
///
/// @param[in] noeud : Le noeud a analyser
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::mettreAJourCollision(NoeudAbstrait* noeud)
{
	std::string nomCollison = noeud->obtenirType();
	if (nomCollison == "butoird" || nomCollison == "butoirg")
		SingletonGlobal::obtenirInstance()->collisionButoirTriangulaire();
	else if (nomCollison == "butoirecirculaire" )
		SingletonGlobal::obtenirInstance()->collisionButoirCirculaire();
	else if (nomCollison == "cible")
		SingletonGlobal::obtenirInstance()->collisionButoirCible();
	else
		return;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudBille::obtenirVecteursEnglobants()
///
/// La boite englobante d'un butoir circulaire, c'est un rayon.
/// Pour etre conforme avec les boites englobantes des autres noeuds, 
/// on retourne quand meme un vector<glm::dvec3> mais avec un seul element
/// dont le x contient le rayon.
///
/// @return Un vecteur<glm::dvec3> dont le seul element a le rayon de l'objet
/// comme premiere coordonnee.
/// 
////////////////////////////////////////////////////////////////////////
std::vector<glm::dvec3> NoeudBille::obtenirVecteursEnglobants()
{
	double rayonModele = (boite_.coinMax.x - boite_.coinMin.x) / 2.0;
	return{ glm::dvec3{ rayonModele * scale_.x, 0, 0 } };
}