////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONORTHO_H__
#define __UTILITAIRE_PROJECTIONORTHO_H__


#include "Projection.h"

enum DirectionZoom { IN_ = 1, OUT_= -1 };
namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class ProjectionOrtho
	/// @brief Classe implantant une projection orthogonale.
	///
	/// Cette classe implante l'interface de projection d�finie par la
	/// classe de base Projection et ajoute certaines fonctionnalit�es
	/// sp�cifiques � la projection orthogonale, comme le zoom autour d'un
	/// point en particulier et le zoom �lastique.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	////////////////////////////////////////////////////////////////////////
	class ProjectionOrtho : public Projection
	{
	public:
		/// Constructeur.
		ProjectionOrtho(double xMinCloture, double xMaxCloture,
			double yMinCloture, double yMaxCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom,
			double xMinFenetre, double xMaxFenetre,
			double yMinFenetre, double yMaxFenetre);

		/// Assignation par copie non-n�cessaire dans le contexte
		ProjectionOrtho& operator=(ProjectionOrtho const&) = delete;

		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn();
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut();
		/// Modification de la cl�ture.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax);
		/// Application de la projection.
		virtual void appliquer() const;


		/// Zoom out �lastique, sur un rectangle.
		void zoomerOut(const glm::dvec2& coin1, const glm::dvec2& coin2);
		/// Zoom in �latique, sur un rectangle.
		void zoomerIn(const glm::ivec2& coin1, const glm::ivec2& coin2);

		/// Translater la fen�tre virtuelle d'un pourcentage en @a X ou en @a Y
		void translater(double deplacementX, double deplacementY);
		/// Translater la fen�tre virtuelle d'un vecteur
		void translater(const glm::ivec2& deplacement);
		/// Centrer la fen�tre virtuelle sur un point
		void centrerSurPoint(const glm::dvec2& pointCentre);

		/// Obtenir les coordonn�es de la fen�tre virtuelle.
		virtual inline void obtenirCoordornneesFenetreVirtuelle(
			double& xMin, double& xMax, double& yMin, double& yMax
			) const;

		/// Obtenir la dimension de la fen�tre virtuelle
		virtual inline glm::dvec2 obtenirDimensionFenetreVirtuelle() const;
		
		virtual void conserverRapportAspect();

	private:

		/// V�rifie que la translation ne d�passe pas les bordures maximales du centre du jeu
		bool translationDepasseBordure(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax);

		/// D�cide la direction de correction en fonction du zoom.
		void ajusterRapportAspect(DirectionZoom dir);

		/// Ajuste la fen�tre en modifiant la port�e verticale
		void ajusterRapportAspectY(double rapportAspect, DirectionZoom dir);

		/// Ajuste la fen�tre en modifiant la port�e horizontale
		void ajusterRapportAspectX(double rapportAspect, DirectionZoom dir);

		/// V�rifie si les nouvelles bornes de la fan�tre viole les bornes des facteurs de zoom
		bool zoomInValide(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax);

		/// V�rifie si les nouvelles bornes de la fan�tre viole les bornes des facteurs de zoom
		bool zoomOutValide(double xBorneMin, double xBorneMax, double yBorneMin, double yBorneMax);

		/// Borne inf�rieure en X de la fen�tre virtuelle.
		double xMinFenetre_;
		/// Borne sup�rieure en X de la fen�tre virtuelle.
		double xMaxFenetre_;
		/// Borne inf�rieure en Y de la fen�tre virtuelle.
		double yMinFenetre_;
		/// Borne sup�rieure en Y de la fen�tre virtuelle.
		double yMaxFenetre_;

	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
	///
	/// Cette fonction retourne les coordonn�es de la fen�tre virtuelle
	/// associ�e � cette projection.
	///
	/// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
	/// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
	/// @param[out]  yMin : La variable qui contiendra l'ordonn�e minimale.
	/// @param[out]  yMax : La variable qui contiendra l'ordonn�e maximale.
	///
	/// @return Les coordonn�es de la fen�tre virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline void ProjectionOrtho::obtenirCoordornneesFenetreVirtuelle(
		double& xMin, double& xMax, double& yMin, double& yMax
		) const
	{
		xMin = xMinFenetre_;
		xMax = xMaxFenetre_;
		yMin = yMinFenetre_;
		yMax = yMaxFenetre_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline glm::dvec2 ProjectionOrtho::obtenirDimensionFenetreVirtuelle() const
	///
	/// Cette fonction retourne les dimensions de la fen�tre virtuelle
	/// associ�e � cette projection orthographique.
	///
	/// @return Les dimensions de la fen�tre de virtuelle.
	///
	////////////////////////////////////////////////////////////////////////
	inline glm::dvec2 ProjectionOrtho::obtenirDimensionFenetreVirtuelle() const
	{
		return glm::dvec2{ xMaxFenetre_ - xMinFenetre_, yMaxFenetre_ - yMinFenetre_ };
	}
}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTIONORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
