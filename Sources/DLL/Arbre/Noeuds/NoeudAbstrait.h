///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////////

/** @defgroup Noeud Noeud
*	@ingroup Arbre
*/

#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


#include <windows.h>
#include <GL/gl.h>
#include <string>

#include "glm\glm.hpp"
#include "../../Visiteurs/VisiteurAbstrait.h"
#include "Utilitaire.h"

/// D�clarations avanc�es pour contenir un pointeur vers un mod�le3D et sa liste
/// d'affichage
namespace modele{
	class Modele3D;
	namespace opengl_storage{
		class OpenGL_Liste;
	}
}

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilis�e pour cr�er l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant �tre pr�sent dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(
		const std::string& type = std::string{ "" }
	);
	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();

	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;

	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

	/// Obtient la position relative du noeud.
	inline const glm::dvec3& obtenirPositionRelative() const;

	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative(const glm::dvec3& positionRelative);

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// �crit l'�tat de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);
	/// V�rifie si le noeud se fait afficher.
	inline bool estAffiche() const;

	/// �crit l'�tat de la s�lection du noeud.
	inline void assignerSelection(bool selectionne);
	/// V�rifie si le noeud est s�lectionn�.
	inline bool estSelectionne() const;
	/// V�rifie si la positin du noeud est ill�gale
	inline bool estImpossible() const;
	/// Assigner le statut de possibilite
	inline void assignerImpossible(bool impossible);
	/// �crit si le noeud peut �tre s�lectionn� ou non.
	inline void assignerEstSelectionnable(bool selectionnable);
	/// �crit le zoom sur le noeud.
	inline void assignerEchelle(glm::dvec3 scale);
	/// �crit le rotation sur le noeud.
	inline void assignerRotation(glm::dvec3 rotation);
	inline void assignerRotationHard(glm::dvec3 rotation){ rotation_ = rotation; };
	/// �crit le rotation 0,0,0 sur le noeud.
	inline void resetRotation();
	/// V�rifie si le noeud est s�lectionnable.
	inline bool estSelectionnable() const;
	/// �crit si le noeud peut �tre enregistr� ou non.
	inline void assignerEstEnregistrable(bool enregistrable);
	/// V�rifie si le noeud est enregistrable.
	inline bool estEnregistrable() const;

	/// �crit si le noeud peut �tre modifi� ou non.
	void assignerEstModifiable(bool modif) { modifiable_ = modif; };

	void assignerEstAjustable(bool ajust) { ajustable_ = ajust; };
	/// V�rifie si le noeud est modifiable.
	bool estModifiable() const { return modifiable_; };
	// V�rifie qu'on peut agrandir l'objet
	bool estAjustable() const{ return ajustable_; }
	/// Assigne le mod�le3D et la liste d'affichage du noeud courant
	inline void assignerObjetRendu(modele::Modele3D const* modele, modele::opengl_storage::OpenGL_Liste const* liste);

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();
	/// Efface le noeud pass� en param�tre.
	virtual void effacer(const NoeudAbstrait* noeud);

	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(const std::string& typeNoeud) const;
	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher(const std::string& typeNoeud);
	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(unsigned int indice) const;
	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher(unsigned int indice);

	/// Ajoute un noeud enfant.
	virtual bool ajouter(NoeudAbstrait* enfant);
	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;
	/// Obtient le numero du noeud.
	int getNumero(){ return numeroNoeud_; };

	/// Changer la s�lection du noeud.
	virtual void inverserSelection();
	/// Efface les enfants s�lectionn�s.
	virtual void effacerSelection();
	/// S�lectionne tous les enfants de m�me que le noeud.
	virtual void selectionnerTout();
	/// D�s�lectionne tous les enfants de m�me que le noeud.
	virtual void deselectionnerTout();
	/// V�rifier si le noeud ou un de ses enfants est s�lectionn�.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);
	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);
	/// Affiche le noeud.
	virtual void afficher() const;
	/// Affiche le noeud de mani�re concr�te.
	virtual void afficherConcret() const;
	/// Anime le noeud.
	virtual void animer(float dt);
	/// Accepter un visiteur
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);
	/// Obtenir jumeau
	virtual NoeudAbstrait* getTwin();
	/// Ajouter jumeau
	virtual void setTwin(NoeudAbstrait* twin);
	//Obtenir les 4 vecteurs de la boite englobante modifie
	virtual void obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4);
	virtual void obtenirBoiteModele(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4);
	//Verifie si un point est dans la boite englobante
	virtual bool pointEstDansBoite(glm::dvec3 point);

	/// Obtenir couleur
	virtual bool getColorShift();
	/// Selectionner couleur
	virtual void setColorShift(bool colorShift);

	/// Obtenir transparence
	virtual bool getTransparent();
	/// Selectionner transparence
	virtual void setTransparent(bool transparent);

	/// Obtenir rouge
	virtual bool getImpossible();
	/// Selectionner rouge
	virtual void setImpossible(bool impossible);

	/// Obtenir modele
	modele::Modele3D const* obtenirModele() const;

	/// Obtenir agrandissement
	inline const glm::dvec3& obtenirAgrandissement() const;

	/// Obtenir rotation
	inline const glm::dvec3& NoeudAbstrait::obtenirRotation() const;

	/// Obtenir le type
	std::string getType(){ return type_; }

protected:
	/// Si jumeau
	NoeudAbstrait* twin_{ nullptr };

	/// Type du noeud.
	std::string      type_;

	/// Mode d'affichage des polygones.
	GLenum           modePolygones_{ GL_FILL };

	/// Position relative du noeud.
	glm::dvec3         positionRelative_;

	/// Rescale relatif du noeud.
	glm::dvec3 		scale_;

	/// Rotation relative du noeud.
	glm::dvec3 		rotation_;

	/// Vrai si on doit afficher le noeud.
	bool             affiche_{ true };

	/// S�lection du noeud.
	bool             selectionne_{ false };

	/// Vrai si le noeud est s�lectionnable.
	bool             selectionnable_{ true };

	/// D�termine si l'objet peut �tre sauvegard� en XML.
	bool             enregistrable_{ true };

	/// D�termine si l'objet peut �tre modifi�
	bool             modifiable_{ true };

	bool			ajustable_{ true };

	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_{ nullptr };

	/// Mod�le 3D correspondant � ce noeud.
	modele::Modele3D const* modele_;
	/// Storage pour le dessin du mod�le
	modele::opengl_storage::OpenGL_Liste const* liste_;

	/// Compteur d'instances;
	static unsigned int compteurNoeuds_;

	/// Num�ro d'instance.
	int numeroNoeud_;

	///boite englobante
	utilitaire::BoiteEnglobante boite_;

	/// Couleur du noeud
	bool colorShift_;

	/// Transparence
	bool transparent_;

	/// Impossibilit� de position
	bool impossible_;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
	NoeudAbstrait* parent
	)
{
	parent_ = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// � son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
{
	return positionRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport � son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const glm::dvec3& positionRelative
	)
{
	positionRelative_ = positionRelative;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une cha�ne repr�sentante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'�tat affich� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche(bool affiche)
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'�tat que le noeud se fait afficher ou non.
///
/// @return L'�tat affich� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @param selectionne : L'�tat s�lectionn� ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEchelle( double scale )
///
/// Cette fonction permet d'assigner un zoom a l'objet.
///
/// @param selectionne : L'echelle a appliquee.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEchelle(glm::dvec3 scale)
{
	scale_ = scale;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEchelle( foloat rotation )
///
/// Cette fonction permet d'assigner une rotation a l'objet.
///
/// @param selectionne : La rotation a appliquee.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerRotation(glm::dvec3 rotation)
{
	rotation_ += rotation;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEchelle( foloat rotation )
///
/// Cette fonction permet d'assigner une rotation a l'objet.
///
/// @param selectionne : La rotation a appliquee.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::resetRotation()
{
	rotation_ = { 0.0, 0.0, 0.0 };
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionn� ou non du noeud.
///
/// @return L'�tat s�lectionn� ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non s�lectionnable n'est jamais s�lectionn�.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @param selectionnable : L'�tat s�lectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable(bool selectionnable)
{
	selectionnable_ = selectionnable;
	selectionne_ = selectionne_ && selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerImpossible( bool impossible )
///
/// Cette fonction permet d'assigner l'�tat d'�tre impossible ou non du noeud.
///
/// @param selectionnable : L'�tat impossible ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerImpossible(bool impossible)
{
	impossible_ = impossible;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::estImpossible( bool impossible )
///
/// Cette fonction permet d'obtenir l'�tat d'�tre impossible ou non du noeud.
///
/// @param selectionnable : L'�tat impossible ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estImpossible() const
{
	return impossible_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'�tat d'�tre s�lectionnable ou non du noeud.
///
/// @return L'�tat s�lectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'�tat d'�tre entregistrable ou non du noeud.
///
/// @param enregistrable : L'�tat enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstEnregistrable(bool enregistrable)
{
	enregistrable_ = enregistrable;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'�tat d'�tre enregistrable en XML ou non du
/// noeud.
///
/// @return L'�tat enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estEnregistrable() const
{
	return enregistrable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D* modele, modele::opengl_storage::OpenGL_Liste* liste)
///
/// Cette fonction assigne l'objet de rendu au mod�le, c'est-�-dire son
/// mod�le 3D et sa liste d'affichage
///
/// @param modele : le mod�le 3D
/// @param liste : la liste d'affichage OpenGL
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D const* modele, modele::opengl_storage::OpenGL_Liste const* liste)
{
	modele_ = modele;
	liste_ = liste;
	boite_ = utilitaire::calculerBoiteEnglobante(*modele_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirAgrandissement() const
///
/// Cette fonction retourne l'agrandissement du noeud par rapport
/// � son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirAgrandissement() const
{
	return scale_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirRotation() const
///
/// Cette fonction retourne l'agrandissement du noeud par rapport
/// � son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirRotation() const
{
	return rotation_;
}

#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__