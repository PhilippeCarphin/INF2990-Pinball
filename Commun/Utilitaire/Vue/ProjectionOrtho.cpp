////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/gl.h>
#include "ProjectionOrtho.h"

#include <iostream>

namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture.
	/// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture.
	/// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture.
	/// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arri�re (en @a z).
	/// @param[in] xMinFenetre   : coordonn�e minimale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonn�e maximale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonn�e minimale en @a y de la fen�tre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonn�e maximale en @a y de la fen�tre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		xMinFenetre_{ xMinFenetre },
		xMaxFenetre_{ xMaxFenetre },
		yMinFenetre_{ yMinFenetre },
		yMaxFenetre_{ yMaxFenetre }
	{
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		double xMaxCopie = xMaxFenetre_;
		double xMinCopie = xMinFenetre_;
		double yMaxCopie = yMaxFenetre_;
		double yMinCopie = yMinFenetre_;

		// Formules qui proviennent de la r�solution d'un syst�me d'�quation
		// Bless you, based Wolfram Alpha !
		xMaxFenetre_ = ((xMaxCopie * incrementZoom_) + xMaxCopie + xMinCopie * incrementZoom_ - xMinCopie) / (2 * incrementZoom_);
		xMinFenetre_ = (xMaxCopie * (incrementZoom_ - 1) + xMinCopie * (incrementZoom_ + 1.0)) / (2 * incrementZoom_);

		yMaxFenetre_ = ((yMaxCopie * incrementZoom_) + yMaxCopie + yMinCopie * incrementZoom_ - yMinCopie) / (2 * incrementZoom_);;
		yMinFenetre_ = (yMaxCopie * (incrementZoom_ - 1) + yMinCopie * (incrementZoom_ + 1.0)) / (2 * incrementZoom_);

		std::cout << "Taille de la fenetre virtuelle : " <<
			(xMaxFenetre_ - xMinFenetre_) << "x" << (yMaxFenetre_ - yMinFenetre_) << std::endl;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		// � IMPLANTER.
		double augmentationX = (incrementZoom_ - 1.0) * 0.5 * (xMaxFenetre_ - xMinFenetre_);
		double augmentationY = (incrementZoom_ - 1.0) * 0.5 * (yMaxFenetre_ - yMinFenetre_);
		
		xMinFenetre_ -= augmentationX;
		xMaxFenetre_ += augmentationX;

		yMinFenetre_ -= augmentationY;
		yMaxFenetre_ += augmentationY;
		
		std::cout << "Taille de la fenetre virtuelle : " <<
			(xMaxFenetre_ - xMinFenetre_) << "x" << (yMaxFenetre_ - yMinFenetre_) << std::endl;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// L'agrandissement de la fen�tre virtuelle est proportionnel �
	/// l'agrandissement de la clot�re afin que les objets gardent la m�me
	/// grandeur apparente lorsque la fen�tre est redimensionn�e.
	///
	/// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
	///                       nouvelle cl�ture
	/// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
	///                       nouvelle cl�ture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		
		// coinMax contient les dimensions de la nouvelle fen�tree, car coinMin
		// est essentiellement tout le temps � z�ro. on �tabli le facteur qu'il
		// faut �largir le viewport vers la gauche et la droite en fonction des
		// valeurs pr�c�dentes: 
		double xScaleFactor = coinMax[0] * 1.0 / ((xMaxCloture_ - xMinCloture_) * 1.0);
		double yScaleFactor = coinMax[1] * 1.0 / ((yMaxCloture_ - yMinCloture_) * 1.0);

		std::cout << "xMin | xMax Cloture : " << xMinCloture_ << " | " << xMaxCloture_ << "\n";
		std::cout << "yMin | yMax Cloture : " << yMinCloture_ << " | " << yMaxCloture_ << "\n";
		
		std::cout << "xMin | xMax Fenetre: " << xMinFenetre_ << " | " << xMaxFenetre_ << "\n";
		std::cout << "yMin | yMax Fenetre: " << yMinFenetre_ << " | " << yMaxFenetre_ << "\n";
		
		// Affichage de d�bug :
		if (xScaleFactor != 1 || yScaleFactor != 1 )
		std::cout << "xScaleFactor : " << xScaleFactor << std::endl 
			<< "yScaleFactor :" << yScaleFactor << std::endl;

		// On fait en sorte que le rendu soit de la bonne taille en multipliant
		// par le facteur de scale. Puisque la fen�tre virtuelle peut avoir des
		// coordonn�es n�gatives, il faut s'assurer que les calculs math�matiques
		// s'appliquent dans tous les cas. On teste premi�rement si on agrandit 
		// ou rapetisse la fen�tre virtuelle : 
		if (xScaleFactor > 1)
			xMaxFenetre_ += (xScaleFactor - 1.0) * (xMaxFenetre_ - xMinFenetre_);
		else if (xScaleFactor < 1)
			xMaxFenetre_ -= (1.0 - xScaleFactor) * (xMaxFenetre_ - xMinFenetre_);
		
		if (yScaleFactor > 1)
			yMinFenetre_ -= (yScaleFactor - 1.0) * (yMaxFenetre_ - yMinFenetre_);
		else if (yScaleFactor < 1)
			yMinFenetre_ += (1.0 - yScaleFactor) * (yMaxFenetre_ - yMinFenetre_);
		//  le (int)( /* ... */  sert a cast en int pour eviter les warnings
		// On sauvegarde la nouvelle taille de la clot�re : 
		if (xScaleFactor > 1)
			xMaxCloture_ += (xScaleFactor - 1.0) * (xMaxCloture_ - xMinCloture_);
		else if (xScaleFactor < 1)
			xMaxCloture_ -= (1.0 - xScaleFactor) * (xMaxCloture_ - xMinCloture_);

		if (yScaleFactor > 1)
			yMaxCloture_ += (yScaleFactor - 1.0) * (yMaxCloture_ - yMinCloture_);
		else if (yScaleFactor < 1)
			yMaxCloture_ -= (1.0 - yScaleFactor) * (yMaxCloture_ - yMinCloture_);

		std::cout << "xMin | xMax Cloture : " << xMinCloture_ << " | " << xMaxCloture_ << "\n";
		std::cout << "yMin | yMax Cloture : " << yMinCloture_ << " | " << yMaxCloture_ << "\n";
		
		std::cout << "xMin | xMax Fenetre: " << xMinFenetre_ << " | " << xMaxFenetre_ << "\n";
		std::cout << "yMin | yMax Fenetre: " << yMinFenetre_ << " | " << yMaxFenetre_ << "\n";
		// On update le rendu
		appliquer();
		mettreAJourCloture();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fen�tre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propri�t�s de la
	/// fen�tre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer() const
	{
		glOrtho(xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in sur un rectangle d�termin� par deux coins.
	/// Ainsi la r�gion d�limit�e par le rectangle deviendra la fen�tre
	/// virtuelle.  La fen�tre r�sultante est ajust�e pour respecter le rapport
	/// d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		// � IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle d�limit� par deux coins.
	/// Ainsi la fen�tre virtuelle avant le zoom sera plac�e � l'interieur de
	/// la r�gion d�limit� par le rectangle.  La fen�tre r�sultante est ajust�e
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		// � IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de d�placer la fen�tre virtuelle en @a x et en @a y.  Les
	/// d�placement doivent �tre exprim�s en proportion de la fen�tre virtuelle.
	///
	/// @param[in]  deplacementX : le d�placement en @a x.
	/// @param[in]  deplacementY : le d�placement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(double deplacementX, double deplacementY)
	{
		// � IMPLANTER.
		std::cout << "Facteurs de deplacement : " <<
			"X : " << deplacementX << " Y: " << deplacementY << std::endl;
		double xTailleCourante = xMaxFenetre_ - xMinFenetre_;
		double yTailleCourante = yMaxFenetre_ - yMinFenetre_;

		double deltaX = deplacementX * xTailleCourante / 100.0;
		double deltaY = deplacementY * yTailleCourante / 100.0;

		xMaxFenetre_ += deltaX;
		xMinFenetre_ += deltaX;

		yMaxFenetre_ += deltaY;
		yMinFenetre_ += deltaY;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	///
	/// Permet de translater la fen�tre virtuelle en fonction d'un d�placement
	/// en coordonn�es de cl�ture.
	///
	/// @param[in]  deplacement : Le d�placement en coordonn�es de cl�ture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	{
		// � IMPLANTER.
		// Il faut calculer la variattion que notre d�placement
		// en coordonn�es de cloture engendre en coordonn�es virtuelles
		//
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Permet de centrer la fen�tre virtuelle sur un point de l'�cran. Le
	/// point de l'�cran est convertit en coordonn�es virtuelles et il devient
	/// le centre de la fen�tre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::ivec2& pointCentre)
	{
		// � IMPLANTER.
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{
		// � IMPLANTER.
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
