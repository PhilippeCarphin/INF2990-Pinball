////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author Samuel Millette
/// @date 2015-02-10
/// @version 1.0
///
/// @ingroup Test
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "NoeudCible.h"
#include "NoeudTable.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
///
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::setUp()
{
	noeud = std::make_unique<NoeudTable>(ArbreRenduINF2990::NOM_TABLE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
///
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::tearDown()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEnfants()
///
/// Cas de test: s'assurer que le noeud abstrait n'a pas d'enfant
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEnfants()
{
	// On v�rifie qu'initialement, le noeud n'a pas d'enfant
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);

	// Essaie d'ajouter un noeud
	NoeudComposite* nouveauNoeud{ new NoeudCible{ ArbreRenduINF2990::NOM_CIBLE } };
	bool ajout{ noeud->ajouter(nouveauNoeud) };

	// L'ajout devrait avoir r�ussi, puisqu'il s'agit d'un noeud composite...
	CPPUNIT_ASSERT(ajout == true);

	// Assurons-nous que le noeud poss�de un d'enfant...
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 2);

	// Nettoyage
	noeud->effacer(nouveauNoeud);

	// Assurons-nous que le noeud ne poss�de plus d'enfant...
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeud->calculerProfondeur() == 1);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
