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
		std::cout << "\n Zoom in Maximal : " << zoomInMax
			<< "\n Zoom out Maximale: " << zoomOutMax << '\n';
		ajusterRapportAspect(DirectionZoom::IN_);
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

		if (zoomInValide(xMinFenetre_, xMaxFenetre_, yMinFenetre_, yMaxFenetre_) == false)
		{
			xMaxFenetre_ = xMaxCopie;
			xMinFenetre_ = xMinCopie;
			yMaxFenetre_ = yMaxCopie;
			yMinFenetre_ = yMinCopie;
		}

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
		double augmentationX = (incrementZoom_ - 1.0) * 0.5 * (xMaxFenetre_ - xMinFenetre_);
		double augmentationY = (incrementZoom_ - 1.0) * 0.5 * (yMaxFenetre_ - yMinFenetre_);

		if (zoomOutValide((xMinFenetre_ - augmentationX), (xMaxFenetre_ + augmentationX),
			(yMinFenetre_ - augmentationY), (yMaxFenetre_ + augmentationY)) == false)
		{
			return;
		}

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
	/// Les coordonn�es re�ues sont en coordonn�es OpenGL (coord. de Fen�tre)
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2)
	{
		std::cout << " coin1.x | coin1.y : " << coin1.x << " | " << coin1.y<< "\n";
		std::cout << " coin2.x | coin2.y : " << coin2.x << " | " << coin2.y << "\n \n";

		if (abs(coin2.x - coin1.x) < 5 || abs(coin2.y - coin1.y) < 5)
		{
			std::cout << "Rectangle trop petit, pas de zoom \n";
			return;
		}

		double pointMilieuSelectionX = (coin1.x + coin2.x) / 2.0;
		double pointMilieuSelectionY = (coin1.y + coin2.y) / 2.0;
		
		// L'astuce est simple : on fixe les valeurs de coordonn�es
		// de fen�tre aux coordonn�es OpenGL donn�es, puis on corrige
		// le rapport d'aspect
		xMinFenetre_ = (coin1.x < coin2.x ? coin1.x : coin2.x);
		xMaxFenetre_ = (coin1.x > coin2.x ? coin1.x : coin2.x);
		
		yMinFenetre_ = (coin1.y < coin2.y ? coin1.y : coin2.y);
		yMaxFenetre_ = (coin1.y > coin2.y ? coin1.y : coin2.y);
		
		ajusterRapportAspect(DirectionZoom::IN_);
		centrerSurPoint(glm::dvec2(pointMilieuSelectionX, pointMilieuSelectionY));
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
	void ProjectionOrtho::zoomerOut(const glm::dvec2& coin1, const glm::dvec2& coin2)
	{
		if (coin1.x == coin2.x || coin1.y == coin2.y)
			return;

		const double longueurFenetreActuelle = (xMaxFenetre_ - xMinFenetre_);
		const double xGaucheCoin = (coin1.x < coin2.x ? coin1.x : coin2.x);
		const double xDroiteCoin = (coin1.x > coin2.x ? coin1.x : coin2.x);
		const double xRatioSelectionFenetreActuelle = (xDroiteCoin - xGaucheCoin) * 1.0 / longueurFenetreActuelle;
		
		std::cout << "WARNING : xCoinGauche | xCoinDroite " << xGaucheCoin << " | " << xDroiteCoin << "\n \n";

		std::cout << "xMin | xMax Fenetre: " << xMinFenetre_ << " | " << xMaxFenetre_ << "\n";
		std::cout << "yMin | yMax Fenetre: " << yMinFenetre_ << " | " << yMaxFenetre_ << "\n \n";
		/// Section pour X ///
		double longueurFenetreSelection = abs(xDroiteCoin - xGaucheCoin);
		double nouvelleLongueurX = longueurFenetreActuelle / xRatioSelectionFenetreActuelle;
		double proportionRelativeCoinGauche = (xGaucheCoin - xMinFenetre_) / longueurFenetreActuelle;

		// On place notre fenetre virtuelle a la longueur proportionnelle
		double nouveauXMinFenetre = xMinFenetre_ - (proportionRelativeCoinGauche * nouvelleLongueurX);
		double nouveauXMaxFenetre = xMinFenetre_ + (nouvelleLongueurX - (xMinFenetre_ - nouveauXMinFenetre));

		///TODO(Emilio): Penser � faire une m�thode afin de ne pas dupliquer le code
		/// Section pour Y ///
		const double hauteurFenetreActuelle = yMaxFenetre_ - yMinFenetre_;
		const double yMinCoin = (coin1.y < coin2.y ? coin1.y : coin2.y);
		const double yMaxCoin = (coin1.y > coin2.y ? coin1.y : coin2.y);
		const double yRatioSelectionFenetreActuelle = (yMaxCoin - yMinCoin) * 1.0 / hauteurFenetreActuelle;
		double nouvelleLongueurY = hauteurFenetreActuelle / yRatioSelectionFenetreActuelle;
		double proportionRelativeCoinBas = (yMinCoin - yMinFenetre_) / hauteurFenetreActuelle;

		double nouveauYMinFenetre = yMinFenetre_ - (proportionRelativeCoinBas * nouvelleLongueurY);
		double nouveauYMaxFenetre = yMinFenetre_ + (nouvelleLongueurY - (yMinFenetre_ - nouveauYMinFenetre));;

		if (zoomOutValide(nouveauXMinFenetre, nouveauXMaxFenetre,
			nouveauYMinFenetre, nouveauYMaxFenetre) == false)
		{
			return;
		}

		// On applique les nouvelles dimenstions 
		xMinFenetre_ = nouveauXMinFenetre;
		xMaxFenetre_ = nouveauXMaxFenetre;
		yMinFenetre_ = nouveauYMinFenetre;
		yMaxFenetre_ = nouveauYMaxFenetre;

		std::cout << "xMin | xMax Fenetre: " << xMinFenetre_ << " | " << xMaxFenetre_ << "\n";
		std::cout << "yMin | yMax Fenetre: " << yMinFenetre_ << " | " << yMaxFenetre_ << "\n \n";

		ajusterRapportAspect(DirectionZoom::OUT_);
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
		//std::cout << "Facteurs de deplacement : " <<
		//	"X : " << deplacementX << " Y: " << deplacementY << std::endl;
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
		// Il faut calculer la variation que notre d�placement
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
	void ProjectionOrtho::centrerSurPoint(const glm::dvec2& pointCentre)
	{
		// � IMPLANTER.
		// N.B: Puisque le fonction existante 'translater' suppose que les 
		// d�placements sont faites � partir des coordonn�es de cl�tures,
		// je fais le translate ici.
		
		glm::dvec2 currentPoint((xMinFenetre_ + xMaxFenetre_) / 2.0, (yMinFenetre_ + yMaxFenetre_) / 2.0);
		glm::dvec2 deplacement(pointCentre - currentPoint);

		std::cout << "\n Vecteur de deplacemnt: (" << deplacement.x << ", " << deplacement.y << ") \n";
		// D�placement (en supposant que le vecteur est bon)
		xMinFenetre_ += deplacement.x;
		xMaxFenetre_ += deplacement.x;

		yMinFenetre_ += deplacement.y;
		yMaxFenetre_ += deplacement.y;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect(DirectionZoom)
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @param[in]	dir : Sp�cifie s'il s'agit d'un zoomIn ou d'un zoomOut
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect(DirectionZoom dir)
	{
		double delta = 0.0;
		double rapportAspect = abs(xMaxCloture_ - xMinCloture_) / abs(yMaxCloture_ - yMinCloture_);
		double rapportAspectVirtuel = (xMaxFenetre_ - xMinFenetre_) / (yMaxFenetre_ - yMinFenetre_);

		std::cout << "------Avant Correction Rapport d'aspect Fenetre : " << rapportAspectVirtuel<< "\n \n";
		
		if (abs(rapportAspect - rapportAspectVirtuel) / rapportAspect < (0.0001 * rapportAspect))
		{
			std::cout << "\n Rapports aspects sont egaux : pas d'ajustation \n";
			return; // Les deux rapports d'aspects sont consid�r�s dans la marge d'erreur
		}
		if (rapportAspectVirtuel > rapportAspect)
		{
			if (dir == IN_)
				ajusterRapportAspectY(rapportAspect, dir);
			else if (dir == OUT_)
				ajusterRapportAspectY(rapportAspect, dir);
		}
		else // if (rapportAspectVirtuel < 1.0)
		{
			if (dir == IN_)
				ajusterRapportAspectX(rapportAspect, dir);
			else if (dir == OUT_)
				ajusterRapportAspectX(rapportAspect, dir);
		}
		std::cout << "\n Apr�s ajustement de rapport d'aspect : \n";
		std::cout << "Rapport d'aspect Virtuel : " << (xMaxFenetre_ - xMinFenetre_) / (yMaxFenetre_ - yMinFenetre_) << '\n';
		std::cout << "Rapport d'aspect Cloture : " << rapportAspect << "\n \n";

	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspectY(double rapportAspect)
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// du rapport d'aspect de la clot�re. Ceci est fait en augmentant la
	/// vue verticalement.
	///
	/// @param[in]	rapportAspect : Valeur du rapport d'aspect de la clot�re
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspectY(double rapportAspect, DirectionZoom dir)
	{
		double delta = 0.0;
		std::cout << "AjusterRapportAspectY \n";
		double longueurVerticaleRequise = abs(xMaxFenetre_ - xMinFenetre_) / rapportAspect;
		delta = (longueurVerticaleRequise - abs(yMaxFenetre_ - yMinFenetre_)) / 2.0;
		std::cout << "delta Y: " << delta;
		if (dir == DirectionZoom::IN_) delta = abs(delta);
		std::cout << "delta Y: " << delta;
		yMaxFenetre_ += delta;
		yMinFenetre_ -= delta;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspectX(double rapportAspect)
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// du rapport d'aspect de la clot�re. Ceci est fait en augmentant la
	/// vue horizontalement.
	///
	/// @param[in]	rapportAspect : Valeur du rapport d'aspect de la clot�re
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspectX(double rapportAspect, DirectionZoom dir)
	{
		double longueurHorizontaleRequise = abs(yMaxFenetre_ - yMinFenetre_) * rapportAspect;
		double delta = (longueurHorizontaleRequise - abs(xMaxFenetre_ - xMinFenetre_)) / 2.0;
		if (dir == DirectionZoom::IN_) delta = abs(delta);
		std::cout << "delta X: " << delta;
		xMaxFenetre_ += delta;
		xMinFenetre_ -= delta;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool bornesSontValide(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax);
	///
	/// V�rfie que les nouvelles bornes qui tentent d'�tre appliqu�es 
	/// respecteront les bornes �tablies lors de la cr�ation de la Vue.
	///
	/// @param[in]	xBorneMin : Borne inf�rieure en X
	/// @param[in]	xBorneMin : Borne sup�rieure en X
	/// @param[in]	xBorneMin : Borne inf�rieure en Y
	/// @param[in]	xBorneMin : Borne sup�rieure en Y
	///
	/// @return L'indication pour proc�der au zoom
	///
	////////////////////////////////////////////////////////////////////////
	bool ProjectionOrtho::zoomOutValide(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax)
	{
		bool valide = false;
		if (xBorneMax - xBorneMin >= zoomOutMax_ || yMaxFenetre_ - yMinFenetre_ >= zoomOutMax_)
		{
			std::cout << "La fenetre serait trop petite: zoom annul� ! \n";
		}
		else
			valide = true;

		return valide;
	}

	bool ProjectionOrtho::zoomInValide(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax)
	{
		bool valide = false;
		if (xBorneMax - xBorneMin <= zoomInMax_ || yMaxFenetre_ - yMinFenetre_ <= zoomInMax_)
		{
			std::cout << "La fenetre serait trop petite: zoom annul� ! \n";
		}
		else
			valide = true;
		return valide;
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
