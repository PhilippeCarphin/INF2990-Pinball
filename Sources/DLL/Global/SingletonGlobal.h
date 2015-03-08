////////////////////////////////////////////////
/// @file   SingletonGlobal.h
/// @author The Ballers
/// @date   2015-02-24
///
/// @ingroup SingletonGlobal
////////////////////////////////////////////////

#ifndef __SINGLETONGLOBAL_H__
#define __SINGLETONGLOBAL_H__


///////////////////////////////////////////////////////////////////////////
/// @class SingletonGlobal
/// @brief 
///
/// @author The Ballers
/// @date 2015-02-24
///////////////////////////////////////////////////////////////////////////
class SingletonGlobal
{

public:

	/// Obtient l'instance unique de la classe.
	static SingletonGlobal* obtenirInstance();

	/// Lib�re l'instance unique de la classe.
	static void libererInstance();

	/// AJOUTER VOS GET/SET sur les variables ici

protected:

	/// Constructeur vide d�clar� protected.
	SingletonGlobal() {};

	/// Destructeur vide d�clar� protected.
	~SingletonGlobal() {};

private:

	static SingletonGlobal* singleton_;

	/// Constructeur par copie d�clar� mais non d�fini.
	SingletonGlobal(const SingletonGlobal&) = delete;

	/// Op�rateur d'assignation d�clar� mais non d�fini.
	SingletonGlobal& operator=(const SingletonGlobal&) = delete;

	/// AJOUTER VOS VARIABLES GLOBAL ICI


};

#endif // __SINGLETONGLOBAL_H__