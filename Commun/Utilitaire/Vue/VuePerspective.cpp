////////////////////////////////////////////////////////////////////////////////////
/// @file VuePerspective.cpp
/// @author The Ballers
/// @date 2015-04-01
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "VuePerspective.h"
#include <iostream>

namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn VuePerspective::VuePerspective(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une vue perspective.  Ne fait que cr�er les objets
	/// Projection et Camera correspondant.
	///
	/// @param[in] camera        : Cam�ra � utiliser au d�part pour cette vue.
	/// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture.
	/// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture.
	/// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture.
	/// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arri�re (en @a z).
	/// @param[in] ratio         : Le rapport d'aspect du plan avant du volume de visualisation 
	/// @param[in] fovy          : L'angle de visionnement de la projection perspective
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	VuePerspective::VuePerspective(Camera const& camera, ProjectionPerspective const& projection) :
		Vue{ camera },
		projection_{ projection }
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn const ProjectionPerspective& VuePerspective::obtenirProjection() const
	///
	/// Retourne la projection perspective associ�e � cette vue.
	///
	/// @return La projection perspective associ�e � cette vue.
	///
	////////////////////////////////////////////////////////////////////////
	const ProjectionPerspective& VuePerspective::obtenirProjection() const
	{
		return projection_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::appliquerProjection() const
	///
	/// Applique la matrice de projection correspondant � cette vue.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::appliquerProjection() const
	{
		projection_.mettreAJourProjection();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::appliquerCamera() const
	///
	/// Applique la matrice correspondant � cette vue selon la position de
	/// la cam�ra (eventuellement un gluLookAt()).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::appliquerCamera() const
	{
		camera_.positionnerOrbite();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
	///                       nouvelle cl�ture.
	/// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
	///                       nouvelle cl�ture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		projection_.redimensionnerFenetre(coinMin, coinMax);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerIn()
	{
		
		double nouvelleDistance =camera_.obtenirDistance() /  projection_.obtenirIncrementZoom();
		if (nouvelleDistance >= projection_.obtenirZoomInMax())
			camera_.assignerDistance(nouvelleDistance);
		
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerOut()
	{
		/*Obtenir l'incr�ment de zoom � partir de la projection plus tard*/

		double nouvelleDistance = camera_.obtenirDistance() * projection_.obtenirIncrementZoom();
		if (nouvelleDistance <= projection_.obtenirZoomOutMax())
			camera_.assignerDistance(nouvelleDistance);

	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerInElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in �lastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonn�es du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonn�es du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerInElastique(const glm::ivec2&,
		const glm::ivec2&)
	{
		/// Not implemented for the moment was : projection_.zoomerIn(coin1, coin2)
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::zoomerOutElastique(const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out �lastique.
	/// 
	/// @param[in]  coin1 : Coin contenant les coordonn�es du premier coin du
	///                     rectangle.
	/// @param[in]  coin2 : Coin contenant les coordonn�es du second coin du
	///                     rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::zoomerOutElastique(const glm::ivec2&,
		const glm::ivec2&)
	{
		/// Not implemented for the moment was : projection_.zoomerOut(coin1, coin2)
	}



	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::deplacerZ(double deplacement)
	///
	/// Ne fait rien, car se d�placer dans l'axe de la profondeur n'a pas
	/// vraiment de signification avec une vue perspective.
	///
	/// @param[in]  deplacement : D�placement selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::deplacerZ(double)
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::rotaterXY(double rotationX, double rotationY)
	///
	/// Permet de faire une rotation de la cam�ra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'�l�vation.
	///
	/// Une rotation de 100% correspondant � 360 degr�s en X (angle de
	/// rotation) ou 180 degr�s en Y (angle d'�l�vation).
	///
	/// @param[in]  rotationX : Rotation en pourcentage de la largeur.
	/// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::rotaterXY(double rotationX, double rotationY)
	{
		// On veut une rotation entre 0.0 et 1.0. COmme d�j� expliqu�, 
		// les valeurs habituelles de rotationX et rotationY sont 
		// de 10.0 avec le signe correspondant
		rotationX /= 100.0; rotationY /= 100.0;
		camera_.orbiterXY(rotationX * 360, rotationY * 180, false);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::rotaterXY(const glm::ivec2& rotation)
	///
	/// Permet de faire une rotation de la cam�ra autour du point vers
	/// lequel elle regarde en modifiant l'angle de rotation et l'angle
	/// d'�l�vation.
	///
	/// Un d�placement de la taille de la fen�tre correspond � 100%.
	///
	/// @param[in]  rotation : Rotation en coordonn�es de clot�re (pixels).
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::rotaterXY(const glm::ivec2& rotation)
	{
		const glm::ivec2 dimensions{ projection_.obtenirDimensionCloture() };
		rotaterXY(rotation[0] / (double)dimensions[0],
			rotation[1] / (double)dimensions[1]);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::rotaterZ(double rotation)
	///
	/// Ne fait rien, car tourner autour de l'axe de la profondeur
	/// correspondrait � un rouli et n'est pas souhaitable pour cette vue.
	///
	/// @param[in]  rotation : Rotation selon l'axe Z.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::rotaterZ(double)
	{
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void VuePerspective::centrerSurPoint(glm::ivec2 pointCentre)
	///
	/// Modifie les bornes de la fen�tre virtuelle afin de se placer sur le
	/// point pass� en param�tre.
	///
	/// @param[in]  rotation : Le point milieu d�sir� de la nouvelle fen�tre
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void VuePerspective::centrerSurPoint(glm::ivec2)
	{
		//projection_.centrerSurPoint(pointCentre);
	}

	void VuePerspective::deplacerXY(double deplacementX, double deplacementY)
	{
		camera_.orbiterXY(deplacementX, deplacementY, false);
	}

	void VuePerspective::deplacerXY(const glm::ivec2& deplacement)
	{
		camera_.orbiterXY(deplacement.x, deplacement.y, false);
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
