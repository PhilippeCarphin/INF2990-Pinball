//////////////////////////////////////////////////////////////////////////////
/// @file Projection.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTION_H__
#define __UTILITAIRE_PROJECTION_H__


#include "glm/glm.hpp"

namespace vue {


	////////////////////////////////////////////////////////////////////////
	/// @class Projection
	/// @brief Classe contr�lant la projection du monde � la fen�tre.
	///
	/// Cette classe offre certaines fonctionnalit�s commune � chacun des types
	/// de projection (isom�trique, perspective, etc.).  Elle d�finit une
	/// interface que doivent implanter les types concrets de projection,
	/// c'est-�-dire permettre de modifier le facteur de zoom par exemple.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	////////////////////////////////////////////////////////////////////////
	class Projection
	{
	public:
		/// Constructeur.
		Projection(double xMinCloture, double xMaxCloture,
			double yMinCloture, double yMaxCloture,
			double zAvant, double zArriere,
			double zoomInMax, double zoomOutMax,
			double incrementZoom, bool estPerspective);

		/// Assignation par copie non-n�cessaire dans le contexte
		Projection& operator=(Projection const&) = delete;

		/// Destructeur virtuel vide.
		virtual ~Projection() {}

		/// Zoom in, c'est-�-dire un agrandissement.
		virtual void zoomerIn() = 0;
		/// Zoom out, c'est-�-dire un rapetissement.
		virtual void zoomerOut() = 0;
		/// Modification de la cl�ture.
		virtual void redimensionnerFenetre(const glm::ivec2& coinMin,
			const glm::ivec2& coinMax) = 0;
		/// Application de la projection.
		virtual void appliquer() const = 0;


		/// Application de la fen�tre de cl�ture (appel � glViewport).
		void mettreAJourCloture() const;
		/// Application de la projection.
		void mettreAJourProjection() const;

		/// Obtention des dimensions de la fen�tre de clot�re.
		inline glm::dvec2 obtenirDimensionCloture() const;
		/// Obtention des coordonn�es de la fen�tre de cl�ture.
		inline void obtenirCoordonneesCloture(
			double& xMin, double& xMax, double& yMin, double& yMax
			) const;

		/// V�rification de si la projection est perspective.
		inline bool estPerspective() const;

		/// Obtenir la dimension de la fen�tre virtuelle
		virtual inline glm::dvec2 obtenirDimensionFenetreVirtuelle() const = 0;

		/// Obtenir les bornes de la fen�tre virtuelle
		virtual inline void obtenirCoordornneesFenetreVirtuelle(
			double& xMin, double& xMax, double& yMin, double& yMax
			) const = 0;

		virtual void conserverRapportAspect() const { return; };

	protected:
		/// Coordonn�e inf�rieur de la cl�ture en X.
		double xMinCloture_;
		/// Coordonn�e sup�rieur de la cl�ture en X.
		double xMaxCloture_;
		/// Coordonn�e inf�rieur de la cl�ture en Y.
		double yMinCloture_;
		/// Coordonn�e sup�rieur de la cl�ture en Y.
		double yMaxCloture_;

		/// Avant du volume de visualisation.
		double zAvant_;
		/// Arri�re du volume de visualisation.
		double zArriere_;

		/// Facteur maximal de zoom in.
		const double zoomInMax_;
		/// Facteur maximal de zoom out.
		const double zoomOutMax_;
		/// Incr�ment des zooms.
		const double incrementZoom_;
		/// Vrai si la projection est perspective.
		const bool   estPerspective_;
	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline glm::dvec2 Projection::obtenirDimensionCloture() const
	///
	/// Cette fonction retourne les dimensions de la fen�tre de cl�ture
	/// associ�e � cette projection.
	///
	/// @return Les dimensions de la fen�tre de cl�ture.
	///
	////////////////////////////////////////////////////////////////////////
	inline glm::dvec2 Projection::obtenirDimensionCloture() const
	{
		return glm::dvec2{ xMaxCloture_ - xMinCloture_, yMaxCloture_ - yMinCloture_ };
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Projection::obtenirCoordonneesCloture(int& xMin, int& xMax, int& yMin, int& yMax) const
	///
	/// Cette fonction retourne les coordonn�es de la fen�tre de cl�ture
	/// associ�e � cette projection.
	///
	/// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
	/// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
	/// @param[out]  yMin : La variable qui contiendra l'ordonn�e minimale.
	/// @param[out]  yMax : La variable qui contiendra l'ordonn�e maximale.
	///
	/// @return Les coordonn�es de la fen�tre de cl�ture.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Projection::obtenirCoordonneesCloture(
		double& xMin, double& xMax, double& yMin, double& yMax
		) const
	{
		xMin = xMinCloture_;
		xMax = xMaxCloture_;
		yMin = yMinCloture_;
		yMax = yMaxCloture_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline bool Projection::estPerspective() const
	///
	/// Cette fonction retourne vrai si la projection est une projection
	/// perspective.
	///
	/// @return Vrai si la projection est une projection perspective.
	///
	////////////////////////////////////////////////////////////////////////
	inline bool Projection::estPerspective() const
	{
		return estPerspective_;
	}


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTION_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
